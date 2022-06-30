//
// Created by aradf on 1/27/2022.
//

#include "types.h"
#include "user.h"
#include "stat.h"


int IOHeavyFunction(void){
    int output=0;
    int pid=getpid();
    for(int i=0;i<300;i++){
        printf(1,"%d : %d\n",pid,i);
    }
    int turnaroundTime = getTurnaroundTime();
    int waitingTime = getWaitingTime();
    int cbt = getCBT();
    sleep(1400+20*pid);
    printf(1,"IO Task:Turnaround time of %d : %d\n" , pid , turnaroundTime);
    printf(1,"IO Task:Waiting time of %d : %d\n" , pid , waitingTime);
    printf(1,"IO Task:CBT of %d : %d\n" , pid , cbt);
    return output;
}
int BalancedFunction(void){
    int output=0;
    int pid=getpid();
    for(int i=0;i<300;i++){
        if(i%3==0)
            printf(1,"%d : %d\n",pid,i);
        else
            output+=i;
    }
    int turnaroundTime = getTurnaroundTime();
    int waitingTime = getWaitingTime();
    int cbt = getCBT();
    sleep(1400+20*pid);
    printf(1,"Balanced Task:Turnaround time of %d : %d\n" , pid , turnaroundTime);
    printf(1,"Balanced Task:Waiting time of %d : %d\n" , pid , waitingTime);
    printf(1,"Balanced Task:CBT of %d : %d\n" , pid , cbt);
    return output;
}

int
main(void) {
    changePolicy(4);
    int pid;
    for (int i = 0; i < 30; i++) {
        if ((pid = fork()) != 0) {
            if(pid<0){
                printf(1,"Fork failed!\n");
                exit();
            }
            else{
                printf(1,"Fork %d successful!\n",i+1);
            }
        } else {
            sleep(20);

            if (i < 15) {
                IOHeavyFunction();
            } else {
                BalancedFunction();
            }
            break;
        }
    }
    if (pid!=0){
        for(int i=0;i<30;i++) {
            wait();
            printf(1, "Wait %d finished!",i+1);
        }
    }
    exit();
}