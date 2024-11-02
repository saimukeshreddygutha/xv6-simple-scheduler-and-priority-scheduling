#include "types.h"
#include "stat.h"
#include "user.h"
#include "limits.h"
void execute_dummy_work(unsigned long long int loop_count) {
    for (unsigned long long int i = 0; i <= loop_count - 1; i++) {
        asm("nop");
    }
}

int main(int argc, char *argv[]) {
    int current_pid = getpid();
    printf(1, "Current Process PID: %d\n", current_pid);

    if (argc < 2) {
        printf(1, "Usage: ticktest <pid>\n");
        exit();
    }

    int target_pid = atoi(argv[1]);
    execute_dummy_work(LONG_MAX);
    int ticks = ticks_running(target_pid);
    if (ticks > 0) {
        printf(1, "Process %d has run for %d ticks.\n", target_pid, ticks);
    } 
    else if(ticks < 0){
        printf(1, "ticks_running() returned -1 for process %d as it does not exist in process table.\n", target_pid);
    }
    else{
    	printf(1, "Process isn't scheduled for running yet\n", target_pid);
    }
    
    exit();
}

