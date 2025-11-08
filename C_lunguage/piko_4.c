#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int status;

    //親プロセスのPIDを表示する。
    printf("親プロセス: PID=%d\n", getpid());

    pid = fork();   //子プロセスの生成（ここから親子プロセスに分岐）
    if (pid < 0) {  // fork失敗時の処理　PIDが負の値になる
        perror("fork 失敗");    //errnoに基づくエラーメッセージを表示
        exit(EXIT_FAILURE);    //EXIET_FAILURE(定義では1)で異常終了
    }

    if (pid == 0) {     //fork()で子プロセスが受け取るPIDは0
        // 子プロセス
        printf("子プロセス: PID=%d, 親PID=%d\n", getpid(), getppid());
        execlp("ls", "ls", "-l", NULL);  // ls -l を実行
        perror("exec 失敗");  // exec 失敗時のみ実行される
        exit(EXIT_FAILURE);
    } else {
        // 親プロセス
        printf("親プロセス: 子プロセス %d の終了を待ちます\n", pid);
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid 失敗");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("子プロセスは正常終了しました。終了コード=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("子プロセスはシグナル %d により終了しました\n", WTERMSIG(status));
        } else {
            printf("子プロセスは異常な終了をしました\n");
        }
    }

    return 0;
}