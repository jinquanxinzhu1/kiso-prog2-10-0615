// step0: 【復習】このコードには3つのバグがあります。見つけて直してください。
// コンパイル: gcc step0_debug_quiz.c -o step0
// 実行:       ./step0

// ヒント: 前回（#9）で学んだ fopen / NULLチェック / fclose がテーマです

#include <stdio.h>

int main(void) {
    FILE *fp = fopen("color.csv", "r");

    char line[256];
    fgets(line, sizeof(line), fp);   // バグ① fopen が失敗していたら？
    printf("%s", line);

    fp = NULL;                        // バグ② ファイルを閉じていない

    FILE *fp2 = fopen("log.txt", "w");
    if (fp2 == NULL) {
        return 1;
    }

    fprintf(fp2, "ログ: %s", line);
    fclose(fp2);

    FILE *fp3 = fopen("no_such_dir/out.csv", "w");
    fprintf(fp3, "data\n");          // バグ③ fp3 が NULL かもしれない
    fclose(fp3);

    return 0;
}

/*
 * バグの答えはここに書く（スペースを開けてから確認すること）
 *
 *
 *
 *
 *
 *
 * ① fopen 直後に NULLチェックがない
 *    → fp が NULL のまま fgets を呼ぶとクラッシュ
 *    修正: if (fp == NULL) {
 *              fprintf(stderr, "開けません\n");
 *              return 1;
 *          }
 *
 * ② fclose を呼ばずに fp = NULL している
 *    → ファイルが正しく閉じられない
 *    修正: fclose(fp); の後に fp = NULL;
 *
 * ③ fp3 の NULLチェックがない
 *    → 存在しないディレクトリへの書き込みでクラッシュ
 *    修正: if (fp3 == NULL) {
 *              fprintf(stderr, "開けません\n");
 *              return 1;
 *          }
 */
