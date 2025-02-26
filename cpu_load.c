#include <math.h>
#include <unistd.h>

void *cpu_load(void *arg)
{
    double x = 0.0001;
    while (1)
    {
        x = sin(x) * cos(x) * tan(x) * sqrt(x + 1.0);
    }
    return NULL;
}