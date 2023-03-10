#ifndef ZORA_LEV_C
#define ZORA_LEV_C

#include <string.h>

#define ZORA_LEV_MAX 69

int Zora_min(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int Zora_levensthein_distance(char *s, char *t) {
    int m = strlen(s), n = strlen(t);

    if (m == 0) return n;
    if (n == 0) return m;

    if (m > ZORA_LEV_MAX/3 || n > ZORA_LEV_MAX/3) return 0;

    int d[ZORA_LEV_MAX][ZORA_LEV_MAX];
    int i, j;

    for (i = 0; i <= m; i++) d[i][0] = i;
    for (j = 0; j <= n; j++) d[0][j] = j;

    for (j = 1; j <= n; j++) {
        for (i = 1; i <= m; i++) {
            int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
            d[i][j] = Zora_min(d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost);
        }
    }

    return d[m][n];
}

int Zora_find_similar_string(char* s, char** arr, int len) {
    int i, min_dist = ZORA_LEV_MAX + 1, min_idx = 0;

    for (i = 0; i < len; i++) {
        int dist = Zora_levensthein_distance(s, arr[i]);
        if (dist >= 0 && dist < min_dist) {
            min_dist = dist;
            min_idx = i;
        }
    }
    return min_idx;
}

#endif
