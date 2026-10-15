#include <stdio.h>

#define N 4
#define INF 999

void printRoute(int source, int destination, int nextHop[N][N]) {
    int current = source;
    printf("%c", current + 'A');

    while (current != destination) {
        current = nextHop[current][destination];
        if (current == -1) {
            printf(" -> No Route\n");
            return;
        }
        printf(" -> %c", current + 'A');
    }
    printf("\n");
}

int main() {
    int cost[N][N];
    int dist[N][N];
    int nextHop[N][N];
    int updated;

    printf("Enter the cost matrix (use %d for INF):\n", INF);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = cost[i][j];
            if (i == j) {
                nextHop[i][j] = i;
            } else if (cost[i][j] != INF) {
                nextHop[i][j] = j;
            } else {
                nextHop[i][j] = -1;
            }
        }
    }

    // Distance Vector (Bellman-Ford) updates until no change
    do {
        updated = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nextHop[i][j] = nextHop[i][k];
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);

    printf("\nFinal distance table:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", dist[i][j]);
        }
        printf("\n");
    }

    printf("\nRoutes:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                printf("%c to %c (cost %d): ", i + 'A', j + 'A', dist[i][j]);
                printRoute(i, j, nextHop);
            }
        }
    }
    return 0;
}
