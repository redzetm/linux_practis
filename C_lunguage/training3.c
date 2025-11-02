/*
問題：
標準入力から文字列を受け取り、それを逆順にして表示するプログラムを書いてください。
条件：
- 入力は最大100文字の英数字からなる文字列とする。
- gets() は使用禁止。fgets() か scanf() を使ってください。
- 逆順の処理はポインタまたは配列を使って行ってください。
- strrev() のような標準関数は使わず、自分で逆転処理を実装してください。

設計
fgets()はstdio.hに含まれているため、インクルードする。
文字列を格納するためのchar型配列を用意する。
※サイズは/0があるから100文字だったら101に設定する。
fgets()を使って標準入力から文字列を読み込む。
文字列の長さを調べるためにstrlen()を使う。string.hもインクルードする。
逆順にするためにforループを使って、配列の最後から最初までアクセスしながら新しい配列に格納する。
最後に逆順にした文字列を表示するためにprintf()を使う。
*/

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 101

int main() {
    char str[MAX_LENGTH];
    char reversed[MAX_LENGTH];
    int length;

    // fgets()を使って標準入力から文字列を読み込む。
    printf("文字列を入力してください: ");
    fgets(str, MAX_LENGTH, stdin);

    // 文字列の長さを調べるためにstrlen()を使う。string.hもインクルードする。
    length = strlen(str);
    if (str[length - 1] == '\n') {
        str[length - 1] = '\0';  // 改行文字を取り除く
        length--;
    }

    // 逆順にするためにforループを使って、配列の最後から最初までアクセス
    //しながら新しい配列に格納する。
    for (int i = 0; i < length; i++) {
        reversed[i] = str[length - 1 - i];
    }
    reversed[length] = '\0';  // 逆順の文字列の終端にNULLを追加

    // 最後に逆順にした文字列を表示するためにprintf()を使う。
    printf("逆順の文字列: %s\n", reversed);

    return 0;
}