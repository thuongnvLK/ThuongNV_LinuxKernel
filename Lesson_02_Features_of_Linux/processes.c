#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

// Function to get the current time in nanoseconds
double get_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1e9 + ts.tv_nsec;  // Convert to nanoseconds (double)
}

// Function for an infinite process that prints uptime in nanoseconds
void infinite_process(const char *name) {
    double start_time = get_time_ns();  // Record start time
    printf("%s (PID: %d) started...\n", name, getpid());

    while (1) {
        usleep(100000);  // Sleep for 100 milliseconds to avoid excessive CPU usage
        double elapsed_time = get_time_ns() - start_time;
        printf("%s (PID: %d) has been running for: %.0f ns (%.6f seconds)\n", 
               name, getpid(), elapsed_time, elapsed_time / 1e9);
    }
}

int main() {
    pid_t pid1, pid2;

    // Create child process 1 (default priority)
    pid1 = fork();
    if (pid1 == 0) {
      	nice(-19);
	infinite_process("Child Process 1");
        exit(0);
    }

    // Create child process 2 (lower priority)
    pid2 = fork();
    if (pid2 == 0) {
        nice(19);  // Lower priority (nice = 10)
        infinite_process("Child Process 2");
        exit(0);
    }

    // Parent process also runs indefinitely
    infinite_process("Parent Process");

    return 0;
}

