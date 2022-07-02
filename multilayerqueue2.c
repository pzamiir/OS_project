#include "types.h"
#include "user.h"
#include "stat.h"

int main(void)
{
    changePolicy(3);
    int i = 0;
    int pid;
    for (i = 0; i < 60; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            printf(1, "EREOR\n");
            exit();
        }
        if (pid == 0)
        {
            pid = getpid();
            if (i < 10)
                setPriority(1);
            else if (i > 9 && i < 20)
                setPriority(2);
            else if (i > 19 && i < 30)
                setPriority(3);
            else if (i > 29 && i < 40)
                setPriority(4);
            else if (i > 39 && i < 50)
                setPriority(5);
            else if (i > 49 && i < 60)
                setPriority(6);

            for (int j = 1; j < 25; j++)
                printf(1, "%d : %d\n", pid, j);

            int turnaroundTime = getTurnaroundTime(pid);
            int waitingTime = getWaitTime(pid);
            int burstTime = getCpuBurstTime(pid);
            sleep(2000 + 10 * pid);

            printf(1, "PID : %d burstTime : %d\n", pid, burstTime);
            printf(1, "PID : %d Turnaround : %d\n", pid, turnaroundTime);
            printf(1, "PID : %d Waiting : %d\n", pid, waitingTime);
            exit();
        }
    }

    if (pid != 0)
    {
        int Burst[6];
        int TAT[6];
        int Waiting[6];

        int totalBurst = 0;
        int totalTA = 0;
        int totalwait = 0;
        int priority = 0;
        for (int i = 0; i < 60; i++)
        {
            pid = wait();
            priority = getPriority(pid) - 1;
            int burstTime = getCpuBurstTime(pid);
            int turnAroundTime = getTurnaroundTime(pid);
            int waitingTime = getWaitTime(pid);
            Burst[priority] += burstTime;
            TAT[priority] += turnAroundTime;
            Waiting[priority] += waitingTime;
            totalBurst += burstTime;
            totalTA += turnAroundTime;
            totalwait += waitingTime;
        }

        for (int i = 0; i < 6; i++)
        {
            int avgCpuBurstTime = (Burst[i]) / 5;
            int avgTurnAround = (TAT[i]) / 5;
            int avgWaitingTime = (Waiting[i]) / 5;
            printf(2, "layer number %d has average bursttime of %d,has average turnaroundtime of %d and has average waiting time of %d\n", i + 1,avgCpuBurstTime,avgTurnAround,avgWaitingTime);

        }

        int avgCpuBurstTime = (totalBurst) / 60;
        int avgTurnAround = (totalTA) / 60;
        int avgWaitingTime = (totalwait) / 60;
        printf(1, "Average of burstTime is : %d and average of total time is %d and average of waiting time is\n",avgCpuBurstTime , avgTurnAround,avgWaitingTime);
        exit();
    }
}