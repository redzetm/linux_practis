/*
🧩 問題：学生情報の表示
以下の条件に従って、C言語でプログラムを作成してください。
🔧 条件
- 学生の情報を格納する構造体 Student を定義する。
- メンバーは 名前（char型配列）、年齢（int）、成績（float）。
- Student 型の変数を1つ作成し、ポインタを使ってそのメンバーに値を代入する。
- ポインタを使って、構造体の内容を表示する。
設計
1. 構造体 Student を定義し、名前、年齢、成績のメンバーを持たせる。
2. main 関数内で Student 型の変数 student を宣言する。
3. Student 型のポインタ studentPtr を宣言し、student のアドレスを代入する。
4. studentPtr を使って、名前、年齢、成績のメンバーに値を代入する。
5. studentPtr を使って、構造体の内容を表示する。

*/

#include <stdio.h>
#include <string.h>

typedef struct Student {
    char name[100];
    int age;
    float grade;
} Student;

int main() {
    Student student;
    Student *studentPtr = &student;

    // ポインタを使ってメンバーに値を代入
    printf("名前を入力してください: ");
    fgets(studentPtr->name, sizeof(studentPtr->name), stdin);
    printf("年齢を入力してください: ");
    if(scanf("%d", &studentPtr->age) != 1){
        printf("年齢は整数で入力してください。\n");
        return 1;
    }
        printf("成績を入力してください: ");
    if(scanf("%f", &studentPtr->grade) != 1){
        printf("成績は数値で入力してください。\n");
        return 1;
    }

    // ポインタを使って構造体の内容を表示
    printf("\n学生情報:\n");
    printf("名前: %s", studentPtr->name);
    printf("年齢: %d\n", studentPtr->age);
    printf("成績: %.2f\n", studentPtr->grade);

    return 0;
}