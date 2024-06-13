
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define W 80
#define H 22
#define A(x, y, z, a, b, c) float a = x, b = y, c = z
#define M(a, b, x, y, z) float f = 2 / (z + 5); a = 40 + 15 * x * f; b = 10 + 15 * y * f
#define P(i, j) (m[i][0] * x + m[i][1] * y + m[i][2] * z)
#define R(a, b, c, d) float c = cos(a), d = sin(a); m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[1][0] = 0; m[1][1] = c; m[1][2] = -d; m[2][0] = 0; m[2][1] = d; m[2][2] = c

int main() {
    float m[3][3], t = 0;
    int x, y, z, i, j, k;
    char c[W * H];
    memset(c, ' ', sizeof(c));
    for (;;) {
        t += 0.05;
        R(t, 1, c1, s1);
        for (i = 0; i < 8; i++) {
            A((i & 1) * 2 - 1, ((i >> 1) & 1) * 2 - 1, ((i >> 2) & 1) * 2 - 1, x, y, z);
            float px = P(0, 1), py = P(1, 1), pz = P(2, 1);
            float a, b;
            M(a, b, px, py, pz);
            if (a >= 0 && a < W && b >= 0 && b < H) c[(int)b * W + (int)a] = '#';
        }
        for (i = 0; i < H; i++) {
            for (j = 0; j < W; j++) putchar(c[i * W + j]);
            putchar('\n');
        }
        usleep(100000);
        printf("\x1b[%dA", H);
        memset(c, ' ', sizeof(c));
    }
}
