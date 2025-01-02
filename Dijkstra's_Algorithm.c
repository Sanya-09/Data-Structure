#include <stdio.h>
#include <limits.h>

#define V 6

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    return min_index;
}

void printSolution(int dist[], int src) {
    printf("\nVertex\t\tDistance from Source %c\n", src + 'A');
    printf("--------------------------------\n");
    for (int i = 0; i < V; i++) {
        printf("%c\t\t%d\n", i + 'A', dist[i]);
    }
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf(" -> %c", j + 'A');
}

void printShortestPath(int dist[], int parent[], int src, int dest) {
    printf("\nShortest distance from %c to %c is %d\n", src + 'A', dest + 'A', dist[dest]);
    printf("Path: %c", src + 'A');
    printPath(parent, dest);
    printf("\n");
}

void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];
    int sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, src);
    printShortestPath(dist, parent, src, dest);
}

int main() {
    int graph[V][V] = {
        { 0, 2, 0, 8, 0, 0},  
        { 2, 0, 0, 5, 6, 0},  
        { 0, 0, 0, 0, 9, 3},  
        { 8, 5, 0, 0, 3, 7},  
        { 0, 6, 9, 3, 0, 1},  
        { 0, 0, 3, 7, 1, 0}  
    };

    int src, dest;
    printf("Enter the source (0 for A, 1 for B, ..., 5 for F): ");
    scanf("%d", &src);
    printf("Enter the destination (0 for A, 1 for B, ..., 5 for F): ");
    scanf("%d", &dest);

    dijkstra(graph, src, dest);

    return 0;
}
