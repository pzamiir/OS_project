#include "types.h"
#include "user.h"
#include "stat.h"



int
main(void)
{
    changePolicy(2);
    //changePriority(1);
    int i=0;
    //int k = getpid();
    //printf(1,"parent pid : %d\n" , k);
    int pid;
    for (i=0 ; i< 30 ; i++) {
        if ((pid=fork()) !=0) {
            if (pid < 0){
                printf(1,"fork error\n");
                exit();
            }
            printf(1,"fork %d completed\n",i+1);
        } else {
            changePriority(1);
            sleep(20);
            break;
        }
    }

    if (pid == 0) {
        //changePriority(6);
        pid = getpid();
        if (i < 5) {
        changePriority(6);
        } 
        else if (i < 10 && i > 4) {
        changePriority(5);
        }
        else if (i < 15 && i > 9) {
        changePriority(4);
        }
        else if (i < 20 && i > 14) {
        changePriority(3);
        }
        else if (i < 25 && i > 19) {
        changePriority(2);
        }
        else if (i < 30 && i > 24) {
        changePriority(1);
        }
        for (int j=1 ; j<250 ; j++) {
            printf(1,"%d : %d\n" , pid , j);
        }
        int turnaroundTime = getTurnaroundTime();
        int waitingTime = getWaitingTime();
        int cbt = getCBT();
        sleep(1400+20*pid);
        printf(1,"Turnaround time of %d : %d\n" , i , turnaroundTime);
        printf(1,"Waiting time of %d : %d\n" , i , waitingTime);
        printf(1,"CBT of %d : %d\n" , i, cbt);
        exit();
    } else {
        changePriority(1);
        for (int i=0 ; i<30 ; i++) {
            wait();
            printf(1,"Wait %d is finished\n",i);
        }
    }
    exit();
}