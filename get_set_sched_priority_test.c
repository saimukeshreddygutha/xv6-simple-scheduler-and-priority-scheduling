#include "types.h"
#include "stat.h"
#include "user.h"



int main() {
    printf(1, "Testing set_sched_priority and get_sched_priority\n");
    printf(1, "Priority of the current process(PID: %d), is %d\n", getpid(), get_sched_priority(getpid()));
    set_sched_priority(1);
    printf(1, "Priority of the current process(PID: %d), is changed to %d\n", getpid(), get_sched_priority(getpid()));
    
    exit();
}
