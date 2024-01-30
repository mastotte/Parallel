#include <thread>
using namespace std;

/** You may add additional functions as needed in this file. */

/** Write your sequential computation here. */
void sequential_increment(volatile int *a, int size, int k) {
  // Implement me!
  for(int i = 0; i < size; i++){
    for(int j = 0; j < k; j++){
      a[i]++;
    }
  }
}

/** Write your round robin computation here.*/
void round_robin_increment(volatile int *b, int size, int k, int num_threads) {
    vector<thread> threads(num_threads);

    for (int tid = 0; tid < num_threads; ++tid) {
        threads[tid] = thread([=, &b]() {
            for (int i = tid; i < size; i += num_threads) {
                for (int j = 0; j < k; ++j) {
                    b[i]++;
                }
            }
        });
    }

    for (int tid = 0; tid < num_threads; ++tid) {
        threads[tid].join();
    }
}

/** Write your custom computation here. */
void custom_increment(volatile int *c, int size, int k, int num_threads) {
    vector<thread> threads(num_threads);

    int chunk_size = size / num_threads;
    int remainder = size % num_threads;

    int start = 0;
    for (int tid = 0; tid < num_threads; ++tid) {
        int thread_size = chunk_size + (tid < remainder ? 1 : 0);
        threads[tid] = thread([=, &c]() {
            int end = start + thread_size;
            for (int i = start; i < end; ++i) {
                for (int j = 0; j < k; ++j) {
                    c[i]++;
                }
            }
        });
        start += thread_size;
    }

    for (int tid = 0; tid < num_threads; ++tid) {
        threads[tid].join();
    }
}


