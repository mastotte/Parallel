#include <thread>
#include <vector>
#include <chrono>
void thread_blur(double *input, double *output, int size, int tid, int num_threads) {
    int workload = size / num_threads;
    int start = tid == 0 ? 0 : workload * tid;
    int end = tid == num_threads - 1 ? size : start + workload;
    
    for (int i = start + 1; i < end - 1; i++) {
        output[i] = (input[i] + input[i + 1] + input[i - 1])/3;
    }
}

// Do not change the signature of this function
// However, you should create more functions in this file for your computation.
// At the end, "output" should contain the final blurred values.
void repeated_blur(double* input, double* output, int size, int repeats, int num_threads) {
    
    for (int i = 0; i < repeats; ++i) {
        
        std::thread* threads = new std::thread[num_threads];

        for (int j = 0; j < num_threads; j++){
            threads[j] = std::thread(thread_blur, input, output, size, j, num_threads);
        }
        
        for (int k = 0; k < num_threads; k++){
            threads[k].join();
        }
        double *tmp = input;
        input = output;
        output = tmp; 
    }
}
