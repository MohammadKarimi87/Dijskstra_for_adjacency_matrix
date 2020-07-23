#include<iostream>
#include<vector>
#include<limits>
#include<cmath>

using namespace std;

typedef float xyz_t;

struct Map{
xyz_t width; /* X coordinate */
xyz_t length; /* Y coordinate */
xyz_t height; /* Z coordinate */
xyz_t resolution; /* the size of the grids*/
};

struct Node
{
    int index;
    xyz_t x;
    xyz_t y;
    xyz_t z;
    xyz_t dist=numeric_limits<xyz_t>::max();//distance to the
    int parent=0;
    vector<int> nbrIndexs;
    vector<int> nbrCost;
};


int main(){
Map myMap{40,40,40,.86}; // select the size of th emap
xyz_t eps=myMap.resolution/100;

int dimention[3]={static_cast<int>(myMap.width/myMap.resolution)+1,static_cast<int>(myMap.length/myMap.resolution)+1,static_cast<int>(myMap.height/myMap.resolution)+1};
int N; //the number of total nodes
N=(dimention[0])*(dimention[1])*(dimention[2]);
cout<<N<<'\n';

vector<Node> nodes{};
nodes.resize(N);
vector<vector<int>> XYBounds;

int count_nodes=0;
for (int i = 0; i < dimention[0]; ++i){
   int a=count_nodes;
   for (int j=0; j< dimention[1]; ++j){
      for (int k=0; k< dimention[2]; ++k){
         nodes[count_nodes].x=i*myMap.resolution;
         nodes[count_nodes].y=j*myMap.resolution;
         nodes[count_nodes].z=k*myMap.resolution;
         nodes[count_nodes].index=count_nodes;
         ++count_nodes;
         }
      }
    int b=count_nodes-1;
    XYBounds.push_back({a,b});
   }
cout<<"neighbors determination"<<endl;

// determining the neighbors of each node along with the costs to get the them
for (int i = 0; i < N; ++i){
     int a{}; //boundries to check the nbr
     int b{};
    for (int ii=0; ii< static_cast<int>(XYBounds.size());++ii){
         if (i>=XYBounds[ii][0] && i<=XYBounds[ii][1]){
            if (ii==0){
               a=XYBounds[ii][0];
               b=XYBounds[ii+1][1];
            }
            else if (ii==(static_cast<int>(XYBounds.size())-1)){
               a=XYBounds[ii-1][0];
               b=XYBounds[ii][1];
            }
            else {
               a=XYBounds[ii-1][0];
               b=XYBounds[ii+1][1];
            }
          }
        }

   for (int j = a; j <= b; ++j){
       if( ((abs(nodes[i].x-nodes[j].x-myMap.resolution)<eps) && (abs(nodes[i].y-nodes[j].y)<eps) && (abs(nodes[i].z-nodes[j].z)<eps))
         ||((abs(nodes[i].x-nodes[j].x+myMap.resolution)<eps) && (abs(nodes[i].y-nodes[j].y)<eps) && (abs(nodes[i].z-nodes[j].z)<eps))
         ||((abs(nodes[i].y-nodes[j].y+myMap.resolution)<eps) && (abs(nodes[i].x-nodes[j].x)<eps) && (abs(nodes[i].z-nodes[j].z)<eps))
         ||((abs(nodes[i].y-nodes[j].y-myMap.resolution)<eps) && (abs(nodes[i].x-nodes[j].x)<eps) && (abs(nodes[i].z-nodes[j].z)<eps))
         ||((abs(nodes[i].z-nodes[j].z+myMap.resolution)<eps) && (abs(nodes[i].x-nodes[j].x)<eps) && (abs(nodes[i].y-nodes[j].y)<eps))
         ||((abs(nodes[i].z-nodes[j].z-myMap.resolution)<eps) && (abs(nodes[i].x-nodes[j].x)<eps) && (abs(nodes[i].y-nodes[j].y)<eps)) )
         {
           nodes[i].nbrIndexs.push_back(nodes[j].index);
           nodes[i].nbrCost.push_back(myMap.resolution);
           //cout<<i<<endl;
          }
     }
  }

cout<<"finished"<<endl;

return 0;}
