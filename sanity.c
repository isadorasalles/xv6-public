#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
    int n, x, pid, retime, rutime, stime;
    int types[3];
    int m[3][4];
    memset(types, 0, sizeof(types));
    memset(m, 0, sizeof(m));

    n = atoi(argv[1]);
    x = 0;
    for (int i = 0; i < 5; i++) {
        for (int f = 0; f < n; f++){
            x = fork ();
            if (x < 0) {  // erro
                exit();
            } 
            else if (x == 0){   // child process
                pid = getpid();
                if (pid % 3 == 0){
                    set_prio(2);
                    for (int j = 0; j < 100; j++){
                        for (int k = 0; k < 1000000; k++){
                            asm("nop");
                        }
                    }
                }
                
                else if (pid % 3 == 1){
                    set_prio(1);
                    for (int j = 0; j < 100; j++){
                        for (int k = 0; k < 1000000; k++){
                            if (k%10000 == 0)
                                yield();   
                        }
                    }
                    
                }
                else if (pid % 3 == 2){
                    set_prio(0);
                    for (int j = 0; j < 100; j++){
                        sleep(1);
                    }
                    
                }
                exit();
            }
        
        }
        for (int f = 0; f < n; f++){
            pid = wait2(&retime, &rutime, &stime);
            types[pid % 3]++;

            m[pid % 3][0] += stime;
            m[pid % 3][1] += retime;
            m[pid % 3][2] += rutime;
            m[pid % 3][3] += stime + retime + rutime;
            
            if (pid % 3 == 0)
                printf(1, "PID = %d  Type: CPU-Bound  Ready time = %d  Run time = %d  Sleeping time = %d\n", 
                pid, retime, rutime, stime);
            else if (pid % 3 == 1)
                printf(1, "PID = %d  Type: S-Bound  Ready time = %d  Run time = %d  Sleeping time = %d\n", 
                pid, retime, rutime, stime);
            else if (pid % 3 == 2)
                printf(1, "PID = %d  Type: I/O-Bound  Ready time = %d  Run time = %d  Sleeping time = %d\n", 
                pid, retime, rutime, stime);
        
        }
        
    }
    printf(1, "\n");
    printf(1, "CPU-Bound metrics:\n");
    if (types[0] == 0)
        printf(1, "  - No processes of this type were runned\n\n");
    else {
        printf(1, "  - Average sleeping time   = %d\n", m[0][0] / types[0]);
        printf(1, "  - Average ready time      = %d\n", m[0][1] / types[0]);
        printf(1, "  - Average running time    = %d\n", m[0][2] / types[0]);
        printf(1, "  - Average turnaround      = %d\n", m[0][3] / types[0]);
        printf(1, "\n");
    }

    printf(1, "S-Bound metrics:\n");
    if (types[1] == 0)
        printf(1, "  - No processes of this type were runned\n\n");
    else {
        printf(1, "  - Average sleeping time   = %d\n", m[1][0] / types[1]);
        printf(1, "  - Average ready time      = %d\n", m[1][1] / types[1]);
        printf(1, "  - Average running time    = %d\n", m[1][2] / types[1]);
        printf(1, "  - Average turnaround      = %d\n", m[1][3] / types[1]);
        printf(1, "\n");
    }

    printf(1, "I/O-Bound metrics:\n");
    if (types[2] == 0)
        printf(1, "  - No processes of this type were runned\n\n");
    else {
        printf(1, "  - Average sleeping time   = %d\n", m[2][0] / types[2]);
        printf(1, "  - Average ready time      = %d\n", m[2][1] / types[2]);
        printf(1, "  - Average running time    = %d\n", m[2][2] / types[2]);
        printf(1, "  - Average turnaround      = %d\n", m[2][3] / types[2]);
        printf(1, "\n");
    }
    exit();
}