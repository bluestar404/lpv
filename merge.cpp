// --------------------------------------
// Header Files and Constants
// --------------------------------------
#include <iostream>
#include <omp.h>
using namespace std;

const int MAX = 100000;  // Increase if you want to test with large inputs
int a[MAX], temp[MAX], backup[MAX];

// --------------------------------------
// Merge Function (Merging two subarrays)
// --------------------------------------
void merge(int low, int mid, int high) {
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
        temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
    while (i <= mid) temp[k++] = a[i++];
    while (j <= high) temp[k++] = a[j++];
    for (int x = low; x <= high; x++) a[x] = temp[x];
}

// --------------------------------------
// Sequential Merge Sort Function
// --------------------------------------
void sequentialMergeSort(int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        sequentialMergeSort(low, mid);
        sequentialMergeSort(mid + 1, high);
        merge(low, mid, high);
    }
}

// --------------------------------------
// Parallel Merge Sort Function
// --------------------------------------
void parallelMergeSort(int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(low, mid);
            #pragma omp section
            parallelMergeSort(mid + 1, high);
        }
        merge(low, mid, high);
    }
}

// --------------------------------------
// Main Function
// --------------------------------------
int main() {
    // -------------------------------
    // Input Section
    // -------------------------------
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        backup[i] = a[i];  // Save original input
    }

    // -------------------------------
    // Sequential Merge Sort Timing Section
    // -------------------------------
    for (int i = 0; i < n; i++) a[i] = backup[i];
    double start = omp_get_wtime();
    sequentialMergeSort(0, n - 1);
    double end = omp_get_wtime();
    cout << "\nSequential Merge Sort Time: " << (end - start) << " seconds\n";

    // -------------------------------
    // Parallel Merge Sort Timing Section
    // -------------------------------
    for (int i = 0; i < n; i++) a[i] = backup[i];
    start = omp_get_wtime();
    for (int i = 0; i < 1000; i++) {
        parallelMergeSort(0, n - 1);
    }
    end = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << (end - start) << " seconds\n";

    // -------------------------------
    // Output Sorted Array
    // -------------------------------
    cout << "\nSorted array:\n";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;

    return 0;
}
