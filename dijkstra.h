#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>

using namespace std;

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

struct AdjVertex
{
    int name;
    double weight;
    AdjVertex(int name_, double weight_);
    
};

class DijkstraVertex
{
    private:
        int name;
        double distance;
        int previous;
        bool isKnown;
    public:
        int getPrevious() const;
        void setPrevious(int value);
        double getDistance() const;
        void setDistance(double value);
        bool operator<(const DijkstraVertex& b) const;
        bool known() const;
        int getName()  const;
        void setName(int value);
        void setKnown(bool value);
        DijkstraVertex();
};

map<int, vector<AdjVertex>> gatherInput(string fileName);

void dijkstra(map<int, vector<AdjVertex>> adjacencyList, int start);

void printPaths(map<int, DijkstraVertex> vertexMap, int start);
#endif