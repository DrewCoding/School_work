#include <iostream>
#include <queue>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

const int PARAMS_MAX = 5;

// Simulation reader provided by Professor Amato

bool customerArrived(double prob) {
        double rv = rand() / (double(RAND_MAX) + 1);
        return (rv < prob);
}

void runSimulation(int simTime, double arrivalRate,
        int serviceTime, int maxLine,
        int &nServed, int &totalWait,
        int &totalLength, int &totalDropped) {
    queue<int> customerQueue;
    int curCustomerTime = 0;
    // Main simulation loop
    for (int curTime = 0; curTime < simTime; curTime++) {
        // At the top of this loop, we're starting a new minute
        // of the simulation.
        // GENERAL STEPS:
        //
        // 1) First, add the current length of the line to an accumulator
        //    variable (like totalLineSize) of the queue to
        //    compute the average after the sim completes.
        // 2) See if a customer is arriving this minute.
        if (customerArrived(arrivalRate)) {
            // 2a) See if the line is at max size.  If it is, this
            //     customer turns away and leaves (is a "dropped" customer).
        }
        // 3) See if a customer is currently being serviced.
        //    One way to do this is to keep a counter such as
        //    'curCustomerTime', which is first set to serviceTime,
        //    then decremented each time through the loop at this point.
        //
        // 4) If a customer is NOT being serviced, it's time to get 
        //    the next customer from the line.  See if the line is
        //    non-empty.
        if (customerQueue.size() != 0) {
            // 4a) See how long they waited and record it
            // 4b) Get the next customer from the line, and keep a counter
            //     for how many were serviced.
        }
    }
}

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

int main() {
    int nServed;
    int totalWait;
    int totalLength;
    int totalDropped;

    string name;
    int simTime;
    double arrivalRate;
    int serviceTime;
    int maxLine;

    return 0;
}