/* Mohammad Karimi */
//OTTO code challenge description:
// First, we convert the challenge to a graph; including waypoints as the nodes and adding start and end nodes as well
// Second, we construct the adjacency matrix for the graph based on the rules mentioned in the challenge:
// 1) uni-directional movements 2) adding penalty (in seconds) to the edges if skip any waypoint nodes
// Third, we developed the Dijkstra's algorithm to find the shortest time from start node to the end node using the adjacency matrix

#include <cmath>
#include<limits>
#include <stdio.h>
#include<vector>
using namespace std;


/* FUNCTIONS FOR DIJKSTRA ALGORITHM*/

static int V; // Number of nodes in the graph which can be aupdated for each new graph
int minDistance(double dist[], bool sptSet[])// A function to find the node with minimum travel time value,
{                                            // from the set of nodes not yet included in shortest path tree
 double min=numeric_limits<double>::max();// Initialize min value
 int min_index;
 for (int v=0; v<V; v++)
     if (sptSet[v]==false && dist[v]<=min)
        min=dist[v], min_index=v;
 return min_index;
}

void printSolution(double dist[]) // A function to print the the solution, here we print only the shortest time from start to end nodes
{
 printf("%.3f\n", dist[V-1]);
}

void dijkstra(const vector<vector<double>> &graph, int src) // the function for dijkstra algorithm;
{                                                           // it takes adjacency matrix of a graph and prints the travel time of the shortest path
 double dist[V]; // shortest distance from start node to node i; at the ned we only keep the value to the end node
 bool sptSet[V]; // shortest path tree set: sptSet[i] will be true if node i is included in shortest path tree
 for (int i=0; i<V; i++) // // Initializing all distances as INFINITE and stpSet[] as false (meaning that the set is empty)
     dist[i] = numeric_limits<double>::max(), sptSet[i] = false; // INFINITE here is the max value that a double type can have
     dist[src] = 0; // // Distance of start node from itself is always 0
 for (int count=0; count<V-1;count++)// Finding the shortest path for all nodes
 {                                  // first, pick the minimum distance node from the set of node that are not yet processed.
  int u=minDistance(dist, sptSet);
		// second, include u node in sptSet
  sptSet[u] = true;
		// third, update the dist value of all the nodes adjacent to u
  for (int v=0; v<V; v++)
			// Update dist[v] only if is not included into sptSet
			// an edge from u to v exists,
			// and total distance/travel time of path from start to v nodes through u node is smaller than current value of dist[v]
  if (!sptSet[v] && graph[u][v] && dist[u]+graph[u][v]<dist[v])
      dist[v]=dist[u]+graph[u][v];
  }
 printSolution(dist); // print the solution
}
//####################################################### END OF THE FUNTIONS FOR DIJKSTRA ALGORITHM


int main()
{
/*GETTING INPUTS AND GENERATING GRAPH FOR ALL THE TEST CASES */

/* GETTING INPUTS USING STDIO */
int N[500];// the number of waypoints for all the test cases, saved in array N
int wp[500][1000][3]; // waypoints saved in a 3D array [testcase_number][number_of_waypoints_for_each_case]
                      //[X_coordinate Y_coordiante Penalty_if_being_avoided]
char wspace;//white space character between the numbers in data entry rows
int tstCsCo=0; // initializing counter for the test cases (tesCasesCounter)
//A DO-WHILE LOOP TO GET DATAT
do {
   scanf("%d", &N[tstCsCo]);// get number of waypoints
   if (N[tstCsCo]==0) // if you enter the number 0, it will finish getting inputs
      break;
   else {
      N[tstCsCo]+=2; // adding two more nodes
      for (int wps=0;wps<N[tstCsCo];wps++){ //itirating through the next N[i] rows to get the way points and their penalty values
      //we add two more nodes to the waypoints to inlcude start (0,0) and goal (100,100) points for all the test cases
          if (wps==0){// adding start node
             wp[tstCsCo][wps][0]=0;
             wp[tstCsCo][wps][1]=0;
             wp[tstCsCo][wps][2]=100;
           }
          else if (wps==N[tstCsCo]-1){// adding end node
             wp[tstCsCo][wps][0]=100;
             wp[tstCsCo][wps][1]=100;
             wp[tstCsCo][wps][2]=100;
           }
          else {
              for (int j=0;j<3;j++){//itirating to get x y penalty; should skip the first row of all the cases to include the starts waypoint later
                  scanf("%d,%c", &wp[tstCsCo][wps][j], &wspace);
               }
           }
        }
 tstCsCo++;
   }
 } while(true);
//############################################## END OF GETTING INPUTS

/* GENERATING THE GRAPH*/
// we develop a 2D vector to define adjacency matrix representation and put each graph in an element of an array
vector<vector<double>> GRAPHS[tstCsCo]; // creating an array of 2D vectors,
for (int ii=0; ii<tstCsCo; ii++){
// initializing the graphs; zero means there is no edge between the corrrosponding nodes
    GRAPHS[ii].resize(N[ii]);
    for (int iii=0; iii<N[ii]; iii++){
         for (int jjj=0; jjj<N[ii]; jjj++){
             (GRAPHS[ii])[iii].push_back(0);// initializing with zero, meaning that there is no edge between nodes at the begining
          }
     }
 }

// update the edges due to the OTTO rules: 1) uni-directional movements 2) adding penalty (in seconds) to the edges if skip any waypoint nodes
for (int ii=0; ii<tstCsCo; ii++){
    for (int iii=0; iii<N[ii]; iii++){
        for (int jjj=0; jjj<N[ii]; jjj++){
            if ((jjj-iii)==1){ // if OTTO travels from waypoint iii to iii+1, the cost will be travel time + 10 seconds loading
               double TT=sqrt(pow((wp[ii][iii][0]-wp[ii][jjj][0]),2)+pow((wp[ii][iii][1]-wp[ii][jjj][1]),2))/2;//dist/speed
               (GRAPHS[ii])[iii][jjj]=TT+10;
             }
            else if ((jjj-iii)>1){// if OTTO skips some waypoints, the cost is penalties + travel time
               double TT=sqrt(pow((wp[ii][iii][0]-wp[ii][jjj][0]),2)+pow((wp[ii][iii][1]-wp[ii][jjj][1]),2))/2;//dist/speed
               double penals=0;
               for (int ij=iii+1; ij<jjj; ij++){
                    penals+=static_cast<double>(wp[ii][ij][2]);
                }
               (GRAPHS[ii])[iii][jjj]=TT+penals+10;
             }
          }
       }
 }
// ################################################# END OF INITILAIZING AND GRAPH GENERATION

/* APPLYING DIJKSTRA ALGORITHM TO FIND SHORTEST PATH IN TERMS OF TRAVEL TIME */
for (int ii=0; ii<tstCsCo; ii++){
    V=(GRAPHS[ii]).size();//iterate to solve for each test case according to the corresponding graph
    dijkstra((GRAPHS[ii]), 0);// calling for distera algorith to find the shortest path from start node to end node
 }
return 0;
}
