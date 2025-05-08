// --------------------------------------
// Header Files and Namespace
// --------------------------------------
#include <iostream>
#include <omp.h>
using namespace std;

// --------------------------------------
// Sequential Bubble Sort Function
// --------------------------------------
void sequential_bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                // Swap
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

// --------------------------------------
// Parallel Bubble Sort Function
// --------------------------------------
void parallel_bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                // Swap
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
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
    int a[n], b[n];

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];  // Copy the array for comparison
    }

    // -------------------------------
    // Sequential Sort Timing Section
    // -------------------------------
    double start_time = omp_get_wtime();
    sequential_bubble_sort(a, n);
    double end_time = omp_get_wtime();
    double seq_time = end_time - start_time;

    // -------------------------------
    // Parallel Sort Timing Section
    // -------------------------------
    start_time = omp_get_wtime();
    for(int i = 0; i < 1000; i++) {
        parallel_bubble_sort(b, n);
    }
    end_time = omp_get_wtime();
    double par_time = end_time - start_time;

    // -------------------------------
    // Output Sorted Arrays
    // -------------------------------
    cout << "Sorted array (Sequential): ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";

    cout << "Sorted array (Parallel): ";
    for (int i = 0; i < n; i++) cout << b[i] << " ";
    cout << "\n";

    // -------------------------------
    // Output Time Comparison
    // -------------------------------
    cout << "Sequential sorting time: " << seq_time << " seconds\n";
    cout << "Parallel sorting time: " << par_time << " seconds\n";

    return 0;
}
