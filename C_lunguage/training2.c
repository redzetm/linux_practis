/*🧠 問題：最大値を求めるプログラムを書こう
問題文：
標準入力から整数を2つ受け取り、そのうち大きい方の値を表示するCプログラムを書いてください。
出力例：
- 入力が 5 と 9 の場合 → 最大値は 9 です
- 入力が -3 と -7 の場合 → 最大値は -3 です

設計
defineでマクロで大きい値を返すマクロを定義
メイン関数の定義
入力される２つの値の変数を初期化
printfで２つの整数の入力を求める
入った数字が、int型かチェックする
※マイナスでもint型ならOKとする
scanfで最初の数字を変数に格納
scanfで次の数字を変数に格納
マクロを使って大きい方の値を求める
printfで「最大値は〇〇です」と表示
return 0で終了

*/

#include <stdio.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))

int main(void){
    int num1 = 0;
    int num2 = 0;
    
    printf("2つの整数を入力してください（スペースで区切る）： ");
    if(scanf("%d %d", &num1, &num2) == 2){
        int max_value = MAX(num1, num2);
        printf("最大値は %d です\n", max_value);
    } else if(scanf("%d %d", &num1, &num2) != 2){
        printf("整数を2つ入力してください \n");
    }
    
    return 0;
}