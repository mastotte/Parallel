#include <math.h>

#define SIZE (1024 * 1024 * 8)

enum QueueType { sync, async, eight, eight_chunked };

void check_results(float *a, int size, QueueType t) {
    for(int i = 0; i < SIZE; i++){
        if (i % 1000000 == 0 || i > SIZE - 50){
            std::cout<<i<<"      "<<a[i]<<std::endl;
        }
    }
}

void check_timing(double seconds, QueueType t) {

}
