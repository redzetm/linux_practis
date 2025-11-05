#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("親プロセス: PID=%d\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork失敗");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 子プロセス
        printf("子プロセス: PID=%d, 親PID=%d\n", getpid(), getppid());

        // execで新しい処理を実行（ls -l）
        char *args[] = {"/bin/ls", "-l", NULL};
        execvp(args[0], args);

        // execが失敗した場合のみここに到達
        perror("exec失敗");
        exit(EXIT_FAILURE);
    } else {
        // 親プロセス
        int status;
        waitpid(pid, &status, 0);
        printf("親プロセス: 子プロセス(PID=%d)の終了を確認\n", pid);
    }

    return 0;
}