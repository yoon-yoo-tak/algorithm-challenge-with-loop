import java.util.*;

public class Solution {
    static final long mod = 1000000007;
    static int[] dx = {1, 0, -1, 0};
    static int[] dy = {0, 1, 0, -1};

    public int solution(int[][] grid, int[] d, int k) {

        int n = grid.length;
        int m = grid[0].length;
        int L = d.length;

        // dp[i][j] := i에서 출발하여 경로 d를 따라 j로 갈 수 있는 경우의 수
        long[][] dp = new long[n * m][n * m];

        for (int i = 0; i < n * m; i++){
            long[][] tmp = new long[L + 1][n * m];
            tmp[0][i] = 1;
            for (int j = 0; j < L; j++){
                for (int l = 0; l < n * m; l++){
                    if (tmp[j][l] != 0){
                        int x = l / m;
                        int y = l % m;
                        for (int dir = 0; dir < 4; dir++){
                            int nx = x + dx[dir];
                            int ny = y + dy[dir];
                            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                            if (grid[nx][ny] == grid[x][y] + d[j]){
                                int nxtIdx = nx * m + ny;
                                tmp[j + 1][nxtIdx] = tmp[j + 1][nxtIdx] + tmp[j][l];
                                tmp[j + 1][nxtIdx] %= mod;
                            }
                        }
                    }
                }
            }

            for (int j = 0; j < n * m; j++){
                dp[i][j] = tmp[L][j];
            }
        }

        long[][] ret = pow(dp, k, n * m);
        long answer = 0;

        for (int i = 0; i < n * m; i++){
            for (int j = 0; j < n * m; j++){
                answer = (answer + ret[i][j]) % mod;
            }
        }

        return (int)answer;
    }

    public long[][] pow(long[][] A, long x, int n){ // A^x
        long[][] ret = new long[n][n];
        for (int i = 0; i < n; i++){
            ret[i][i] = 1;
        }
        long[][] B = A;
        while (x > 0){
            if ((x&1) == 1){
                ret = mult(ret, B, n);
            }
            B = mult(B, B, n);
            x >>= 1;
        }
        return ret;
    }

    public long[][] mult(long[][] A, long[][] B, int n){
        long[][] C = new long[n][n];
        for (int i = 0; i < n; i++){
            for (int k = 0; k < n; k++){
                if (A[i][k] != 0){
                    for (int j = 0; j < n; j++){
                        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
                    }
                }
            }
        }
        return C;
    }
}