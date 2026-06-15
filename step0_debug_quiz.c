// step0: 【復習】このコードには3つのバグがあります。見つけて直してください。
// コンパイル: gcc step0_debug_quiz.c -o step0
// 実行:       ./step0

// ヒント: 前回（#9）で学んだ fopen / NULLチェック / fclose がテーマです

#include <stdio.h>

int main(void) {
    FILE *fp = fopen("color.csv", "r");

    // バグ①修正
    if (fp == NULL) {
        fprintf(stderr, "color.csv を開けません\n");
        return 1;
    }

    char line[256];
    fgets(line, sizeof(line), fp);
    printf("%s", line);

    // バグ②修正
    fclose(fp);
    fp = NULL;

    FILE *fp2 = fopen("log.txt", "w");
    if (fp2 == NULL) {
        return 1;
    }

    fprintf(fp2, "ログ: %s", line);
    fclose(fp2);

    FILE *fp3 = fopen("no_such_dir/out.csv", "w");

    // バグ③修正
    if (fp3 == NULL) {
        fprintf(stderr, "out.csv を開けません\n");
        return 1;
    }

    fprintf(fp3, "data\n");
    fclose(fp3);

    return 0;
}

/*
 * バグの答え
 *
 * ① fopen 直後に NULLチェックがない
 *    → fp が NULL のまま fgets を実行するとエラーになる。
 *    修正: if (fp == NULL) を追加する。
 *
 * ② fclose を呼ばずに fp = NULL している
 *    → ファイルが正しく閉じられない。
 *    修正: fclose(fp); を実行してから fp = NULL にする。
 *
 * ③ fp3 の NULLチェックがない
 *    → 存在しないディレクトリを開こうとすると fp3 が NULL になり、
 *       fprintf を実行するとエラーになる。
 *    修正: if (fp3 == NULL) を追加する。
 */
