#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void *cpu_load(void *arg);
void *monitor_cpu_usage(void *arg);
int main()
{
    int num_cups = sysconf(_SC_NPROCESSORS_ONLN);
    pthread_t threads[num_cups];
    pthread_t monitor_thread;
    if (pthread_create(&monitor_thread, NULL, monitor_cpu_usage, NULL) != 0)
    {
        perror("Failed to create monitor thread");
        exit(-1);
    }
    printf("Starting %d threads to load CPU ...\n", num_cups);
    for (int i = 0; i < num_cups; i++)
    {
        if (pthread_create(&threads[i], NULL, cpu_load, NULL) != 0)
        {
            perror("pthread_create failed");
            exit(-1);
        }
    }
    for (int i = 0; i < num_cups; i++)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}