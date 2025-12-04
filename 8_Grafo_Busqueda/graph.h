#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <vector>
#include <stack>
#include <queue>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

using std::vector;
using std::queue;
using std::string;
using std::stringstream;
using std::stack;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjList, adjMat;

    // Helper recursivo para DFS
    void dfsHelper(int,int, vector<bool>&, vector<int>&,
        vector<int>&, bool&);
public:
    Graph();

    void loadGraphList(string,int);
    void loadGraphMat(string,int,int);

    string printAdjList();
    string printAdjMat();

    string DFS(int,int);
    string BFS(int,int);
};

// IMPLEMENTANDO

Graph::Graph() : vertices(0) {}

void Graph::loadGraphList(string dt, int n) {
    vertices = n;
    // Crea la lista de adyacencia, a c/vértice un vector vacío
    adjList.assign(vertices, vector<int>());

    stringstream ss(dt);
    char NoValor;
    int u,v;

    // Mientras pueda descomponerse el fljo en estos componentes...
    while (ss >> NoValor >> u >> NoValor >> v >> NoValor) {   
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // ordenar para que el recorrido sea de menor a mayor
    for (auto &list:adjList) std::sort(list.begin(), list.end());
}

void Graph::loadGraphMat(string dt, int rows, int cols) {
    vertices = rows;
    adjMat.assign(vertices, vector<int>(vertices, 0));

    stringstream ss(dt);
    char NoValor;
    int u, v;

    while (ss>>NoValor>>u>>NoValor>>v>>NoValor) {
        adjMat[u][v] = adjMat[v][u] = 1;
    }
}

string Graph::printAdjList() {
    stringstream ss;
    for (int i = 0; i < vertices; ++i) {
        ss << "vertex " << i << " : ";
        for (size_t j = 0; j < adjList[i].size(); ++j) {
            ss << adjList[i][j];
            if (j + 1 < adjList[i].size()) ss << " ";
        }
        ss << " "; 
    }
    return ss.str();
}

string Graph::printAdjMat() {
    stringstream ss;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            ss << adjMat[i][j] << " ";
        }
    }
    return ss.str();
}


string Graph::DFS(int start, int goal) {
    vector<bool> visited(vertices, false);
    vector<int> parent(vertices, -1), visitOrder;
    bool found = false;

    // Llamada recursiva
    dfsHelper(start, goal, visited, parent, visitOrder, found);

    // Construcción del string de salida
    // Formato esperado: "visited: 0 1 2 3 path: 0 1 3"
    
    stringstream ssVisited;
    for (int v : visitOrder) {
        ssVisited << v << " ";
    }

    // Reconstruir camino desde el goal hacia atrás usando parent
    vector<int> path;
    int curr = goal;
    // Reconstruimos si encontramos el goal, o si el goal es el start
    if (found) {
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        std::reverse(path.begin(), path.end());
    }

    stringstream ssPath;
    for (size_t i = 0; i < path.size(); ++i) {
        ssPath << path[i];
        if (i + 1 < path.size()) ssPath << " ";
    }

    return "visited: " + ssVisited.str() + "path: " + ssPath.str();
}

void Graph::dfsHelper(int curr, int goal, vector<bool>& visited,
    vector<int>& parent, vector<int>& visitOrder, bool& found) {
    // Si ya encontramos el objetivo en otra rama, parar
    if (found) return;

    visited[curr] = true;
    visitOrder.push_back(curr);

    if (curr == goal) {
        found = true;
        return;
    }

    // Recorrer vecinos YA ESTÁN ORDENADOS en loadGraphList
    for (int neigh : adjList[curr]) {
        if (!visited[neigh]) {
            parent[neigh] = curr;
            dfsHelper(neigh,goal,visited,parent,visitOrder,found);
            // Si fue encontrado, tras la recursión cortar el ciclo
            if (found) return; 
        }
    }
}

// IMPLEMENTACIÓN DE BFS
string Graph::BFS(int start, int goal) {
    vector<bool> visited(vertices, false);
    vector<int> parent(vertices, -1);
    queue<int> q;

    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    vector<int> order;                
    order.push_back(start);

    bool found = false;
    while (!q.empty() && !found) {
        int curr = q.front(); q.pop();
        
        if (curr == goal) {
            found = true;
            break; 
        }

        for (int neigh : adjList[curr]) {
            if (!visited[neigh]) {
                visited[neigh] = true;
                parent[neigh] = curr;
                q.push(neigh);
                order.push_back(neigh);
                
                if (neigh == goal) {
                    found = true;
                    break; 
                }
            }
        }
    }

    vector<int> path;
    if (found) {
        for (int at = goal; at != -1; at = parent[at])
            path.push_back(at);
        std::reverse(path.begin(), path.end());
    }

    stringstream ssVisited, ssPath;
    for (int v : order) ssVisited << v << " ";
    for (size_t i = 0; i < path.size(); ++i) {
        ssPath << path[i];
        if (i + 1 < path.size()) ssPath << " ";
    }

    return "visited: " + ssVisited.str() + "path: " + ssPath.str();
}

#endif