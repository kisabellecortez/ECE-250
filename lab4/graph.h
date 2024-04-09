#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;
// define your classes here...

/* store edge with corresponding adjacent node*/
class NodeToEdge
{
public:
    int node;
    double distance;
    double speedLimit;
    double adjFactor;
    double travelTime; 

    NodeToEdge(int n, double d, double s) : node{n}, distance{d}, speedLimit{s}, adjFactor{1} {
        travelTime = distance / (speedLimit * adjFactor);
    };
};

class Graph
{
private:
    unordered_map<int, vector<NodeToEdge>> graph; 

public: 
    Graph(){};
    ~Graph(){};

    /* lab functions */
    void insert(int a, int b, double d, double s);
    void load(string filename);
    bool traffic(int a, int b, double A);
    void update(string filename);
    void print(int a);
    void del(int a);
    void path(int a, int b);
    void lowest(int a, int b);

    /* helper functions */
    void addNode(int a); 
    void Dijkstra(int from, int to, pair<double, queue<int>> &shortestPair);
};