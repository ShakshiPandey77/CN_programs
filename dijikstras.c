#include<bits/stdc++.h>
using namespace std;
int V;
int minDistance(int dist[], bool sptSet[]) 
{ 
	
	int min = INT_MAX, min_index; 

	for (int v = 0; v < V; v++) 
		if (sptSet[v] == false && dist[v] <= min) 
			min = dist[v], min_index = v; 

	return min_index; 
} 


void printSolution(int dist[]) 
{ 
	printf("Vertex \t\t Distance from Source\n"); 
	for (int i = 0; i < V; i++) 
		printf("%d \t\t %d\n", i, dist[i]); 
} 


void dijkstra(int **graph, int src) 
{ 
	int dist[V]; 

	bool sptSet[V];

	
	for (int i = 0; i < V; i++) 
		dist[i] = INT_MAX, sptSet[i] = false; 

	 
	dist[src] = 0; 

	 
	for (int count = 0; count < V - 1; count++) { 
		
		int u = minDistance(dist, sptSet); 

		
		sptSet[u] = true; 

		 for (int v = 0; v < V; v++) 

			
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
				&& dist[u] + graph[u][v] < dist[v]) 
				dist[v] = dist[u] + graph[u][v]; 
	} 

	
	printSolution(dist); 
} 


int main() 
{ 
	cout<<"Enter the no. of nodes :";
	cin>>V;
	int **graph=new int*[V];
	for(int i=0;i<V;i++)
	graph[i]=new int[V];
	cout<<"\nEnter the adjacency matrix :\n";
	for(int i=0;i<V;i++)
	for(int j=0;j<V;j++)
	cin>>graph[i][j];
	dijkstra(graph, 0); 

	return 0; 
} 

/* output:
Enter the no. of nodes :9
Enter the adjacency matrix :
999 4  999 999 999 999 999 8 999
  4 999 8 999 999 999 999 11 999
  999 8 999 7 999 4 999 999 2
  999 999 7 999 9 14 999 999 999
  999 999 999 9 999 10 999 999 999
  999 999 4 14 10 999 2 999 999
  999 999 999 999 999 2 999 1 6
  8 11 999 999 999 999 1  999 7
  999 999 2 999 999 999 6 7 999
Vertex 		 Distance from Source
0 		 0
1 		 4
2 		 12
3 		 19
4 		 21
5 		 11
6 		 9
7 		 8
8 		 14
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
