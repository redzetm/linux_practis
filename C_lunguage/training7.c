#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // 子プロセス：lsコマンドを実行
        printf("子プロセス（PID: %d）が ls を実行します。\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        perror("exec failed"); // execが失敗した場合のみ表示
    } else {
        // 親プロセス：子の終了を待つ
        printf("親プロセス（PID: %d）が子プロセス（PID: %d）の終了を待ちます。\n", getpid(), pid);
        int status;
        waitpid(pid, &status, 0);
        printf("親プロセス：子プロセスが終了しました（終了コード: %d）。\n", WEXITSTATUS(status));
    }

    return 0;
}