#include <stdio.h>
#include "err.h"
#include "graph.h"
#include "lqueue.h"

struct GraphRecord
{
      int adj[max][max];
      int visited[max];
      int nodes;
};

Graph CreateGraph(int NodesCount)
{
      Graph G;

      G = malloc(sizeof(struct GraphRecord));
      if(G == NULL) Error( "Out of space!!!" );

      G->nodes = NodesCount;

      return G;
}


void DisposeGraph(Graph G)
{
     free(G);
}


/* a function to build adjacency matrix of a graph */
void buildadjm(Graph G)
   {
     int i,j;
     for(i=0;i<G->nodes;i++)
         for(j=0;j<G->nodes;j++)
          {
           printf("enter 1 if there is an edge from %d to %d, otherwise enter 0 \n", i,j);
           scanf("%d",&(G->adj[i][j]));
           }
      }

void printadjm(Graph G)
{
     int i,j;
     for(i=0;i<G->nodes;i++)
     {
         for(j=0;j<G->nodes;j++)
          printf(" %d",G->adj[i][j]);
         putchar('\n');
     }
}

void ClearVisited(Graph G)
{
     int n;
     for(n=0; n<G->nodes; n++)
         G->visited[n] = 0;
}

int CheckAdjacencyMatrix(Graph G) {
    for (int i = 0; i < G->nodes; i++) {
        if (G->adj[i][i] != 0) {
            Error("Main diagonal must have value 0");
            return 0;
        }
        for (int j = 0; j < G->nodes; j++) {
            if (G->adj[i][j] != 0 && G->adj[i][j] != 1) {
                Error("Invalid adjacency matrix value");
                return 0;
            }
        }
    }
    return 1;
}
// 3 stavy - 0 (not found), 1 (opened), 2 (closed)
void dfs(Graph G, int v0)
{
    if(G == NULL) {
        Error("Graph not initialized");
        return;
    }
    if(v0 < 0 || v0 >= G->nodes) {
        Error("Invalid node number");
        return;
    }
    
    for (int i = 0; i < G->nodes; i++) {
        if (G->visited[i] < 0 || G->visited[i] > 2) {
            Error("Invalid value in visited array");
            return;
        }
    }
    if(!CheckAdjacencyMatrix(G)) {
        return;
    }

    ClearVisited(G);
    printf("Depth first search - DFS:\n");
    dfs2(G,v0);
    for(int i = 0; i < G->nodes; i++)
    {
        if(G->visited[i] == 0)
        {
            dfs2(G,i);
        }
    }
}

void dfs2(Graph G, int v0)
{
    int w;
    printf("The node opened: %d\n",v0);
    G->visited[v0] = 1;

    for(w = 0; w < G->nodes; w++){
        if(G->adj[v0][w] == 1 && G->visited[w] == 0){
            dfs2(G,w);
        }
    }
    
    G->visited[v0] = 2;
}

void dfsst(Graph G, int v0)
{
    if(G == NULL){
        Error("Graph not initialized");
        return;
    }
    if(v0 < 0 || v0 >= G->nodes){
        Error("Invalid node number");
        return;
    }
    for (int i = 0; i < G->nodes; i++) {
        if (G->visited[i] < 0 || G->visited[i] > 2) {
            Error("Invalid value in visited array");
            return;
        }
    }

    if(!CheckAdjacencyMatrix(G)){
        return;
    }

    ClearVisited(G);
    
    printf("DFS Spanning tree:\n");
    dfsst2(G,v0);
    for(int i = 0; i < G->nodes; i++)
    {
        if(G->visited[i] == 0)
        {
            dfsst2(G,i);
        }
    }
}

void dfsst2(Graph G, int v0)
{
    G->visited[v0] = 1;

    for(int w = 0; w < G->nodes; w++)
    {
        if(G->adj[v0][w] == 1 && G->visited[w] == 0)
        {
            printf("Edge: (%d,%d)\n",v0,w);
            dfsst2(G,w);
        }
    }
    G->visited[v0] = 2;
}

void bfs2(Graph G, int v0){

    LQueue Q = CreateQueue();
    if (Q == NULL) {
        Error("Failed to create queue for BFS!");
        return;
    }

    Enqueue(v0, Q);
    G->visited[v0] = 1;
    while (!IsEmptyQueue(Q)) {
        int v = FrontAndDequeue(Q);
        printf("The node opened: %d\n", v);
        for (int w = 0; w < G->nodes; w++) {
            if (G->adj[v][w] == 1 && G->visited[w] == 0) {
                Enqueue(w, Q);
                G->visited[w] = 1;
            }
        }
        G->visited[v] = 2;
    }
    RemoveQueue(&Q);
}

void bfs(Graph G, int v0) {
    if (G == NULL) {
        Error("Graph is NULL in bfs!");
        return;
    }
    if (v0 < 0 || v0 >= G->nodes) {
        Error("Invalid starting node for bfs!");
        return;
    }
    
    for (int i = 0; i < G->nodes; i++) {
        if (G->visited[i] < 0 || G->visited[i] > 2) {
            Error("Invalid value in visited array");
            return;
        }
    }

    if(!CheckAdjacencyMatrix(G)){
        return;
    }

    ClearVisited(G);
    printf("Breadth first search - BFS:\n");
    bfs2(G, v0);
    for (int i = 0; i < G->nodes; i++) {
        if (G->visited[i] == 0) {
            bfs2(G, i);
        }
    }

}

void bfsst2(Graph G, int v0)
{
    LQueue Q = CreateQueue();
    if (Q == NULL) {
        Error("Failed to create queue for BFS!");
        return;
    }

    Enqueue(v0, Q);
    G->visited[v0] = 1;
    while (!IsEmptyQueue(Q)) {
        int v = FrontAndDequeue(Q);
        for (int w = 0; w < G->nodes; w++) {
            if (G->adj[v][w] == 1 && G->visited[w] == 0) {
                Enqueue(w, Q);
                G->visited[w] = 1;
                printf("Edge: (%d,%d)\n", v, w);
            }
        }
        G->visited[v] = 2;
    }
    RemoveQueue(&Q);
}

void bfsst(Graph G, int v0)
{
    if(G == NULL){
        Error("Graph not initialized");
        return;
    }
    if(v0 < 0 || v0 >= G->nodes){
        Error("Invalid node number");
        return;
    }

    for (int i = 0; i < G->nodes; i++) {
        if (G->visited[i] < 0 || G->visited[i] > 2) {
            Error("Invalid value in visited array");
            return;
        }
    }

    if(!CheckAdjacencyMatrix(G)){
        return;
    }

    ClearVisited(G);
    printf("BFS spanning tree:\n");
    bfsst2(G,v0);
    for(int i = 0; i < G->nodes; i++)
    {
        if(G->visited[i] == 0)
        {
            bfsst2(G,i);
        }
    }

}
