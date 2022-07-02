#include "types.h"
#include "user.h"
#include "stat.h"

int main(void)
{
    changePolicy(1);
    int pid;
    for (int i = 0; i < 10; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            printf(1, "fork error\n");
            exit();
        }
        
        if(pid == 0)
        	break;
    }
    if (pid == 0)
    {

        pid = getpid();

        

        for (int j = 1; j < 1000; j++)
        {
            printf(1, "%d : %d\n", pid, j);
        }
    
        int cpuBurstTime = getCpuBurstTime(pid);
        int turnAroundTime = getTurnaroundTime(pid);
        int waitTime = getWaitTime(pid);

        sleep(2000 + 10 * pid);

        printf(1, "PID : %d burstTime : %d\n", pid, cpuBurstTime);
        printf(1, "PID : %d Turnaround : %d\n", pid, turnAroundTime);
        printf(1, "PID : %d Waiting : %d\n", pid, waitTime);
        exit();
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
            int waitingTime = getWaitTime(pid);
            int burstTime = getstartTime(pid);
            totalTurnaround += turnAroundTime;
            totalWaiting += waitingTime;
            totalBurst += burstTime;
        }
        int avgCBT = (totalBurst) / 10;
        int avgTAT = (totalTurnaround) / 10;
        int avgWT = (totalWaiting) / 10;
        printf(1, "Average of burstTime is : %d and average of total time is %d and average of waiting time is",avgCBT , avgTAT,avgWT);
    }
    exit();
}
