#include "types.h"
#include "user.h"
#include "stat.h"

int main(void)
{
    changePolicy(4);
    int pid;
    for (int i = 0; i < 10; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            printf(1, "error\n");
            exit();
        }
        if (pid == 0)
        {
            if (i < 2)
                lotteryTickets(20);                 
            if (i >= 2 && i < 4)
                lotteryTickets(10);
            if (i >= 4 && i < 6)
                lotteryTickets(16); 
            if (i >= 6 && i < 8)
                lotteryTickets(18);
            if (i >= 8 && i < 10)
                lotteryTickets(23);
            break;
        }
    }
    if (pid == 0)
    {
        pid = getpid();
        for (int j = 1; j < 10; j++)
        {
            printf(1, "%d : %d\n", pid, j);
        }
    }
    else
    {
        int totalBurst = 0;
        int totalTurnaround = 0;
        int totalWaiting = 0;

        for (int i = 0; i < 10; i++)
        {
            pid = wait();
            int turnAroundTime = getTurnaroundTime(pid);
            int waitTime = getWaitTime(pid);
            int cpuBurstTime = getCpuBurstTime(pid);
            totalTurnaround += turnAroundTime;
            totalWaiting += waitTime;
            totalBurst += cpuBurstTime;
        }
        int avgCpuBurstTime = (totalBurst) / 10;
        int avgTurnAround = (totalTurnaround) / 10;
        int avgWaitingTime = (totalWaiting) / 10;
        printf(1, "Average of burstTime is : %d and average of total time is %d and average of waiting time is",avgCpuBurstTime , avgTurnAround,avgWaitingTime);
    }
    exit();
    
}