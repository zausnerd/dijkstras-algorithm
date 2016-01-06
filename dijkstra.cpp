#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>
#include "dijkstra.h"

using namespace std;


AdjVertex::AdjVertex(int name_, double weight_):
    name(name_), weight(weight_) {}
    
int DijkstraVertex::getPrevious() const {
    return previous;
}
        
void DijkstraVertex::setPrevious(int value) {
    previous = value;
}

double DijkstraVertex::getDistance() const {
    return distance;
}

void DijkstraVertex::setDistance(double value) {
    distance = value;
}

bool DijkstraVertex::operator<(const DijkstraVertex& b) const {
    return distance > b.distance;
}

bool DijkstraVertex::known() const {
    return isKnown;
}

int DijkstraVertex::getName()  const {
    return name;
}
void DijkstraVertex::setName(int value) {
    name = value;
}
void DijkstraVertex::setKnown(bool value) {
    isKnown = value;
}

DijkstraVertex::DijkstraVertex(): 
        distance(1000000), isKnown(false) {}


map<int, vector<AdjVertex>> gatherInput(string fileName) {
    int numNodes; int name; double weight; int nodeKey;
    map<int, vector<AdjVertex>> adjacencyList;
    ifstream inputStream;
    inputStream.open(fileName);
    if (inputStream.is_open()) {
        inputStream >> numNodes;
        for(int node = 0; node < numNodes; node++) {
            vector<AdjVertex> adjListVector;
            inputStream >> nodeKey;
            inputStream >> name;
            while (name != -1) {
                inputStream >> weight;
                adjListVector.push_back(AdjVertex(name,weight));
                inputStream >> name;
            }
            adjacencyList[nodeKey] = adjListVector;
        }
    }
    else {
        cout << "Valid file not found !\n";
    }
    return adjacencyList;
}

void dijkstra(map<int, vector<AdjVertex>> adjacencyList, int start) {
    int currentVertex = start;
    map<int, DijkstraVertex> vertexMap;
    for (unsigned int i = 0; i < adjacencyList.size(); i++) {
        vertexMap[i] = DijkstraVertex();
        vertexMap[i].setName(i);
    }
    vertexMap[currentVertex].setPrevious(start);
    vertexMap[currentVertex].setDistance(0);
    vertexMap[currentVertex].setKnown(true);
    priority_queue<DijkstraVertex> pq;
    pq.push(vertexMap[currentVertex]);
    while (pq.size() > 0) {
        currentVertex = pq.top().getName();
        pq.pop();
        for (auto vertex : adjacencyList[currentVertex]) {
            if (!vertexMap[vertex.name].known()) {
                vertexMap[vertex.name].setDistance(vertex.weight + vertexMap[currentVertex].getDistance());
                vertexMap[vertex.name].setPrevious(currentVertex);
                vertexMap[vertex.name].setKnown(true);
                pq.push(vertexMap[vertex.name]);
                
            }
            else {
                if (vertexMap[vertex.name].getDistance() > vertexMap[currentVertex].getDistance() + vertex.weight) {
                    vertexMap[vertex.name].setDistance(vertexMap[currentVertex].getDistance() + vertex.weight);
                    vertexMap[vertex.name].setPrevious(currentVertex);
                }
            }
        }
    }
    printPaths(vertexMap,start);
}

void printPaths(map<int, DijkstraVertex> vertexMap, int start) {
    for (auto e : vertexMap) {
        if (e.second.known()) {
            cout << "vertex: " << e.second.getName() << endl << "cost from " 
                 << start << ": " << e.second.getDistance() << endl
                 << "previous : " << e.second.getPrevious() << endl 
                 << "path from " << start << " - " << e.first << ":  "; 
            stack<int>path;
            if (e.second.getName() != start) {
                path.push(e.second.getName());
                int nextVal = e.second.getPrevious();
                while (nextVal != start) {
                    path.push(nextVal);
                    nextVal = vertexMap[nextVal].getPrevious();
                }
                path.push(start);
                while (path.size() > 0) {
                    cout << path.top() << " ";
                    path.pop();
                }
                cout << endl << endl;
            }
            else {
                cout << start << endl << endl;
            }
        }    
    }       

}
