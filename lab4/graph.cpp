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
    queue<int> shortestPath; 

    Dijkstra(a, b, shortestPath); // get shortest path using Dijkstra's algorithm

    cout << "here"; 

    if(shortestPath.empty()){
        cout << "empty" << endl; 
    }

    // loop through path
    while(!shortestPath.empty()){
        cout << shortestPath.front() << " "; 

        shortestPath.pop(); // remove element to go to next element 
    }

    cout << endl; 
}

void Graph::lowest(int a, int b)
{
    queue<int> shortestPath; 
    double weight = 0; 

    Dijkstra(a, b, shortestPath); // get shortest path using Dijkstra's algorithm

    int prevKey = a; // set previous key to first node in path 
    shortestPath.pop(); // go to next node in path 

    // loop through path
    for(int i = 0; i < shortestPath.size() - 1; i++){
        int currKey = shortestPath.front(); 
        vector<NodeToEdge> adjNodes = graph[prevKey];
        
        // loop through vector of adjacent nodes 
        for(int j = 0; j < adjNodes.size(); i++){
            // find adjacent edge between previous node and current node
            if(adjNodes[j].node == currKey){
                weight += adjNodes[j].distance / (adjNodes[j].speedLimit * adjNodes[j].adjFactor); // calculate current weight
                break; 
            }
        }

        prevKey = currKey; // set previous key to current key
        shortestPath.pop(); // remove element to go to next element
    }

    cout << weight << endl; 
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

/* perform Dijkstra's algorithm */
void Graph::Dijkstra(int from, int to, queue<int> &shortestPath){
    priority_queue<pair<double, queue<int>>> todo;
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
            shortestPath = currentPath; 
            return; 
        }

        if(visited.find(currentNode) == visited.end()){
            visited.insert(currentNode); 

            vector<NodeToEdge> &adjNodes = graph[currentNode];

            for(int i = 0; i < adjNodes.size(); i++){
                queue<int> newPath = currentPath;
                newPath.push(adjNodes[i].node);
                todo.push({currentWeight + adjNodes[i].travelTime, currentPath});
            }
        }
    }

    return;
}