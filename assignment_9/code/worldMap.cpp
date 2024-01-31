#include "worldMap.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

WorldMap::WorldMap() {}

void WorldMap::createWorldMap(string fileName) {
    //Open txt file
    ifstream file;
    file.open(fileName);

    //Grab first line containing the dimensions of the chart
    string dimensions;
    getline(file, dimensions);
    stringstream str(dimensions);

    //Breaks the string of two dimensions into the x and y dimensions
    string dimension;
    getline(str, dimension, ' ');
    rows = stoi(dimension);
    getline(str, dimension, ' ');
    cols = stoi(dimension);

    //Creates the worldMap array
    worldMap = new int*[rows];
    for (int i = 0; i < rows; i++) {
        worldMap[i] = new int[cols];
    }

    //Assigns the region values from the text file to the worldMap
    for (int i = 0; i < cols; i++) {
        string Row;
        getline(file, Row);
        stringstream islands(Row);

        for (int j = 0; j < rows; j++) {
            string island;
            getline(islands, island, ' ');
            worldMap[j][i] = stoi(island);
        }
    }
}

void WorldMap::printWorldMap() {
    //Prints a formated version of the worldMap
    for (int i = 0; i < cols; i++) {
        cout << "|";
        for (int j = 0; j < rows; j++) {
            cout << " " << worldMap[j][i] << " |";
        }
        cout << endl;
    }
}

void WorldMap::addRegion(int x, int y) {
    for (auto region : regions) {
        if (region->x == x && region->y == y) {
            return;
        }
    }
    Region* temp = new Region();
    temp->x = x;
    temp->y = y;
    regions.push_back(temp);
}

bool checkIfEdgeExists(Region *r, int x2, int y2) {
    for (auto neighbor : r->neighbors) {
        if (neighbor.region->x == x2 && neighbor.region->y == y2) {
            return true;
        }
    }
    return false;
}

void WorldMap::addEdgeBetweenRegions(int x1, int y1, int x2, int y2) {
    // TODO START
    for (unsigned int i = 0; i < regions.size(); i++)
    {
        if (regions[i]->x == x1 && regions[i]->y == y1)
        {
            for (unsigned int j = 0; j < regions.size(); j++)
            {
                if (i != j && regions[j]->x == x2 && regions[j]->y == y2)
                {
                    if (!checkIfEdgeExists(regions[i], x2, y2))
                    {
                        NeighboringRegion av;
                        av.region = regions[j];
                        regions[i]->neighbors.push_back(av);
                        // another vertex for edge in other direction
                        NeighboringRegion av2;
                        av2.region = regions[i];
                        regions[j]->neighbors.push_back(av2);
                    }
                }
            }
        }
    }
    // TODO END
}

vector<vector<int>> WorldMap::findAdjacentLandRegions(int x, int y) {
    // TODO START
    // identify the open paths that are adjacent to the vertex at x, y
    // fill adjArr array with the numbers of the adjacent vertices
    vector<vector<int>> neighbors;
    for (int i = x - 1; i <= x + 1; i++)
    {
        if (i < 0 || i >= this->rows)
        {
            continue;
        }
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (j < 0 || j >= this->cols)
            {
                continue;
            }
            // if there is an open path at this adjacent position, add to adjArray
            if (!(i == x && j == y) && worldMap[i][j] == 1)
            {
                neighbors.push_back({i, j});
            }
        }
    }
    return neighbors;
    // TODO END
}

void WorldMap::convertWorldMapToAdjacencyListGraph() {
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (worldMap[j][i] == 1) {
                    addRegion(i,j);
            }

        }
    }
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if (worldMap[j][i] == 1) {
                    for (auto neighbor : findAdjacentLandRegions(i,j)) {
                        addEdgeBetweenRegions(i, j, neighbor[0], neighbor[1]);
                    }
            }

        }
    }
}

// helper function to check if v2 is a neighbor of verter v1
bool isNeighbor(int x1, int y1, int x2, int y2, const vector<Region *> regions) {
    for (auto region : regions) {
        if (region->x == x1 && region->y == y1) {
            for (auto neighbor: region->neighbors) {
                if (neighbor.region->x == x2 && neighbor.region->y == y2) {
                    return true;
                }
            }
        }
    }
    return false;
}

WorldMap::~WorldMap() {
    for (int i = 0; i < rows; i++) {
        delete[] worldMap[i];
    }
    delete[] worldMap;

    regions.clear();
    regions.shrink_to_fit();

    rows = 0;
    cols = 0;
}

void WorldMap::displayEdges() {
    for (auto region : regions) {
        cout << "(" << region->x << "," << region->y << ")" << " --> ";
        for (auto neighbor : region->neighbors) {
            cout << "(" << neighbor.region->x << "," << neighbor.region->y << ") ";
        }
        cout << endl;
    }
}

// HELPER FOR findNumOfIslands
void findNumOfIslandsHelper(Region *r) {
    r->visited = true;

    for(auto neighbor : r->neighbors) {
        if (!neighbor.region->visited) {
            findNumOfIslandsHelper(neighbor.region);
        }
    }
}

int WorldMap::findNumOfIslands() {
    int numIslands = 0;
    for (auto region : regions) {
        if (!region->visited) {
            findNumOfIslandsHelper(region);
            numIslands++;
        }
    }
    return numIslands;
}

vector<Region *> &WorldMap::getRegions() {
    return regions;
}
