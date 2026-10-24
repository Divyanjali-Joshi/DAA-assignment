
#include <stdio.h>
#include <string.h>

int main() {
    int n, W, i, j, r;
    int weight[101], value[101];
    int dp[101][1001];
    char line[200];

    FILE *out = fopen("result.txt", "w");

    if (out == NULL) {
        printf("Cannot create result.txt\n");
        return 1;
    }

    while (fgets(line, sizeof(line), stdin)) {
        if (strncmp(line, "#Test", 5) != 0)
            continue;

        if (!fgets(line, sizeof(line), stdin) ||
            sscanf(line, "%d %d", &n, &W) != 2) {
            printf("Invalid test case header\n");
            fclose(out);
            return 1;
        }

        if (n < 1 || n > 100 || W < 0 || W > 1000) {
            printf("Invalid input size\n");
            fclose(out);
            return 1;
        }

        for (i = 0; i < n; i++) {
            if (!fgets(line, sizeof(line), stdin) ||
                sscanf(line, "%d %d", &weight[i],
                       &value[i]) != 2) {
                printf("Invalid item data\n");
                fclose(out);
                return 1;
            }
        }

        for (j = 0; j <= W; j++)
            dp[0][j] = 0;

        printf("\nTest case: n=%d, W=%d\n", n, W);

        for (i = 1; i <= n; i++) {
            for (j = 0; j <= W; j++) {
                if (weight[i - 1] <= j) {
                    int include = value[i - 1] +
                        dp[i - 1][j - weight[i - 1]];
                    int exclude = dp[i - 1][j];

                    dp[i][j] = (include > exclude)
                               ? include : exclude;
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }

            printf("\nAfter item %d:\n", i);
            printf("Item/Cap ");

            for (j = 0; j <= W; j++)
                printf("%4d", j);

            printf("\n");

            for (r = 0; r <= i; r++) {
                printf("%4d     ", r);

                for (j = 0; j <= W; j++)
                    printf("%4d", dp[r][j]);

                printf("\n");
            }
        }

        printf("\nMaximum value = %d\n", dp[n][W]);

        fprintf(out,
                "#Test case input (%d %d) test result: %d\n",
                n, W, dp[n][W]);
    }

    fclose(out);
    printf("\nResults saved in result.txt\n");

    return 0;
}
