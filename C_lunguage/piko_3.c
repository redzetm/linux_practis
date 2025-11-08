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
        // 子プロセス：別プログラム（ls）を実行
        printf("子プロセス: PID=%d, 実行開始\n", getpid());
        execlp("ls", "ls", "-l", NULL);  // ls -l を実行
        perror("exec failed");  // exec失敗時のみここに来る
        exit(1);
    } else {
        // 親プロセス：子の終了を待つ
        int status;
        pid_t wpid = waitpid(pid, &status, 0);

        if (wpid == -1) {
            perror("waitpid failed");
            return 1;
        }

        printf("親プロセス: 子PID=%d の終了を確認\n", wpid);

        if (WIFEXITED(status)) {
            printf("子は正常終了: status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("子はシグナルで終了: signal=%d\n", WTERMSIG(status));
        } else {
            printf("子は異常終了\n");
        }
    }

    return 0;
}