#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"
#include "limits.h"

void execute_dummy_work(unsigned long long int loop_count) {
    for (unsigned long long int i = 0; i <= loop_count - 1; i++) {
        asm("nop"); 
    }
}

int main(void) {
    const int num_children = 10;  
    int child_pids[num_children];  
    int parent_pid = getpid();
    printf(1, "Parent process PID %d started\n", getpid());
    int pstart_time = uptime();
    for (int i = 0; i < num_children; i++) {
        int pid = fork();
        if (pid < 0) {
            printf(1, "Fork failed for child %d!\n", i);
            exit();
        } else if (pid == 0) {
        	int start_time = uptime();
        	if(pid==parent_pid+2){
            	execute_dummy_work(LONG_MAX);
            	execute_dummy_work(LONG_MAX);
            	execute_dummy_work(LONG_MAX);
            	execute_dummy_work(LONG_MAX);
            	execute_dummy_work(LONG_MAX);
            	
		}

        execute_dummy_work(LONG_MAX);
        execute_dummy_work(LONG_MAX);

        int end_time = uptime();
        printf(1, " %d \t %d \t \t %d \t \t %d \t \t%d\n", i, getpid(), sjf_job_length(getpid()), get_sched_priority(getpid()),end_time-start_time);
		
        exit();  
        } else {
            child_pids[i] = pid;
            
        }
    }
    printf(1, "Parent process checking ticks for all children...\n");
    for (int i = 0; i < num_children; i++) {

        printf(1, "Child: %d PID: %d has been created \n", i, child_pids[i]);
	if(child_pids[i]%2 == 0)set_sched_priority_for_pid(child_pids[i], 1);
    }
	printf(1, "CHILD \t PID         PREDICTCED BURST \t PRIORITY \t TICKS\n");
    for (int i = 0; i < num_children; i++) {
        wait();
    }

    printf(1, "Parent process: All children have finished execution.\n");
    int pend_time = uptime();
    printf(1, "Parent process took %d ticks to complete\n", pend_time-pstart_time);
    exit(); 
}

