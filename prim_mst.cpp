#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <queue>

using namespace std;

//
// This file reads the facebook graph input file
// (.csv), builds a graph from the adjacencies described,
// and computes a Minimum Spanning Tree (MST) on the graph.
//
// The graph data structure is a simple adjacency list
// format -- each node (struct Person) 
// contains a string vector of all of its friend nodes.
//
#define IS_QUIT(s) (s == "X" || s == "x")
#define FILENAME "facebook-small.csv"
#define MAX_WEIGHT 65535
using namespace std;

// Data about a single person
struct Person {
    string name;
    bool mst_visited;
    int mst_weight;
    string mst_parent;
    vector<string> friends;
    vector<int> weights;
};

// Used for MST calculations, only holds the name,
// current best weight, and edge (parent)
struct PersonCandidate {
    string mst_name;
    string mst_parent;
    int mst_weight;
    bool operator< (const PersonCandidate &rhs) const {
        return mst_weight > rhs.mst_weight;
    }
};

void parse_line(const string &str,
        vector<string> &line) {
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ',')) {
        line.push_back(tmp);
    }
}

// Compute an MST using Prim's algorithm.
void MST(map<string, Person> &everyone, string source) {
    priority_queue<PersonCandidate> pq;
    PersonCandidate qNode, newqNode;

    // Put the root into the queue
    qNode.mst_weight = 0;
    qNode.mst_parent = "(none)";
    qNode.mst_name = source;
    pq.push(qNode);

    // Process each best edge in priority order
    // (these are PersonCandidates)
    while (!pq.empty()) {
        // Take the next best edge from the queue
        // (mst_weight is the weight of the best known edge to that node)
        qNode = pq.top();
        pq.pop();

        // If it's visited, it's a stale (less preferred) entry, skip
        Person &tmpPerson = everyone[qNode.mst_name];
        if (tmpPerson.mst_visited)
            continue;

        // Mark it as visited and update the Person in the map with
        // the parent and weight info.  We must use a reference here.
        tmpPerson.mst_visited = true;
        tmpPerson.mst_weight = qNode.mst_weight;
        tmpPerson.mst_parent = qNode.mst_parent;

        // Process each friend
        for (size_t i = 0; i < tmpPerson.friends.size(); i++) {
            Person &newPerson = everyone[tmpPerson.friends[i]];
            if (newPerson.mst_visited)
                continue;

            // Add an entry to the queue for this edge -- it may
            // not be picked if a better edge ends up higher in the
            // priority queue
            newqNode.mst_weight = tmpPerson.weights[i];
            newqNode.mst_parent = tmpPerson.name;
            newqNode.mst_name = tmpPerson.friends[i];
            pq.push(newqNode);
        }
    }
    cout << "MST from " << source << ": "  << endl;
    map<string, Person>::iterator it;
    for (it = everyone.begin(); it != everyone.end(); it++) {
        string n = it->first;
        Person p = it->second;
        cout << "Edge: "
             << p.mst_parent
             << " : " << n << " weight " << p.mst_weight << endl;
    }
}

int main() {
    ifstream inFile(FILENAME);
    vector<string> row;
    vector<string> names;
    map<string, Person> everyone;
    string inputLine;

    // Verify that the file open was OK
    if (!inFile.good()) {
        cerr << "Invalid file." << endl;
        return (-1);
    }

    // Read the header line of the file (first line, contains column labels).
    // We save this line (names) so we can lookup the string names in the
    // below loop.
    getline(inFile, inputLine);
    parse_line(inputLine, names);

    // Reach each subsequent entry
    while (getline(inFile, inputLine)) {
        if (inFile.eof())
            break;
        vector<string> row;
        Person p;
        parse_line(inputLine, row);

        // Use 0th field for our name, initialize the other fields
        p.name = row[0];
        p.mst_visited = false;
        p.mst_parent = "(none)";
        p.mst_weight = MAX_WEIGHT;

        // Start processing the rest of the fields at 1 ...
        for (size_t i = 1; i < row.size(); i++) {
            int adj_status = atoi(row[i].c_str());
            if (adj_status >= 1)  {
                // Maintain parallel vectors where the weight of the
                // edge from this person to names[i] is weights[i]
                p.friends.push_back(names[i]);
                p.weights.push_back(adj_status);
            }        
        }
        // Add this (new) person to the map.
        // In this map, the key is the string name of the person, and
        // the value is their Person structure (adjacency list).
        everyone.insert(make_pair(row[0], p));
    }

    // Output the graph
    map<string, Person>::iterator it = everyone.begin();
    while (it != everyone.end()) {
        string key = it->first;
        Person p = it->second;
        cout << p.name << " is connected to: " << endl;
        for (size_t i = 0; i < p.friends.size(); i++) {
            cout << "\t" << p.friends[i] << " weight " << p.weights[i] << endl;
        }
        it++;
    }

    for (;;) {
        cout << endl << "Enter the root of the MST (X to quit): ";
        getline(cin, inputLine);
        if (IS_QUIT(inputLine))
            break;
        if (everyone.count(inputLine) == 0) {
            cout << "Error: that person is not in the database." << endl;
            continue;
        }

        // Clear the previous state
        map<string, Person>::iterator it;
        for (it = everyone.begin(); it != everyone.end(); it++) {
            string n = it->first;
            Person &p = it->second;
            p.mst_visited = false;
            p.mst_weight = MAX_WEIGHT;
            p.mst_parent = "(none)";
        }

        // Compute the MST
        MST(everyone, inputLine);
    }
    cout << "Exiting..." << endl;
    return (0);
}
