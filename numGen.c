#include <omp.h>    //Use OpenMP
#include <stdio.h>  //Provide I/O
#include <stdlib.h> //Use NULL
#include <unistd.h> //Use usleep (sleep for a number of microseconds)
#include <math.h>
#define NUM_PHIL 5 // The number of philosophers
#define MEALS 100  // The number of meals per philosopher


static omp_lock_t chopsticks[NUM_PHIL];

void philosopher()
{
// Wait for all threads to start
#pragma omp barrier
 
    // Set up variables for the thread id, right chopstick, and left chopstick.
    int id = omp_get_thread_num();
    int right_chopstick;
    int left_chopstick;
    double start = omp_get_wtime();
    // Philosophers 0 through NUM_PHIL-2 reach to the left first then the right.
    if (id < NUM_PHIL - 1)
    {
        right_chopstick = id;
        left_chopstick = id + 1;
    }
    // Philosopher NUM_PHIL-1 has its left and right swapped.  Notice that it reaches in the
    // opposite order of all other philosophers.
    else
    {
        right_chopstick = 0;
        left_chopstick = id;
    }
    // Acquire chopsticks (semaphores), eat, wait for 100 microseconds, then release
    // chopsticks (semaphores).
    int i;
    for (i = 0; i < MEALS; i++)
    {
        omp_set_lock(&chopsticks[left_chopstick]);
        omp_set_lock(&chopsticks[right_chopstick]);
 
        usleep(100);
 
        omp_unset_lock(&chopsticks[left_chopstick]);
        omp_unset_lock(&chopsticks[right_chopstick]);
    }
    double end = omp_get_wtime();
    double total = end - start;
    FILE *fptr;
    fptr = fopen("numbers.txt", "a");
    fprintf(fptr, "%g,", total);
    fclose(fptr);
    // printf("%g\n", total);
}
