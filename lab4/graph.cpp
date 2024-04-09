#include "graph.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <functional>
#include <vector>

using namespace std;

// implement classes' member functions here...

/* insert new edge */
void Graph::insert(int a, int b, double d, double s)
{
    // create edge with adjacent node
    NodeToEdge newEdgeA(b, d, s);
    NodeToEdge newEdgeB(a, d, s);

    // add node to graph
    addNode(a);
    addNode(b);

    // add NodeToEdge to vector at key a and b
    graph[a].push_back(newEdgeA);
    graph[b].push_back(newEdgeB);
}

/* insert all nodes and edges in the graph */
void Graph::load(string filename)
{
    // create ifstream object to read
    ifstream file(filename);
    int a, b;
    double d, s;

    // run insert function using parameters on each line
    while (file >> a >> b >> d >> s)
    {
        insert(a, b, d, s);
    }

    file.close();
}

/* change adjustment factor on the edge between a and b*/
bool Graph::traffic(int a, int b, double A)
{
    // check if nodes exist
    if (graph.find(a) != graph.end() && graph.find(b) != graph.end())
    {
        bool adjacent = false;

        // store vectors of adjacent nodes
        vector<NodeToEdge> &adjNodesA = graph[a];
        vector<NodeToEdge> &adjNodesB = graph[b];

        // loop through elements in vector
        for (int i = 0; i < adjNodesA.size(); i++)
        {
            // if b is adjacent to a
            if (adjNodesA[i].node == b)
            {
                adjNodesA[i].adjFactor = A; // change adjacency factor for b
                adjNodesA[i].travelTime = adjNodesA[i].distance / (adjNodesA[i].speedLimit * adjNodesA[i].adjFactor); // change travel time 

                // find a in adjacency list of b
                for (int j = 0; j < adjNodesB.size(); j++)
                {
                    // change adjacency factor for a
                    if (adjNodesB[j].node == a)
                    {
                        adjNodesB[j].adjFactor = A; // change adjacency factor for a 
                        adjNodesB[j].travelTime = adjNodesB[j].distance / (adjNodesB[j].speedLimit * adjNodesB[j].adjFactor); // change travel time 
                    }
                }

                return true;
            }
        }

        return false;
    }

    return false;
}

void Graph::update(string filename)
{
    bool isUpdated = false;

    // create ifstream object to read
    ifstream file(filename);
    int a, b;
    double A;

    // run traffic function using parameters on each line
    while (file >> a >> b >> A)
    {
        // at least one adjustment factor is updated
        if (traffic(a, b, A))
        {
            isUpdated = true;
        }
    }

    file.close();

    if (isUpdated)
    {
        cout << "success" << endl;
    }
    else
    {
        cout << "failure" << endl;
    }
}

/* print all adjacent nodes */
void Graph::print(int a)
{
    // check if node a exists
    if (graph.find(a) != graph.end())
    {
        vector<NodeToEdge> &adjNodes = graph[a]; // store vector of adjacent nodes

        // loop through vector
        for (int i = 0; i < adjNodes.size(); i++)
        {
            cout << adjNodes[i].node << " "; // print adjacent nodes
        }

        cout << endl;

        return; 
    }

    cout << "failure" << endl;
}

/* delete vertex a and it's edges*/
void Graph::del(int a)
{
    // check if node a exists
    if (graph.find(a) != graph.end())
    {
        vector<NodeToEdge> &adjNodesA = graph[a]; // store vector of adjacent nodes

        // loop through vector
        for (int i = 0; i < adjNodesA.size(); i++)
        {
            vector<NodeToEdge> &adjNodesB = graph[adjNodesA[i].node]; // store vector of adjacent nodes of adjacent node

            // loop through vector
            for (int j = 0; j < adjNodesB.size(); j++)
            {
                // if adjacent node is a
                if (adjNodesB[j].node == a)
                {
                    adjNodesB.erase(adjNodesB.begin() + j); // erase adjacent node a
                    break;
                }
            }
        }

        graph.erase(a); // delete node a

        cout << "success" << endl;

        return; 
    }

    cout << "failure" << endl;
}

void Graph::path(int a, int b)
{
    pair<double, queue<int>> shortestPair; 

    Dijkstra(a, b, shortestPair); // get shortest path using Dijkstra's algorithm

    queue<int> shortestPath = shortestPair.second; 

    // failed if no paths to noes
    if(shortestPath.empty()){
        cout << "failure" << endl; 
        return; 
    }

    // loop through path
    while(!shortestPath.empty()){
        cout << shortestPath.front() << " "; 

        shortestPath.pop(); // remove element to go to next element 
    }

    cout << endl; 
}

/* print the weight of the shortest path */
void Graph::lowest(int a, int b)
{
    pair<double, queue<int>> shortestPair;  

    Dijkstra(a, b, shortestPair); // get shortest path using Dijkstra's algorithm

    queue<int> shortestPath = shortestPair.second;

    // failed if no path to nodes 
    if(shortestPath.empty()){
        cout << "failure" << endl; 
        return; 
    }

    cout << shortestPair.first << endl;
}

/* helper functions */

/* add node to graph if node doesn't exist */
void Graph::addNode(int a)
{
    if (graph.find(a) == graph.end())
    {
        graph[a] = vector<NodeToEdge>{};
    }
}

struct ComparePair {
    bool operator()(const pair<double, queue<int>>& lhs, const pair<double, queue<int>>& rhs) const {
        return lhs.first > rhs.first; // Compare based on the first element (weight)
    }
};

/* perform Dijkstra's algorithm */
void Graph::Dijkstra(int from, int to, pair<double, queue<int>> &shortestPair){
    priority_queue<pair<double, queue<int>>, vector<pair<double, queue<int>>>, ComparePair> todo;
    unordered_set<int> visited; 

    // push path [from] into stack 
    todo.push({0, queue<int>({from})});

    while(!todo.empty()){
        // get weight and next node in path
        pair<double, queue<int>> currentPair = todo.top(); 
        double currentWeight =  currentPair.first;
        queue<int> currentPath = currentPair.second; 
        int currentNode = currentPath.back(); 
        todo.pop(); 

        if(currentNode == to){
            shortestPair = currentPair; 
            return; 
        }

        if(visited.find(currentNode) == visited.end()){
            visited.insert(currentNode); 

            vector<NodeToEdge> &adjNodes = graph[currentNode];

            for(int i = 0; i < adjNodes.size(); i++){
                queue<int> newPath = currentPath;

                newPath.push(adjNodes[i].node);

                if(adjNodes[i].adjFactor != 0){
                    todo.push({currentWeight + adjNodes[i].travelTime, newPath});
                }
            }
        }
    }

    return;
}