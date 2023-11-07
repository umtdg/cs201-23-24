#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include <cmath>

typedef void (*sort_func_t)(int *, size_t);
typedef std::chrono::high_resolution_clock _clock;
typedef std::chrono::nanoseconds _ns;

// bubble sort - in place - ascending
// https://en.wikipedia.org/wiki/Bubble_sort#Optimizing_bubble_sort
void bubble_sort(int *data, size_t n) {
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 1; i < n; i++) {
            if (data[i - 1] > data[i]) {
                // Swap the elements
                std::swap(data[i - 1], data[i]);
                swapped = true;
            }
        }
        n--; // Reduce the range of unsorted elements
    } while (swapped);
}

// quicksort - Hoare partition scheme - in place - ascending
// https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme
size_t qs_partition(int *data, size_t lo, size_t hi) {
    size_t pivot = data[(size_t)floor((hi - lo)/2.0) + lo];

    size_t i = lo - 1; // left index
    size_t j = hi + 1; // right index

    while (true) {
        do i++; while(data[i] < pivot);

        do j--; while(data[j] > pivot);

        if (i >= j) return j;

        std::swap(data[i], data[j]);
    }
}

void quicksort(int *data, size_t lo, size_t hi) {
    if (lo >= hi) return;

    size_t p = qs_partition(data, lo, hi);
    quicksort(data, lo, p);
    quicksort(data, p + 1, hi);
}

void quicksort(int *data, size_t n) {
    quicksort(data, 0, n - 1);
}

// merge sort - top-down - in place - ascending
void merge(int *data, size_t lo, size_t mid, size_t hi) {
    int *tmp = new int[hi - lo];
    size_t i = lo, j = mid, k = 0;

    while (i < mid && j < hi) {
        if (data[i] < data[j]) {
            tmp[k++] = data[i++];
        } else {
            tmp[k++] = data[j++];
        }
    }

    while (i < mid) tmp[k++] = data[i++];
    while (j < hi) tmp[k++] = data[j++];

    std::copy(tmp, tmp + (hi - lo), data + lo);

    delete[] tmp;
}

void merge_sort(int *data, size_t n) {
    if (n <= 1) return;

    // divide into equal sized subarrays and sort them separately
    size_t mid = n / 2;
    merge_sort(data, mid);
    merge_sort(data + mid, n - mid);

    // merge the two sorted subarrays
    merge(data, 0, mid, n);
}


void test_sort_method(sort_func_t sort_func, int *data, size_t n) {
    int data_sorted[n];
    std::copy(data, data + n, data_sorted);

    sort_func(data_sorted, n);

    std::cout << std::left << std::setw(10) << "Original"
        << " " << std::setw(10) << "Sorted"
        << "\n";
    for (size_t i = 0; i < n; i++) {
        std::cout << std::setw(10) << data[i]
            << " " << std::setw(10) << data_sorted[i]
            << "\n";

        if (i > 0 && data_sorted[i - 1] > data_sorted[i]) {
            std::cerr << "Sorting failed!\n";
            return;
        }
    }
}


int main(int argc, char **argv) {
    if (argc != 4) return 1;

    std::string sort_method = argv[1];
    std::string data_file = argv[2];
    size_t data_size = std::stoi(argv[3]);

    sort_func_t sort_func;
    auto data_vec = std::vector<int>(data_size);
    auto data = data_vec.data();

    // set sort method
    if (sort_method == "bubble") {
        sort_func = bubble_sort;
    } else if (sort_method == "quick") {
        sort_func = quicksort;
    } else if (sort_method == "merge") {
        sort_func = merge_sort;
    } else {
        std::cerr << "Invalid sort method!\n";
        return 1;
    }

    // read data into vector
    std::ifstream data_fs;
    data_fs.open(data_file);

    for (size_t i = 0; i < data_size; i++) {
        data_fs >> data[i];
    }

    data_fs.close();

    // benchmark sort method
    auto start = _clock::now();
    sort_func(data, data_size);
    auto end = _clock::now();

    std::cout << std::chrono::duration_cast<_ns>(end - start).count();

    return 0;
}
