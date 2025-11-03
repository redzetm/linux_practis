/*
🧪問題：ファイルに文字列を書き込むプログラムを作成せよ
以下の仕様に従って、C言語でプログラムを書いてください：
🔧仕様
- ファイル名は "output.txt" とする
- ファイルが存在しない場合は新規作成、存在する場合は上書き
- 書き込む文字列は "Hello, Linux system programming!\n" とする
- 書き込み後、ファイルを必ず閉じること
💡ヒント
- open()、write()、close() を使う
- 必要なら #include <fcntl.h> や #include <unistd.h> を使う
- パーミッションは 0644（rw-r--r--）でよい
設計
1. 必要なヘッダーファイルをインクルードする
open(), write(), close() のために <fcntl.h> と <unistd.h> をインクルードする。
書き込み専用のファイルを作成するために <sys/stat.h> もインクルードする。
書き込み専用ファイルは、本プログラムと同じディレクトリに生成する。
#define OUTPUT_TXT "output.txt"定義して、修正しやすくする。
2. main関数を定義する
3. open()でファイルを開く
- O_WRONLY | O_CREAT | O_TRUNC フラグを使用して、書き込み専用でファイルを開く。
- パーミッションは 0644 に設定する。
- open()が失敗した場合、エラーメッセージを表示して終了する。
4. write()で文字列を書き込む
- "Hello, Linux system programming!\n" をファイルに書き込む。
- write()が失敗した場合、エラーメッセージを表示して終了する。
5. close()でファイルを閉じる
- ファイルディスクリプタを閉じる。
- close()が失敗した場合、エラーメッセージを表示して終了する。
6. 正常終了
- プログラムを正常に終了する。
*/
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#define OUTPUT_TXT "output.txt"
#define WRITE_STRING "Hello, Linux system programming!\n"

int main(void) {
    
    int fd = open(OUTPUT_TXT, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("ファイルのオープンに失敗しました");
        exit(EXIT_FAILURE);
    }
    
    ssize_t bytes_written = write(fd, WRITE_STRING, sizeof(WRITE_STRING) - 1);
    if (bytes_written == -1) {
        perror("ファイルへの書き込みに失敗しました");
        close(fd);
        exit(EXIT_FAILURE);
    }

    
    if (close(fd) == -1) {
        perror("ファイルのクローズに失敗しました");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}