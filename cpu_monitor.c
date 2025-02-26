#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
void *monitor_cpu_usage(void *arg)
{
    FILE *fp;
    char line[256];
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        perror("Error opening /proc/stat");
        exit(-1);
    }
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(line, "cpu ", 4) == 0)
        {
            sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
            break;
        }
    }
    fclose(fp);
    unsigned long long PrevIdle = idle + iowait;
    unsigned long long PrevNonIdle = user + nice + system + irq + softirq + steal;
    unsigned long long PrevTotal = PrevIdle + PrevNonIdle;
    unsigned long long PrevSteal = steal;
    unsigned long long Idle, NonIdle, Total, totald, idled, Steal, steald;
    while (1)
    {
        sleep(1);
        fp = fopen("/proc/stat", "r");
        if (fp == NULL)
        {
            perror("Error opening /proc.stat");
            exit(-1);
        }
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            if (strncmp(line, "cpu ", 4) == 0)
            {
                sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
                break;
            }
        }
        fclose(fp);
        Idle = idle + iowait;
        Steal = steal;
        NonIdle = user + nice + system + irq + softirq + steal;
        Total = Idle + NonIdle;
        totald = Total - PrevTotal;
        idled = Idle - PrevIdle;
        steald = Steal - PrevSteal;
        PrevIdle = Idle;
        PrevNonIdle = NonIdle;
        PrevTotal = Total;
        float cpu_usage = (float)(totald - idled) / totald * 100;
        float cpu_steal = (float)(steald) / totald * 100;
        printf("CPU Usage : %.2f%%  CPU Steal : %.2f%% \r", cpu_usage, cpu_steal);
        fflush(stdout);
    }
}