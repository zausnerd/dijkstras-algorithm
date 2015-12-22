#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
#include "dijkstra.h"
using namespace std;


int main(int argc, const char * argv[])
{
    string fileName;
    double inputVal;
    if (argc <= 2) {
        cout << "Not enough arguments, exiting \n";
    }
    else {
        inputVal = atof(argv[2]);
        fileName = argv[1];
        map<int, vector<AdjVertex>> adjacencyList = gatherInput(fileName);
        if (adjacencyList.size() == 0) {
            cout << "No nodes in file? :( \n";
        }
        
        else {
            int largestInput = adjacencyList.size() - 1;
            while (inputVal != -1) {
                if (inputVal < -1 || inputVal > largestInput) {
                    cout << "Hey that's not valid, chief \n";    
                }
                else if (inputVal == -1) {
                    cout << "ok boss, I'll see you later. \n";
                }
                else {
                    cout << "It's time to Dance Dance Dijkstra!! \n";
                    dijkstra(adjacencyList,inputVal);
                }
                if (inputVal != -1) {
                    cout << "Please enter the starting value, -1 to exit \n";
                    cin >> inputVal;   
                }
            }
        }
    }
    return 0;
}
