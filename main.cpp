#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <iomanip>
#include <fstream>

using namespace std;

// Source: https://www.geeksforgeeks.org/merge-sort/
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<int>& arr, int left,
           int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Source: https://www.geeksforgeeks.org/merge-sort/
// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int> arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Source: https://www.geeksforgeeks.org/insertion-sort-algorithm/
/* Function to sort array using insertion sort */
void insertionSort(vector<int> arr, int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/**
 * Decide how many times to call the function repeatedly
 * @param vecSize size of the vector to sort
 * @return what size the loop should be
 */
int LoopSize(int vecSize)
{
    int loopSize = 0;

    if (vecSize < 10)
    {
        loopSize = 500000;
    }
    else if (vecSize < 50)
    {
        loopSize = 1000;
    }
    else if (vecSize < 100)
    {
        loopSize = 500;
    }
    else if (vecSize < 500)
    {
        loopSize = 300;
    }
    else
    {
        loopSize = 10;
    }
    return loopSize;
}

/**
 * Calculate insertion sort time by repeating it
 * @param vec vector to sort
 * @return insertion sort time
 */
double CalcSmallInsertionTime(vector<int> vec)
{
    int n = LoopSize(vec.size());
    std::clock_t start_time = std::clock();
    for (auto i = 0; i < n; i++)
    {
        insertionSort(vec, vec.size() - 1);
    }

    std::clock_t tot_time = std::clock() - start_time;
    return ((double) tot_time) / (double) CLOCKS_PER_SEC / n;
}

/**
 * Calculate merge sort time by repeating it
 * @param vec vector to sort
 * @return merge sort time
 */
double CalcSmallMergeTime(vector<int> vec)
{
    int n = LoopSize(vec.size());
    std::clock_t start_time = std::clock();
    for (auto i = 0; i < n; i++)
    {
        mergeSort(vec, 0, vec.size() - 1);
    }

    std::clock_t tot_time = std::clock() - start_time;
    return ((double) tot_time) / (double) CLOCKS_PER_SEC / n;
}

/**
 * Generate a random vector
 * @param size size of the vector
 * @return a random vector
 */
vector<int> RandomVector(int size)
{
    // Source: https://en.cppreference.com/w/cpp/numeric/random/random_device
    random_device rd;
    vector<int> vec {};
    std::uniform_int_distribution<int> dist(0, 9999);
    for (auto i = 0; i < size; i++)
    {
        vec.push_back(dist(rd));
    }
    return vec;
}

/**
 * Calculate the time it takes to sort a vector using insertion sort
 * @param vec vector to sort
 * @return time for insertion sort
 */
double CalcInsertion(vector<int> vec)
{
    // calculate time for insertion sort
    std::clock_t  start_time = std::clock();
    insertionSort(vec, vec.size());
    std::clock_t  tot_time = std::clock() - start_time;
    double insertionTime = ((double) tot_time) / (double) CLOCKS_PER_SEC;

    if (insertionTime == 0)
    {
        insertionTime = CalcSmallInsertionTime(vec);
    }

    return insertionTime;
}

/**
 * Calculate the time it takes to sort a vector using merge sort
 * @param vec vector to sort
 * @return time for merge sort
 */
double CalcMerge(vector<int> vec)
{
    std::clock_t  start_time = std::clock();
    mergeSort(vec, 0, vec.size() - 1);
    std::clock_t  tot_time = std::clock() - start_time;
    double mergeTime = ((double) tot_time) / (double) CLOCKS_PER_SEC;

    if (mergeTime == 0)
    {
        mergeTime = CalcSmallMergeTime(vec);
    }

    return mergeTime;
}

/**
 * Test speeds of two sorting algorithms
 * @param vec vector to sort
 * @return vector containing merge time and insertion time
 */
vector<double> TestSpeed(vector<int> & vec)
{
    double mergeTime = CalcMerge(vec);
    double insertionTime = CalcInsertion(vec);

    return {mergeTime, insertionTime};
}

/**
 * Get the average runtime of each algorithm
 * @param size size of the vector
 * @return vector containing merge time and insertion time
 */
vector<double> GetAverageTime(int size)
{
    cout << "Testing for input size of " << size << ':' << endl;
    cout << endl;
    double mergeTimeTotal = 0;
    double insertionTimeTotal = 0;

    int count = 200;
    for (auto i = 0; i < count; i++)
    {
        vector<int> vec = RandomVector(size);
        vector<double> timeVec = TestSpeed(vec);

        mergeTimeTotal += timeVec.at(0);
        insertionTimeTotal += timeVec.at(1);
    }

    double mergeTime = mergeTimeTotal / count;
    double insertionTime = insertionTimeTotal / count;

    return {mergeTime, insertionTime};
}

int main()
{
    string filename = "sortingTimes.csv";
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Can't open file" << endl;
    }
    file << "Input Size, Merge Sort Time, Insertion Sort Time\n";

    for (auto i = 50; i < 3000; i += 50)
    {
        auto timeVec = GetAverageTime(i);
        file << i << ", " << timeVec.at(0) << ", " << timeVec.at(1) << '\n';
    }
    file.close();

    return 0;
}
