#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include "Queue.h"
#include <iomanip>
#include <cstdlib>

using namespace std;

//
// This file provides a starting point for Program #6.  It reads the 
// input file (.csv), builds a graph from the adjacencies in the file,
// and will print the friends list for any node requested.
//
// The graph is a simple adjacency list format -- each node (struct Person) 
// contains a string vector of all of its friend nodes.
//

#define IS_QUIT(s) (s == "X" || s == "x")
#define FILENAME "facebook.csv"
using namespace std;

struct Person {
    
    vector<string> friends;
    bool visited;
};

void parse_line(const string &str,
        vector<string> &line) {
    istringstream istr(str);
    string tmp;
    while (getline(istr, tmp, ',')) {
        line.push_back(tmp);
    }
}

bool search(vector<string> visited, string find) // This is meant to search for if a person/vertice was visited.
{
    for(int i = 0; i < visited.size(); i++)
    {
        if(visited[i] == find)
        {
            return true;
        }
    }
    return false;
}

bool breadthSearch(map<string, Person> everyone, string start, string end) {
    queue<string> q;
    vector<string> visited; // Where you store all the visited names
    string curr;

    visited.push_back(start); // Start has been visited
    q.push(start); //Push the start into the queue

    while(!q.empty())
    {
        curr = q.front(); // Get the first element of the queue
        q.pop(); 
        if(curr == end) 
        {
            return true;
        }

        for(int i = 0; i < everyone[curr].friends.size(); i++) //Iterate through all the friends lists
        {
            if(!search(visited, everyone[curr].friends[i])) // If a name has not been visitied,
            {
                q.push(everyone[curr].friends[i]);          // then it needs to be visited
                visited.push_back(everyone[curr].friends[i]);
            }
        }
    }

    return false;
}

int main() {
    ifstream inFile(FILENAME);
    vector<string> row;
    vector<string> names;
    map<string, Person> everyone;
    string inputLine;
    string first_Person, last_person;

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
        // Start at 1 (0th field is the string name)
        for (size_t i = 1; i < row.size(); i++) {
            int adj_status = atoi(row[i].c_str());
            // A '1' indicates an adjacency, so skip if we get a '0'
            // If there is an adjacency to this person, push the string name
            // of that person on the adjacency list.
            if (adj_status == 1)
                p.friends.push_back(names[i]);
        }
        // Add this (new) person to the map.
        // In this map, the key is the string name of the person, and
        // the value is their Person structure (adjacency list).
        everyone.insert(make_pair(row[0], p));
    }

    for (;;) {
        cout << endl << "Enter the first name "
             << "(X to quit): ";
        getline(cin, first_Person);
        //getline(cin, inputLine);
        if (IS_QUIT(first_Person))
            break;

        // Look up the adjacency list of this person in the map
        if (everyone.count(first_Person) == 0) {
            cout << "That person is not in the map." << endl;
            continue;
        }
        

        cout << endl << "Enter the end name "
             << "(X to quit): ";
        
        
        //getline(cin, inputLine);
        getline(cin, last_person);
        if (IS_QUIT(last_person))
            break;

        if (everyone.count(last_person) == 0) {
            cout << "That person is not in the map." << endl;
            continue;
        }
        
        

        if(breadthSearch(everyone, first_Person, last_person))
        {
            cout << "There is a path between the two." << endl;
        }
        else
        {
            cout << "There is NO path between the two." << endl;
        }
        
    }
    cout << "Exiting..." << endl;
    return (0);
}
