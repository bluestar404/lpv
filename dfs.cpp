// -----------DFS-------------
#include <iostream>
#include <omp.h>
using namespace std;

const int MAX = 100;
int parent[MAX];          // Stores parent of each node
bool visited[MAX];        // Marks if a node is visited
int numNodes = 0;

const int ROOT_NODE = 0;

// ------------------------------
// Function to Find Children of a Node
// ------------------------------
void findChildren(int node, int* children, int& childCount) {
    childCount = 0;
    #pragma omp parallel for
    for (int i = 0; i < numNodes; i++) {
        if (parent[i] == node) {
            #pragma omp critical
            {
                children[childCount++] = i;
            }
        }
    }
}

// ------------------------------
// Parallel DFS Traversal Function
// ------------------------------
void parallelDFS(int node) {
    visited[node] = true;
    cout << node << " ";

    int children[MAX];
    int childCount = 0;
    findChildren(node, children, childCount);

    // Parallel traversal for each child
    #pragma omp parallel for
    for (int i = 0; i < childCount; i++) {
        int child = children[i];
        if (!visited[child]) {
            #pragma omp critical
            {
                if (!visited[child]) {  // Double check inside critical
                    parallelDFS(child);
                }
            }
        }
    }
}

// ------------------------------
// Main Function
// ------------------------------
int main() {
    cout << "Enter number of nodes: ";
    cin >> numNodes;

    // Initialize all as unvisited and parent as -1
    for (int i = 0; i < numNodes; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    cout << "Enter parent for each node (except root " << ROOT_NODE << "):\n";
    for (int i = 0; i < numNodes; i++) {
        if (i == ROOT_NODE) continue;
        cout << "Parent of node " << i << ": ";
        cin >> parent[i];
    }

    cout << "Parallel DFS Traversal starting from root node " << ROOT_NODE << ":\n";
    parallelDFS(ROOT_NODE);

    return 0;
}
