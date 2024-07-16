#include <thread>
#include <iostream>
#if defined(SR)
#include "SRBarrier.h"
#elif defined(SRO)
#include "SROBarrier.h"
#else
#error "No barrier specified"
#endif
barrier_object B;


void thread_blur(double* input, double* output, int start, int end, int tid, int repeats) {
    for (int j = 0; j < repeats; j++){
        
        for (int i = start + 1; i < end - 1; i++) {
            output[i] = (input[i] + input[i + 1] + input[i - 1])/3;
        }
        double *tmp = input;
        input = output;
        output = tmp;
        B.barrier(tid);
    }
}

// Do not change the signature of this function.
// However, you should create more functions in this file for your computation.
// At the end, "output" should contain the final blurred values.
void repeated_blur(double* input, double* output, int size, int repeats, int num_threads) {
    B.init(num_threads);
    int workload = size / num_threads;
    
    std::thread* threads = new std::thread[num_threads];

    for (int j = 0; j < num_threads; ++j) {
        int start = j * workload;
        int end = start + workload;

        if (j == num_threads - 1){
            end = size;
        }
        
        threads[j] = std::thread(thread_blur, input, output, start, end, j, repeats);
    }

    for (int j = 0; j < num_threads; ++j) {
        threads[j].join();
    }
    
    delete[] threads;

    std::swap(input, output);

}

