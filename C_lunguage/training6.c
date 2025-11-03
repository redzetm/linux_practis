#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // 子プロセス
        printf("子プロセスです。PID: %d, 親PID: %d\n", getpid(), getppid());
    } else {
        // 親プロセス
        printf("親プロセスです。PID: %d, 子PID: %d\n", getpid(), pid);
    }

    return 0;
}