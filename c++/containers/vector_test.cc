/*
 * Vector benchmark. Benchmark code comes from:
 * https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c
 */

#include <iostream>
#include <chrono>
#include <string>
#include "containers.h"

using namespace std;
using namespace std::chrono;

int iters = 1;

void benchmark(std::function<void (void)> thunk, string name) {
  cout << "Averaging 5 calls to benchmark" << endl;
  long long duration = 0;

  for (int i = 0; i < 5; i++) {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    thunk();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    long long dur = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Iteration " << i << " took "
         << dur
         << " microseconds." << endl;
    duration += dur;
  }
  
  cout << name << ": Average time was "
       << (duration / 5)
       << " microseconds." << endl;
}

void benchmark_arrayvec() {
  ArrayVector<int> v;

  for(int i = 0; i < iters; i++) {
    v = ArrayVector<int>(i,v);
  }
}

void benchmark_llvec() {
  LLVector<int> v;

  for(int i = 0; i < iters; i++) {
    v.addToFront(i);
  }
}

int main(int argc, char **argv) {
  cout << "Starting the example...\n";
  if (argc < 2) {
    cout << "You can specify how many iterations you want to use with first cmd line param\n";
    iters = 20000;
  } else {
    iters = std::stoi(argv[1]);
  }

  // Run benchmarks to build array vectors
  benchmark(benchmark_arrayvec, "build-arrayvec");

  // Run benchmarks to build array vectors
  benchmark(benchmark_llvec, "build-llvec");
}
