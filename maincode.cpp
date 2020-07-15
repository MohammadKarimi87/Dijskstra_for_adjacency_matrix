/* Mohammad Karimi */
// Here, we develop a Dijkstra Algorithm in 3D
// we use adjacency matrix related to a graph extracted from an occupancy-grid
// the algorithm is developed based on "https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/" + https://autorob.org/lectures/autorob_02_graph_search.pdf

#include <cmath>
#include<limits>
#include <stdio.h>
#include<vector>
using namespace std;


/* FUNCTIONS FOR DIJKSTRA ALGORITHM*/

static int V; // Number of nodes in the graph which can be updated for each new graph
int minDistance(double dist[], bool visitQueue[])// A function to find the node with minimum travel time value,
{                                            // from the set of nodes not yet included in shortest path tree
 double min=numeric_limits<double>::max();// Initialize min value
 int min_index;
 for (int v=0; v<V; v++)
     if (visitQueue[v]==true && dist[v]<=min)
        min=dist[v], min_index=v;
 return min_index;
}

void printSolution(double dist[], int prntList[]) // A function to print the the solution, here we print only the shortest time from start to end nodes
{
for (int i=0;i<V;++i){
    printf("%.3f\t", dist[i]);
    printf("%i\n", prntList[i]);
}

}

void dijkstra(const vector<vector<double>> &graph, int src) // the function for dijkstra algorithm;
{                                                           // it takes adjacency matrix of a graph and prints the travel time of the shortest path
 double dist[V]; // shortest distance from start node to node i; in the end, we only keep the value to the end node
 bool sptSet[V]; // shortest path tree set: sptSet[i] will be true if node i is included in shortest path tree
 bool visitQueue[V];//update
 int prntList[V]; //update
 for (int i=0; i<V; i++) // // Initializing all distances as INFINITE and stpSet[] as false (meaning that the set is empty)
     dist[i] = numeric_limits<double>::max(), sptSet[i] = false, visitQueue[i] = false, prntList[i] = i; // INFINITE here is the max value that a double type can have
     visitQueue[0]=true;//update
     dist[src] = 0; // Distance of start node from itself is always 0

 for (int count=0; count<V-1;count++)// Finding the shortest path for all nodes
 {                                  // first, pick the minimum distance node from the set of node that are not yet processed.
  int u=minDistance(dist, visitQueue);
		// second, include u node in sptSet
  sptSet[u] = true;
  visitQueue[u]=false;
		// third, update the dist value of all the nodes adjacent to u
  for (int v=0; v<V; v++)
			// Update dist[v] only if is not included into sptSet
			// an edge from u to v exists,
			// and total distance/travel time of path from start to v nodes through u node is smaller than current value of dist[v]
  if (!sptSet[v] && graph[u][v] && dist[u]+graph[u][v]<dist[v]){
        dist[v]=dist[u]+graph[u][v];
        prntList[v]=u;//update
        visitQueue[v]=true;
               }
 }
 printSolution(dist,prntList); // print the solution
}
//####################################################### END OF THE FUNTIONS FOR DIJKSTRA ALGORITHM


int main()
{

/* GENERATING THE GRAPH*/
// we develop a 2D vector to define adjacency matrix representation
  vector<vector<double>> GRAPH={{0, 4, 0, 0, 0, 0, 0, 8, 0},
                                {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                {0, 0, 2, 0, 0, 0, 6, 7, 0}};


/* APPLYING DIJKSTRA ALGORITHM TO FIND SHORTEST PATH IN TERMS OF TRAVEL TIME */

    V=(GRAPH).size();
    dijkstra((GRAPH), 0);// calling for distera algorith to find the shortest path from start node to end node

return 0;
}
