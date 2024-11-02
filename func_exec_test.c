#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void benchmark_command(char *command[], const char *description) {
    int start_time, end_time;

    printf(1, "\nExecuting: %s\n", description);
    start_time = uptime();

    if (fork() == 0) {
        exec(command[0], command);
        printf(1, "Exec failed for %s\n", command[0]);
        exit();
    } else {
        wait();
    }
    end_time = uptime();

    int elapsed_time = end_time - start_time;
    printf(1, "Execution time for %s: %d ticks\n", description, elapsed_time);
}

int main(void) {
    printf(1, "Benchmarking commands under the current scheduler...\n");

    // Test 1: Run stressfs
    char *stressfs_cmd[] = {"stressfs", 0};
    benchmark_command(stressfs_cmd, "stressfs");

    // Test 2: Run ls
    char *ls_cmd[] = {"ls", 0};
    benchmark_command(ls_cmd, "ls");

    // Test 3: Run cat on README
    char *cat_cmd[] = {"cat", "README", 0};
    benchmark_command(cat_cmd, "cat README");

    // Test 4: Run uniq on test.txt
    char *uniq_cmd[] = {"uniq", "test.txt", 0};
    benchmark_command(uniq_cmd, "uniq test.txt");

    // Test 5: Run find on root directory
    char *find_cmd[] = {"find", ".", "-name", "README", 0};
    benchmark_command(find_cmd, "find . -name README");
    

    // Test 6: Execute a pipe (cat README | uniq)
    int start_time = uptime();
    if (fork() == 0) {
        int pipe_fd[2];
        pipe(pipe_fd);

        if (fork() == 0) {
            close(1);          
            dup(pipe_fd[1]);     
            close(pipe_fd[0]);  
            close(pipe_fd[1]);  

            exec("cat", (char *[]){"cat", "README", 0});
            printf(1, "Exec failed for cat\n"); 
            exit();
        }

        if (fork() == 0) {
            close(0);          
            dup(pipe_fd[0]);     
            close(pipe_fd[1]);  
            close(pipe_fd[0]);   

            exec("uniq", (char *[]){"uniq", 0});
            printf(1, "Exec failed for uniq\n"); 
            exit();
        }

        close(pipe_fd[0]);
        close(pipe_fd[1]);
        
        wait();
        wait();
        int end_time = uptime();
        printf(1, "Execution time for %s: %d ticks\n", "cat README | uniq",end_time-start_time);
        exit();
    } else {
        wait();  
    }

    printf(1, "Benchmarking completed.\n");
    exit();
}


