//File reader, randomizer, and queue setup provided by Professor Amato

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>

using namespace std;

struct Customer{

    int lineEnterTime; //Time at which the customer enters the queue
    int cashierTime; //Time at which the customer is serviced
    
    int timeInLine; // The wait time of being in line before being serviced
};

// Number of parameters in each simulation
const int PARAMS_MAX = 5;

// Returns 'true' if a customer arrived during this minute, using a random number.

bool customerArrived(double prob) {
        double rv = rand() / (double(RAND_MAX) + 1);
        //return true;
        return (rv < prob);
}


void runSimulation(int simTime, double arrivalRate,
        int serviceTime, int maxLine,
        int &nServed, int &totalWait,
        int &totalLength, int &totalDropped) {
    queue<Customer> customerQueue;
    int curCustomerTime = 0;
    int totalLineSize = 0;
    nServed = 0;
    totalDropped = 0;
    for (int curTime = 0; curTime < simTime; curTime++) {
        // Length of the line accumulated by each minute
           
        totalLineSize += customerQueue.size();

        //See if a customer is arriving this minute.
        if (customerArrived(arrivalRate) == true) {
            if(customerQueue.size() < maxLine) // If there is room in the queue, add Customer to queue
            {
                if(customerQueue.empty())
                {
                    curCustomerTime = serviceTime;
                }
                Customer c;
                c.lineEnterTime = curTime;
                customerQueue.push(c);
            }
            else
            {
                totalDropped++; // If the line is at max capacity, the customer is dropped.
            }
        }

        // See if a customer is currently being serviced.
        
        if (!customerQueue.empty()) {
            
            // Get the next customer from the line
            if(curCustomerTime <= 0)
            {
                
                customerQueue.pop(); //remove front customer
                nServed++; // Add served amount
                if(!customerQueue.empty()) //If there is Customers behind the popped front() Customer, serve the next customer
                {
                    curCustomerTime = serviceTime;
                    customerQueue.front().cashierTime = curTime;
                    customerQueue.front().timeInLine = customerQueue.front().cashierTime - customerQueue.front().lineEnterTime;
                    totalWait += customerQueue.front().timeInLine;
                }
                
            }
        }
        if(!customerQueue.empty())
        {
            curCustomerTime--;
        }
        else
        {
            curCustomerTime = serviceTime;
        }
    }
    totalLength = totalLineSize;
}

// Read one simulation from the file.
//
// Each simulation is specified by 5 values, each on a single line:
// - Name (a string)
// - Simulation time - the overall number of minutes for the simulation
// - Arrival rate - per-minute arrival rate of customers
// - Service time - the time each customer takes at the register
// - Max. line size - the maximum number of people in line
//
bool readNextSimulation(ifstream &f, string &name, int &simulationTime,
        double &arrivalRate, int &serviceTime, int &lineSize) {
    string buf;
    string fileValues[5];
    int i = 0;

    while (getline(f, buf)) {
        // We've reached the end of the file, indicate to caller
        // there are no more simulations.
        if (f.eof())
            break;
        fileValues[i++] = buf;
        if (i == PARAMS_MAX) {
            // Fill in the values, converting to the right type
            name = fileValues[0];

            // Remove linefeed if necessary
            if (name.size() != 0 && name[name.size() - 1] == '\r')
                name.erase(name.size() - 1);

            simulationTime = atoi(fileValues[1].c_str());
            arrivalRate = atof(fileValues[2].c_str());
            serviceTime = atoi(fileValues[3].c_str());
            lineSize = atoi(fileValues[4].c_str());
            return (true);
        }
    }
    return (false);
}

//
// Reports the results of the simulation in tabular format.
//
void printReport(string name, int simTime, double arrivalRate,
        int serviceTime, int maxLine, int nServed, int totalWait,
        int totalLength, int totalDropped) {

    // Left-justify everything
    cout << left;

    // Print a table
    cout << endl;
    cout << setw(25) << "Simulation name: " << setw(12) << name << endl;
    cout << "--------------------------------------" << endl;
    cout << setw(25) << "Simulation time: " << setw(12) << simTime << endl;
    cout << setw(25) << "Arrival rate: " << setw(12) << arrivalRate << endl;
    cout << setw(25) << "Service time: " << setw(12) << serviceTime << endl;
    cout << setw(25) << "Max line size: " << setw(12) << maxLine << endl;
    cout << endl;
    cout << setw(25) << "Customers served:" << setw(12) << nServed << endl;
    cout << setw(25) << "Average wait time:" << double(totalWait) / nServed << endl;
    cout << setw(25) << "Average line length:" << setw(12)
         << double(totalLength) / simTime << endl;
   cout << setw(25) << "Total dropped customers:" << setw(12)
         << totalDropped << endl;
}

/* Main program */
int main() {
    // Sim results
    int nServed;
    int totalWait;
    int totalLength;
    int totalDropped;

    // Sim parameters
    string name;
    int simTime;
    double arrivalRate;
    int serviceTime;
    int maxLine;

    string buf;
    ifstream f("simtest.txt");

    // initialize the random number generator
    srand(time(NULL));

    if (!f.good()) {
       cerr << "Invalid file, exiting." << endl;
       return (-1);
    }

    while (readNextSimulation(f, name, simTime, arrivalRate, serviceTime, maxLine)) {
           runSimulation(simTime, arrivalRate, serviceTime, maxLine,
                nServed, totalWait, totalLength, totalDropped);
           printReport(name, simTime, arrivalRate,
                serviceTime, maxLine, nServed, totalWait, totalLength, totalDropped);
    }
    return 0;
}
