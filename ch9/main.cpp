#include "Heap.h"

int main() {
    const int n = 8;
    double arr[n] = {6.5, 5.5, 3.5, 1.5, 8.5, 7.5, 2.5, 4.5};
    Heap<double> heap(arr, n, false);
    heap.sort();
    heap.output();
}