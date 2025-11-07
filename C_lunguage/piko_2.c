#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main(void) {
    pid_t pid = fork();
 
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
 
    if (pid == 0) {
        // 子プロセス
        printf("子プロセス: PID=%d, PPID=%d\n", getpid(), getppid());
        exit(42);  // 任意の終了コード
    } else {
        // 親プロセス
        int status;
        pid_t wpid = wait(&status);
 
        if (wpid == -1) {
            perror("wait failed");
            return 1;
        }
 
        printf("Parent: waited for PID=%d\n", wpid);
 
        if (WIFEXITED(status)) {
            printf("子プロセス exited normally with status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("子プロセス terminated by signal %d\n", WTERMSIG(status));
        } else {
            printf("子プロセス ended abnormally\n");
        }
    }
 
    return 0;
}