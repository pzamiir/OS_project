#include "types.h"
#include "user.h"
#include "stat.h"

int main(void)
{
    changePolicy(2);
    int i = 0;
    int pid;
    for (i = 0; i < 30; i++)
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
            if (i < 5)
                setPriority(6);
            else if (i > 4 && i < 10)
                setPriority(5);
            else if (i > 9 && i < 15)
                setPriority(4);
            else if (i > 14 && i < 20)
                setPriority(3);
            else if (i > 19 && i < 25)
                setPriority(2);
            else if (i > 24 && i < 30)
                setPriority(1);

            for (int j = 1; j < 250; j++)
                printf(1, "%d : %d\n", pid, j);

            int cpuBurstTime = getCpuBurstTime(pid);
            int turnAroundTime = getTurnaroundTime(pid);
            int waitTime = getWaitTime(pid);

            sleep(2000 + 10 * pid);
            printf(1, "PID : %d burstTime : %d\n", pid, cpuBurstTime);
            printf(1, "PID : %d Turnaround : %d\n", pid, turnAroundTime);
            printf(1, "PID : %d Waiting : %d\n", pid, waitTime);
            exit();
        }
    }

    if (pid != 0)
    {
        setPriority(1);
        int layerBurst[6];
        int layerTAT[6];
        int layerWait[6];

        int totalBurst = 0;
        int totalTA = 0;
        int totalWait = 0;

        for (int i = 0; i < 30; i++)
        {
            pid = wait();
            int priority = getPriority(pid) - 1;
            int burstTime = getCpuBurstTime(pid);
            int turnAroundTime = getTurnaroundTime(pid);
            int waitingTime = getWaitTime(pid);
            layerBurst[priority] += burstTime;
            layerTAT[priority] += turnAroundTime;
            layerWait[priority] += waitingTime;
            totalBurst += burstTime;
            totalTA += turnAroundTime;
            totalWait += waitingTime;
        }

        for (int i = 0; i < 6; i++)
        {
            int avgCBT = (layerBurst[i]) / 5;
            int avgTAT = (layerTAT[i]) / 5;
            int avgWT = (layerWait[i]) / 5;
            printf(2, "priority number %d has average bursttime of %d,has average turnaroundtime of %d and has average waiting time of %d", i + 1,avgCBT,avgTAT,avgWT);
        }

        int avgCBT = (totalBurst) / 30;
        int avgTAT = (totalTA) / 30;
        int avgWT = (totalWait) / 30;
        printf(1, "Average of burstTime is : %d and average of total time is %d and average of waiting time is",avgCBT , avgTAT,avgWT);
        
        exit();
    }
}