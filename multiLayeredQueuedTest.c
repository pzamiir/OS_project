#include "types.h"
#include "user.h"
#include "stat.h"



int
main(void)
{
    changePolicy(3);
    //changePriority(1);
    int i=0;
    //int k = getpid();
    //printf(1,"parent pid : %d\n" , k);
    int pid;
    for (i=0 ; i< 60 ; i++) {
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
        if (i < 10) {
        changePriority(1);
        } 
        else if (i < 20 && i > 9) {
        changePriority(2);
        }
        else if (i < 30 && i > 19) {
        changePriority(3);
        }
        else if (i < 40 && i > 29) {
        changePriority(4);
        }
        else if (i < 50 && i > 39) {
        changePriority(5);
        }
        else if (i < 60 && i > 49) {
        changePriority(6);
        }
        for (int j=1 ; j<200 ; j++) {
            printf(1,"%d : %d\n" , pid , j);
        }
        int turnaroundTime = getTurnaroundTime();
        int waitingTime = getWaitingTime();
        int cbt = getCBT();
        sleep(1400+20*pid);
        printf(1,"Turnaround time of %d : %d\n" , i , turnaroundTime);
        printf(1,"Waiting time of %d : %d\n" , i , waitingTime);
        printf(1,"CBT of %d : %d\n" , i , cbt);
        exit();
    } else {
        changePriority(1);
        for (int i=0 ; i<60 ; i++) {
            wait();
            printf(1,"Wait %d is finished\n",i);
        }
    }
    exit();
}