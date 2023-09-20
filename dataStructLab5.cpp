#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

//
// This is a starter file to help frame your ideas around
// this program.
//

const string DATAFILE = "netflix.csv";     // Input file (CSV)
const int NFIELDS = 5;                     // Number of fields in
                                           // each line of the input file
const char DELIMITER = ',';                // The field separator for the file.
                                           // For a CSV, this is a comma.

// This holds a single Netflix entry.  Each line in the file should
// correspond to one of these structs.  If you use separate chaining, each bucket
// will have a linked list.
//
// Note: this structure is not yet ready to be part of a linked list.  It
// needs an additional pointer to the 'next' entry.
//
struct netflix_entry {
    string type;                   // The type of entry (movie or tv show)
    string title;                  // Title
    string director;               // Director's full name
    string country;                // Country of release
    int year;                      // Year of release

    netflix_entry *next;
};

// Starting number of buckets, adjust as needed -- should be a prime number.
const int HASH_SIZE = 2089;

// Hash table for all of the entries -- static so it's zeroed for free.
static netflix_entry *entryHash[HASH_SIZE];

// Generate a hash key, given a string (this would come from the
// string the user typed to find).  your hash function goes here.

// djb2 Hash function (Provided by Professor)
unsigned int getHashKey(const string& key) {
    unsigned int hash = 5381;
 
    for (int i = 0; i < key.size(); i++)
        hash = ((hash << 5) + hash) + key[i];

    return (hash % HASH_SIZE);
}

// Reads a single entry, filling in the
// fields (title, etc.) passed by the caller.
void readSingleEntry(const string &str,
        netflix_entry *newEnt) {
    istringstream istr(str);
    string fields[NFIELDS];
    string tmp;
    int i = 0;

    // Read each field separated by a comma
    while (getline(istr, tmp, DELIMITER) && i < NFIELDS) {
        fields[i++] = tmp;
    }

    // Make a new Netflix entry based on the
    // fields just read from the file.
    newEnt->type = fields[0];
    newEnt->title = fields[1];
    newEnt->director = fields[2];
    newEnt->country = fields[3];
    newEnt->year = atoi(fields[4].c_str()); // Convert the string to an int
    newEnt->next = 0;
}

// Insert a new entry into the hash table
void entryInsert(netflix_entry *newEnt) {

    int key = getHashKey(newEnt->title);
    
    if(entryHash[key] == nullptr) //If an entry does not exist (is null), insert the new entry in the null's place
    {
        entryHash[key] = newEnt;
        return;   
    }

    netflix_entry* n = entryHash[key];

    while(n->next != nullptr) // If an entry is in a slot, move down the list to the edge and place entry
    {
        n = n->next;
    }
    n-> next = newEnt;
   
}

// This function accepts a string title and a reference
// to an empty entry.
//
// Upon return,
// - 'foundEnt' will be filled-in with what was found.
// - The function will return 'true' if something was found, 'false' otherwise.
// - The 'ncmp' parameter tracks the number of comparisons required
//
bool entryFind(const string &title, netflix_entry &foundEnt, int &ncmp) {
    unsigned int key = getHashKey(title);
    
    if(entryHash[key] == NULL) //It is false if there is no entry that has been located
    {
        return false;
    }

    netflix_entry* n = entryHash[key];
    ncmp = 0;
    while(n != nullptr) //Move down entry and match the title parameter with the title entry and return true if found, return false if there is nothing.
    {
        ++ncmp;
        if(n->title == title)
        {
            foundEnt = *n;
            return true;
        }
        n = n->next;
    }
    return false;
}

//
// Sample main().
//
int main() {
    ifstream inFile(DATAFILE);
    string inputLine, inputStr;
    int linesRead = 0;

    if (!inFile.good()) {
        cerr << "Cannot open the input file!" << endl;
        exit(-1);
    } 

    // Read in each entry
    while (getline(inFile, inputLine)) {
        // Keep a counter of read lines.
        linesRead++;

        // Dynamically allocate a new entry
        netflix_entry *entp = new netflix_entry;

        // Read the next line from the file, passing a pointer
        // to the newly allocated entry.
        readSingleEntry(inputLine, entp);

        // Now we have a complete entry, find where it goes
        // in the hash table and add it.
        entryInsert(entp);

        // Extra debugging statement: uncomment this to
        // see how many lines are being read from the file
        // in real-time.
        //
        // if (linesRead % 25 == 0)
        //    cerr << "Inserted " << linesRead << " entries"
        //         << endl;
    }

    // Handle errors and/or summarize the read
    if (linesRead == 0) {
        cerr << "Nothing was read from the file!" << endl;
        return (-1);
    } else {
        cout << "Read " << linesRead << " entries." << endl;
        cout << fixed << setprecision(2) << endl;
    }

    // (example) Forever loop until the user requests an exit
    string movieName;
    netflix_entry movieInfo;
    int comparisons = 0;
    for (;;) {

        cout << "Enter a movie or show title (Type -1 to quit): ";
        getline(cin, movieName);
        if(movieName == "-1") //If input is -1, exit loop
        {
            break;
        }
        
        if(entryFind(movieName, movieInfo, comparisons)) //If the movie exists, display information
        {
            cout << "Comparisons: " << comparisons << endl;
            cout << "Type: " << movieInfo.type << endl;
            cout << "Title: " << movieInfo.title << endl;
            cout << "Director: " << movieInfo.director << endl;
            cout << "Country: " << movieInfo.country << endl;
            cout << "Release date: " << movieInfo.year << endl;
        }
        else //If the movie does not exist, display that it wasn't found.
        {
            cout << "Comparisons: " << comparisons << endl;
            cout << "Movie not found. Try again." << endl;
        }
    }

    // And we're done!
    cout << "Exiting..." << endl;

    return (0);
}