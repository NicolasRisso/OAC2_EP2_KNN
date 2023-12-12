#include <stdio.h>
#include <omp.h>

int main() {
    // Set the number of threads to use (optional)
    omp_set_num_threads(4);

    // Create a parallel region
    #pragma omp parallel
    {
        // Get the thread ID
        int tid = omp_get_thread_num();

        // Get the total number of threads
        int num_threads = omp_get_num_threads();

        // Print a message from each thread
        printf("Hello from thread %d of %d\n", tid, num_threads);

        // Note: The following code block will be executed in parallel by multiple threads
        #pragma omp barrier

        // Print another message after synchronization
        printf("Thread %d is done!\n", tid);
    }

    return 0;
}
