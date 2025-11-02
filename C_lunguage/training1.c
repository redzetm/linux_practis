//問題文：
//標準入力から整数を1つ受け取り、その数が「偶数」か「奇数」かを判定して表示するCプログラムを書いてください。
//- 入力が 4 の場合 → 偶数です
//- 入力が 7 の場合 → 奇数です

/*設計
STDIO.ｈをインクルード
main関数の定義
num変数を初期化
printfで入力（数字）を求める
入った数字が、int型かチェックする
※マイナスでもint型ならOKとする
num変数に入力された数字を格納（scanfを使う）
if文でnum変数が偶数か奇数かを判定（２で割って割り切れれば偶数）
- 偶数の場合、printfで「偶数です」と表示
- 奇数の場合、printfで「奇数です」と表示
return 0で終了
*/
#include <stdio.h>
int main(void){
    int num = 0;
    printf("整数を入力してください：  ");
    if(scanf("%d", &num) == 1){
        if(num % 2 == 0){
            printf("偶数です\n");
        } else {
            printf("奇数です\n");
        }
    } else {
        printf("整数を入力してください \n");
    }
    
    return 0;
}