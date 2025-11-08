#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int status;

    
    printf("親プロセス: PID=%d\n", getpid());   //親プロセスのPIDを表示する。

    pid = fork();               //子プロセスの生成（ここから親子プロセスに分岐）
    if (pid < 0) {              // fork失敗時の処理　PIDが負の値になる
        perror("fork 失敗");    //errnoに基づくエラーメッセージを表示
        exit(EXIT_FAILURE);    //EXIT_FAILURE(定義では1)で異常終了
    }

    if (pid == 0) {             //fork()で子プロセスが受け取るPIDは0、if文のブロック実行
        // 子プロセス
        //printfで子プロセスのPIDと親プロセスのPIDを表示
        printf("子プロセス: PID=%d, 親PID=%d\n", getpid(), getppid());
        //execlp()でlsコマンドを実行。ほかのexec()系にしなかった理由はPATH環境変数を利用するため
        //execlp()は成功したときは値を返さないが、失敗したら-1を返すのとerrnoに基づくエラーメッセージを表示
        //なのでperror()を使っている
        execlp("ls", "ls", "-l", NULL);  // ls -l を実行
        perror("exec 失敗");  // execlp() 失敗時のみ実行される
        exit(EXIT_FAILURE);     // execlp()失敗時に異常終了。exit(EXIT_FAILURE)は1で定義されているから
        //exit(1)と同じ意味となる
    } else {
        // 親プロセス
        printf("親プロセス: 子プロセス %d の終了を待ちます\n", pid);    //親プロセスのPIDと子プロセスのPIDを表示
        if (waitpid(pid, &status, 0) == -1) {   //子プロセスのidがpidに入ってるのでその子プロセスの結果が
                                                //statusに入るまでブロッキングで待つ
            perror("waitpid 失敗");             //waitpid()失敗時(-1のとき)のエラーメッセージを表示
            exit(EXIT_FAILURE);                 //waitpid()失敗時に異常終了    EXIT_FAILUREは1で定義されている 
        }

        if (WIFEXITED(status)) {    //子プロセスが正常終了したかどうかを確認
            printf("子プロセスは正常終了しました。終了コード=%d\n", WEXITSTATUS(status));   
            //WEXITSTATUS(status)で子プロセスの終了コードを取得
        } else if (WIFSIGNALED(status)) {   //子プロセスがシグナルによって終了したかどうかを確認
            printf("子プロセスはシグナル %d により終了しました\n", WTERMSIG(status));   
            //WTERMSIG(status)で終了に使われたシグナル番号を取得
        } else {
            printf("子プロセスは異常な終了をしました\n");
        }
    }

    return 0; //正常終了
}