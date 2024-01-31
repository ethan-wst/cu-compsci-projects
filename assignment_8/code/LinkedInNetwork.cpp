#include "LinkedInNetwork.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void LinkedInNetwork::addProfessional(string name){
    if (getProfessional(name)) {
        cout << name << " found." << endl;
    } else {
        professionals.push_back(new Professional(name));
    }
}

void LinkedInNetwork::addConnection(string v1, string v2){
    Professional* from = getProfessional(v1);
    Professional* to = getProfessional(v2);

    if (from && to) {
        for (auto neighbor : from->neighbors) {
            if (neighbor.v == to) {
                cout << "Edge already exists" << endl;
                return;
            }
        }
        from->neighbors.push_back(neighbor(to));
        to->neighbors.push_back(neighbor(from));
    }
   
}

void LinkedInNetwork::displayConnections(){
    for (auto professional : professionals) {
        cout << professional->name << " --> ";
        for (auto neighbor : professional->neighbors) {
            cout << neighbor.v->name << " ";        
        }
        cout << endl;
    }
}

void LinkedInNetwork::breadthFirstTraverse(string sourceProfessional){
    Professional* src = getProfessional(sourceProfessional);
    if (src) {
        eraseMarks();
        cout << "Starting Professional (root): " << src->name << "-> ";
        queue<Professional*> pq;
        src->visited = true;
        src->connectionOrder = 0;
        pq.push(src); 

        while (!pq.empty()) {
            Professional* p = pq.front();
            pq.pop();
            for (auto neighbor : p->neighbors) {
                if (!neighbor.v->visited) {
                    neighbor.v->visited = true;
                    neighbor.v->connectionOrder = p->connectionOrder + 1;
                    cout << neighbor.v->name << "(" << neighbor.v-> connectionOrder << ") ";
                    pq.push(neighbor.v);
                }
            }
        }
    }
}

void bfs_helper(Professional* src, vector<Professional*> &professionals) {
    if (src) {
        queue<Professional*> pq;
        src->visited = true;
        src->connectionOrder = 0;
        pq.push(src); 

        while (!pq.empty()) {
            Professional* p = pq.front();
            pq.pop();
            for (auto neighbor : p->neighbors) {
                if (!neighbor.v->visited) {
                    neighbor.v->visited = true;
                    neighbor.v->connectionOrder = p->connectionOrder + 1;
                    pq.push(neighbor.v);
                }
            }
        }
    }
}

vector<string> LinkedInNetwork::suggestProfessionalsWithinKthOrder(string professionalName, int k){
    vector<string> professionalsWithinK;
    Professional* source = getProfessional(professionalName);
    bfs_helper(source, professionals);

    for (auto professional : professionals) {
        if (professional->connectionOrder <= k && professional->visited && professional->name != professionalName) {   
            professionalsWithinK.push_back(professional->name);       
        }
    } 
    
    return professionalsWithinK;
}

Professional* LinkedInNetwork::getProfessional(string name) {
    for (auto professional : professionals) {
        if (professional->name == name) {
            return professional;
        }
    }
    return nullptr;
}

void LinkedInNetwork::eraseMarks() {
    for (auto professional : professionals) {
        professional->visited = false;
        professional->connectionOrder = 0;
    }
}