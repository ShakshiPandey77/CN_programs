// Implement Djikstra’s algorithm to compute the shortest path through a graph.

//this program finds Dijkstra's shortest path using STL set
#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <utility> //for pair
#include <iterator> 

using namespace std; 

#define INF 9999 

// This class represents a directed graph using adjacency list representation 
class Graph { 
	int V; // No. of vertices 

	// In a weighted graph, we need to store vertex and weight pair for every edge 
	list< pair<int, int> > *adj; 

public: 
	Graph(int V); // Constructor 

	// function to add an edge to graph 
	void addEdge(int u, int v, int w); 

	// prints shortest path from s 
	void shortestPath(int s); 
}; //end of class

// Allocates memory for adjacency list 
Graph::Graph(int V) { 
	this->V = V; 
	adj = new list< pair<int, int> >[V]; 
} // end 

void Graph::addEdge(int u, int v, int wt) { 
	adj[u].push_back(make_pair(v, wt)); 
	adj[v].push_back(make_pair(u, wt)); 
} //end

// Prints shortest paths from src to all other vertices 
void Graph::shortestPath(int src) { 
	// Create a set to store vertices that are being prerocessed 
	set< pair<int, int> > setds; //first element in pair is distance, second is the vertex number

	// Create a vector for distances and initialize all distances as infinite (INF) 
	vector<int> dist(V, INF); 

	// Insert source itself in Set and initialize its distance as 0. 
	setds.insert(make_pair(0, src)); 
	dist[src] = 0; 

	/* Looping till all shortest distance are finalized 
	then setds will become empty */
	while (!setds.empty()) { 
		// The first vertex in Set is the minimum distance vertex, extract it from set. 
		pair<int, int> tmp = *(setds.begin()); 
		setds.erase(setds.begin()); 

		// vertex label is stored in second of pair
		int u = tmp.second; 

		// 'i' is used to get all adjacent vertices of a vertex 
		list< pair<int, int> >::iterator i; 
		for (i = adj[u].begin(); i != adj[u].end(); ++i) { 
			// Get vertex label and weight of current adjacent of u. 
			int v = (*i).first; //vertex label
			int weight = (*i).second; //weight of edge

			// If there is shorter path to v through u. 
			if (dist[v] > dist[u] + weight) { 
				/* If distance of v is not INF then it must be in 
					our set, so removing it and inserting again 
					with updated less distance. 
					Note : We extract only those vertices from Set 
					for which distance is finalized. So for them, 
					we would never reach here. */
				if (dist[v] != INF) 
					setds.erase(setds.find(make_pair(dist[v], v))); 

				// Updating distance of v 
				dist[v] = dist[u] + weight; 
				setds.insert(make_pair(dist[v], v)); 
			} //end of if
		}// end of for 
	}//end of while 

	// Print shortest distances stored in dist[] 
	cout<<"Vertex Distance from Source\n"; 
	for (int i = 0; i < V; ++i) 
		cout<<i<<"\t\t"<<dist[i]<<"\n"; 
} //end of method


int main() { 
	int V, adj, wt, src;
	cout<<"Enter number of vertices :";
	cin>>V;
	Graph g(V);

	cout<<"Enter the adjacency list(adj vertex and weight):\n";
	for(int i = 0; i<V; i++){
		cout<<"Vertex "<<i<<" (-1 to exit):\n";
		while(1){
			cin>>adj>>wt;
			if(adj <0 || wt <0) break;
			g.addEdge(i,adj,wt);
		}//end of loop
	}//end of loop

	cout<<"Enter source vertex :";
	cin>>src;
	g.shortestPath(src); 
	return 0; 
} //end of main

/*
OUTPUT:
Enter number of vertices :6
Enter the adjacency list(adj vertex and weight):
Vertex 0 (-1 to exit):
1 5
2 3
3 7
-1 -1
Vertex 1 (-1 to exit):
0 5
2 4
4 7
5 9
-1 -1
Vertex 2 (-1 to exit):
0 3
2 4
3 3
4 8
-1 -1
Vertex 3 (-1 to exit):
0 7
2 3
4 4
-1 -1
Vertex 4 (-1 to exit):
1 7
2 8
3 4
5 2
-1 -1
Vertex 5 (-1 to exit):
1 9
4 2
-1 -1
Enter source vertex :0
Vertex Distance from Source
0		0
1		5
2		3
3		6
4		10
5		12
*/







/* #include<stdio.h>
#define INFINITY 9999
#define MAX 10
 
void dijkstra(int G[MAX][MAX],int n,int startnode);
 
int main()
{
	int G[MAX][MAX],i,j,n,u;
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	printf("\nEnter the adjacency matrix:\n");
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);
	
	printf("\nEnter the starting node:");
	scanf("%d",&u);
	dijkstra(G,n,u);
	
	return 0;
}
 
void dijkstra(int G[MAX][MAX],int n,int startnode)
{
 
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];
	
	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<n-1)
	{
		mindistance=INFINITY;
		
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			
			//check if a better path exists through nextnode			
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
 
	//print the path and distance of each node
	for(i=0;i<n;i++)
		if(i!=startnode)
		{
			printf("\nDistance of node%d=%d",i,distance[i]);
			printf("\nPath=%d",i);
			
			j=i;
			do
			{
				j=pred[j];
				printf("<-%d",j);
			}while(j!=startnode);
	}
}
*/
