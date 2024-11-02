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
        printf(1, "Usage: sjf_job_length_test <pid>\n");
        exit();
    }

    int target_pid = atoi(argv[1]);
    execute_dummy_work(LONG_MAX);
    execute_dummy_work(LONG_MAX);
    int predicted_job_length = sjf_job_length(target_pid);

    if (predicted_job_length >= 0) {
        printf(1, "Process %d is predicted to run for %d ticks.\n", target_pid, predicted_job_length);
    } else {
        printf(1, "Process with PID: %d. does not exist.\n", target_pid);
    }

    exit();
}

