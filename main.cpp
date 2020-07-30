/* Mohammad Karimi */
// Here, we develop a Dijkstra Algorithm
// we use adjacency matrix related to a graph extracted from an occupancy-grid

#include <cmath>
#include<limits>
#include <stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

static int V; // Number of nodes in the graph which can be updated for each new graph
struct Node
{
    double dist=numeric_limits<double>::max();// shortest distance from the source
    int index;
    int parent=0; // parent of the node in the path tree
};
bool compare(const Node &n1, const Node &n2){ //compare function to sort nodes based on the smallest shortest path
return n1.dist<n2.dist;
}

bool findNotExist(const vector<Node> &sptSet, const Node &v )
{
  for(int i=0;i<static_cast<int>(sptSet.size());++i)
  { if (sptSet[i].index==v.index)
  return false;
  }
  return true;
}

void printSolution(const vector<Node> &nodes) // A function to print the the solution, here we print only the shortest time from start to end nodes
{
    printf("%s\t\t", "node index");	
    printf("%s\t\t", "shortest distance"); // the shortest distance from source to that node
    printf("%s\n", "parent index");
for (int i=0;i<V;++i){
	
    printf("%i\t\t\t", i);	
    printf("%.3f\t\t\t\t", nodes[i].dist); // the shortest distance from source to that node
    printf("%i\n", nodes[i].parent);// the parents
  }
}

void dijkstra(const vector<vector<double>> &graph, int src) // the function for dijkstra algorithm; src is the source node
{
V=(graph).size();
vector<Node> nodes{};
nodes.resize(V);
for (int i=0;i<V;++i){
      nodes[i].index=i;
     }
 nodes[src].dist=0;
 vector<Node> sptSet{}; // shortest path tree set: sptSet[i] will be true if node i is included in shortest path tree
 vector<Node> visitQueue{nodes[src]};
 for (int count=0; count<V-1;count++)// Finding the shortest path for all nodes
 {                                  // first, pick the minimum distance node from the set of node that are not yet processed.
  //sort the visitQueue based on the dist value
sort(visitQueue.begin(), visitQueue.end(), compare);
  //select the one has min dist
   Node u=visitQueue[0];
   sptSet.push_back(u);
		// second, include u node in sptSet
   visitQueue.erase(visitQueue.begin());
		// third, update the dist value of all the nodes adjacent to u
  for (int v=0; v<V; v++)
			// Update dist[v] only if is not included into sptSet
			// an edge from u to v exists,
			// and total distance/travel time of path from start to v nodes through u node is smaller than current value of dist[v]
  if (findNotExist(sptSet, nodes[v]) && graph[u.index][nodes[v].index] && u.dist+graph[u.index][nodes[v].index]<nodes[v].dist){
        nodes[v].dist=u.dist+graph[u.index][nodes[v].index];
        nodes[v].parent=u.index;
        visitQueue.push_back(nodes[v]);
               }
 }
 printSolution(nodes); // print the solution
}
//####################################################### END OF THE FUNTIONS FOR DIJKSTRA ALGORITHM



int main(){
vector<vector<double>> GRAPH{   {0, 4, 0, 0, 0, 0, 0, 8, 0},
                                {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                {0, 0, 2, 0, 0, 0, 6, 7, 0}};

dijkstra((GRAPH), 0);
return 0;}

