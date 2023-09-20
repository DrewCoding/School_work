#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main(){
    map<string, string> DataAddress;
    map<string, string> DataID;
    ifstream f("trees.txt");
    string id, address;

    if (!f.good()) {
       cerr << "Invalid file, cancelling operation." << endl;
       return (-1);
    }

    while(true)
    {
        getline(f, id);
        if(f.eof())
        {
            break;
        }

        getline(f, address);

        DataAddress.insert(make_pair(id, address));
        DataID.insert(make_pair(address, id));
    }


    int inputChoice = 0;
    string inputID = "";
    string inputAddress = "";

    do
    {
        cout << "Menu: " << endl;
        cout << "1. Find tree address by ID. " << endl;
        cout << "2. Find tree ID by address. " << endl;
        cout << "3. Exit " << endl;
        cout << "Your Choice: ";
        cin >> inputChoice;

        switch(inputChoice)
        {
            case 1:
            {
                cout << "Enter the tree ID: ";
                cin.ignore();
                cin >> inputID;
                if(DataAddress.count(inputID))
                {
                    cout << DataAddress[inputID] << endl;
                }
                else
                {
                    cout << "Invalid Entry." << endl;
                }
                break;
            }
            case 2:
            {
                cout << "Enter the tree address: ";
                cin.ignore();
                getline(cin, inputAddress);
                if(DataID.count(inputAddress))
                {
                    cout << DataID[inputAddress] << endl;
                }
                else
                {
                    cout << "Invalid Entry." << endl;
                    
                }
                
                break;
            }
            case 3:
            {
                cout << "Exiting..." << endl;
            
                break;
            }
            default:
                cout << "Invalid." << endl;
                break;
        }
        cout << endl;
    } while(inputChoice != 3);
    return 0;
}