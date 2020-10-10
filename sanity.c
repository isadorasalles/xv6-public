#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
    int  k, n, x, pid, retime, rutime, stime;
    int sum_retime, sum_rutime, sum_stime;

    n = atoi(argv[1]);
    x = 0;

    for (int i = 0; i < 5*n; i++ ) {
        x = fork ();
        if (x == 0) {  //parent
        wait();
        } 
        else {   // child
            printf(1, "Process %d created\n", k);
            pid == getpid();
            if (pid % 3 == 0){
                set_prio(2);
                for (int j = 0; j < 100; j++){
                    for (int k = 0; k < 1000000; k++){
                    }
                }
                printf(0, "CPU-Bound %d\n", pid);
            }
            
            else if (pid % 3 == 1){
                set_prio(1);
                for (int j = 0; j < 100; j++){
                    for (int k = 0; k < 1000000; k++){
                        if (k%100 == 0)
                            yield();   
                    }
                }
                printf(0, "S-Bound%d\n", pid);
            }
            else if (pid % 3 == 2){
                set_prio(0);
                for (int j = 0; j < 100; j++){
                    sleep(1);
                }
                printf(0, "IO-Bound%d\n",pid);
            }
            exit();
        
        }
        wait2(&retime,&rutime,&stime);
        sum_retime += retime;
        sum_rutime += rutime;
        sum_stime += stime;
    }
    sum_retime /= 5*n;
    sum_rutime /= 5*n;
    sum_stime /= 5*n;
    printf(0, "%d %d %d %d\n", sum_retime, sum_rutime, sum_stime, sum_retime+sum_rutime+sum_stime);
    exit();
}