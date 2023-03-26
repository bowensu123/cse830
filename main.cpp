#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include "gnuplot-iostream.h"
using namespace std;

/*
 For compilers to find llvm you may need to set:
   export LDFLAGS="-L/usr/local/opt/llvm/lib"
   export CPPFLAGS="-I/usr/local/opt/llvm/include"
 */
void insertion_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = key;
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void merge_sort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    Gnuplot gp;
    ofstream outfile;
    outfile.open("/Users/subowen/Desktop/hw/hw/sort_times.txt");

    int min_n = 2;
    int max_n = 2000;
    int step_n = 5;
    vector<pair<int,double>> merge_data,insertion_data;
    //vector<pair<int,double>> insertion_data;
    outfile << "index" << " " << "merge_time" << " " << "insertion_time" << endl;
    for (int n = min_n; n <= max_n; n += step_n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            arr[i] = rand() % max_n;
        vector<int> copy = arr;
        cout<<"start"<<endl;
        cout<<"original arr: "<<endl;
        for(int i = 0;i<n;++i)
        {
            cout<< arr[i]<<" ";
        }
        cout<<"\n"<<endl;
        std::clock_t start_time = std::clock();
        merge_sort(arr, 0, n-1);
        std::clock_t merge_time = std::clock() - start_time;
        merge_data.push_back(make_pair(n, ((double) merge_time) / (double) CLOCKS_PER_SEC));
        cout<<"after arr: "<<endl;
        
        for(int i = 0;i<n;++i)
        {
            cout<< arr[i]<<" ";
        }
        cout<<"end"<<endl;
        std::clock_t star_time = std::clock();
        insertion_sort(copy);
        std::clock_t insertion_time = std::clock() - star_time;
        insertion_data.push_back(make_pair(n, ((double) insertion_time) / (double) CLOCKS_PER_SEC));
        outfile << n << " " << merge_time << " " << insertion_time << endl;
    }

    outfile.close();
    // Plot the results
    
    //gp << "set terminal png size 800,600\n";
    //gp << "plot '-' with points\n";
    gp << "plot '-' with lines title 'merge sort', '-' with lines title 'insertion sort'\n";
    gp.send1d(merge_data);
    gp.send1d(insertion_data);
    //gp << "set output 'sort_times.png'\n";
    //gp << "set title 'Sort Runtimes'\n";
    //gp << "set xlabel 'Array Size'\n";
    //gp << "set ylabel 'Time (s)'\n";
 
    return 0;
    /*
    string gnuplot_commands[] = {
        "set xlabel \"n\"",
        "set ylabel \"Time (microseconds)\"",
        "set logscale x 10",
        "set key top left",
        "plot \"sort_times.txt\" using
    };*/
    
}
