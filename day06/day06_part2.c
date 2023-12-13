#include <stdio.h>
#include <stdlib.h>

unsigned long long min_speed(unsigned long long time, unsigned long long record)
{
    unsigned long long hold;
    unsigned long long distance;

    hold = 0;
    distance = 0;
    while (hold <= time)
    {
        distance = (hold * (time - hold));
        if (record >= distance)
            hold++;
        else
            break;
    }
    return (hold);
}

unsigned long long max_speed(unsigned long long time, unsigned long long record)
{
    unsigned long long hold;
    unsigned long long distance;

    hold = time;
    distance = 0;
    while (hold >= 0)
    {
        distance = (hold * (time - hold));
        if (record >= distance)
            hold--;
        else
            break;
    }
    return (hold);
}

int main()
{
    unsigned long long nraces = 1;
    unsigned long long min;
    unsigned long long max;
    unsigned long long *p;
    unsigned long long time[] = {57726992};
    unsigned long long record[] = {291117211762026};
    int i = 0;

    p = (unsigned long long *)malloc(sizeof(unsigned long long) * nraces);
    if (p == NULL)
        return (0);
    while (nraces > i)
    {
        min = min_speed(time[i], record[i]);
        max = max_speed(time[i], record[i]);
        p[i++] = max - min + 1;
    }
    printf("The solution is: %llu", p[0]);
    free (p);
    return (0);
}
