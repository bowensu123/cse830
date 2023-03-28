#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include "gnuplot-iostream.h"
#include <map>
#include <unordered_map>
#include <random>
using namespace std;

/*
 For compilers to find llvm you may need to set:
   export LDFLAGS="-L/usr/local/opt/llvm/lib"
   export CPPFLAGS="-I/usr/local/opt/llvm/include"
 */


int main()
{
    //std::vector<int> ns = {10,50,100,150,200,300,400,500,600,700,800,900,1000};
    std::vector<int>ns;
    for(int i =0;i<50;++i)
    {
        ns.push_back(20*i+5);
    }
    vector<pair<int,double>> multimap_time, unordered_multimap_time;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1,1000000);
    for(int n:ns)
    {
        
        vector<int> tmp;
        for(int i =0;i<n;i++)
        {
            tmp.push_back(dis(gen));
        }
        std::multimap<int,int> mmap;
        std::clock_t start_time = std::clock();
        for(int i =0;i<n;i++)
        {
            mmap.insert({tmp[i],i});
        }
        std::clock_t end_time = std::clock()-start_time;
        std::cout<<"std::multimap insertion for n = "<<n<<" took "<<((double) end_time) / (double) CLOCKS_PER_SEC<<" seconds. "<<std::endl;
        multimap_time.push_back(make_pair(n,((double) end_time) / (double) CLOCKS_PER_SEC));
        
        std::unordered_multimap<int,int> umap;
        std::clock_t start1_time = std::clock();
        for(int i =0;i<n;i++)
        {
            umap.insert({tmp[i],i});
        }
        std::clock_t end1_time = std::clock()-start1_time;
        std::cout<<"std::unordered_multimap insertion for n = "<<n<<" took "<<((double) end1_time) / (double) CLOCKS_PER_SEC<<" seconds. "<<std::endl;
        unordered_multimap_time.push_back(make_pair(n,((double) end1_time) / (double) CLOCKS_PER_SEC));
    }

    Gnuplot gp;

    gp << "set title 'Insertion Runtimes'\n";
    gp << "set xlabel 'Array Size'\n";
    gp << "set ylabel 'Time (s)'\n";
    gp << "set output 'Q3.png'\n";
    gp << "plot '-' with lines title 'hash table', '-' with lines title 'balanced binary tree'\n";
    gp.send1d(unordered_multimap_time);
    gp.send1d(multimap_time);
    return 0;
}
