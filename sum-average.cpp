//Implement Min, Max, Sum and Average operations using Parallel 
//Reduction.
#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int a[100], n;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) cin >> a[i];

    int min_val = a[0], max_val = a[0], sum = 0;

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        if (a[i] < min_val) min_val = a[i];
        if (a[i] > max_val) max_val = a[i];
        sum += a[i];
    }

    cout << "Minimum: " << min_val << "\n";
    cout << "Maximum: " << max_val << "\n";
    cout << "Sum: " << sum << "\n";
    cout << "Average: " << (float)sum / n << "\n";

    return 0;
}
