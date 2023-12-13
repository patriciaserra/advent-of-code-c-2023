#include <stdio.h>
#include <stdlib.h>

int min_speed(int time, int record)
{
    int hold;
    int distance;

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

int max_speed(int time, int record)
{
    int hold;
    int distance;

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
    int nraces = 4;
    int min;
    int max;
    int *p;
    int time[] = {57, 72, 69, 92};
    int record[] = {291, 1172, 1176, 2026};
    int i = 0;

    p = (int *)malloc(sizeof(int) * nraces);
    if (p == NULL)
        return (0);
    while (nraces > i)
    {
        min = min_speed(time[i], record[i]);
        max = max_speed(time[i], record[i]);
        p[i++] = max - min + 1;
    }
    free (p);
    printf("The solution is: %d", p[3] * p [2] * p [1] * p [0]);
}
