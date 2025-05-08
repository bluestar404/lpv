#include <iostream>
#include <omp.h>
using namespace std;

#define MAX_NODES 100
const int ROOT_NODE = 0;

// ------------------------------
// Global Variables
// ------------------------------

int parent[MAX_NODES];
int numNodes;

// ------------------------------
// Queue Implementation
// ------------------------------

int queue[MAX_NODES];
int front = -1, rear = -1;

bool isEmpty() {
    return front == -1;
}

void enqueue(int value) {
    if (rear == MAX_NODES - 1) return;
    if (isEmpty()) front = 0;
    rear++;
    queue[rear] = value;
}

int dequeue() {
    if (isEmpty()) return -1;
    int val = queue[front];
    if (front == rear) front = rear = -1;
    else front++;
    return val;
}

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
// Parallel BFS Traversal
// ------------------------------

void parallel_bfs_traversal(int start) {
    bool visited[MAX_NODES] = {false};
    
    visited[start] = true;
    enqueue(start);
    
    cout << "BFS Traversal: ";
    
    while (!isEmpty()) {
        int current = dequeue();
        cout << current << " ";
        
        // Find children of current node
        int children[MAX_NODES];
        int childCount = 0;
        findChildren(current, children, childCount);
        
        // Process all children
        for (int i = 0; i < childCount; i++) {
            int child = children[i];
            if (!visited[child]) {
                visited[child] = true;
                enqueue(child);
            }
        }
    }
    cout << endl;
}

// ------------------------------
// Main Function
// ------------------------------

int main() {
    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    
    // Initialize parent array
    for (int i = 0; i < numNodes; i++) {
        parent[i] = -1;
    }
    
    // Root node has parent -1
    parent[ROOT_NODE] = -1;
    
    cout << "Enter parent for each node (except root " << ROOT_NODE << "):" << endl;
    for (int i = 0; i < numNodes; i++) {
        if (i == ROOT_NODE) continue;
        
        cout << "Parent of node " << i << ": ";
        cin >> parent[i];
        
    }
    
    cout << "Starting BFS traversal from root node " << ROOT_NODE << "..." << endl;
    parallel_bfs_traversal(ROOT_NODE);
    
    return 0;
}
