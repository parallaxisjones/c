
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define Z(i,j) m[i][j]
#define Q 0.4
#define T 0.1
#define P 3.14

float m[4][4], q = Q;

void R(float t) {
    float c = cos(t), s = sin(t);
    Z(0,0) = Z(1,1) = Z(2,2) = c;
    Z(1,0) = Z(2,1) = s;
    Z(2,0) = Z(0,1) = -s;
}

void M(float x, float y, float z, float* a, float* b) {
    *a = 2 * x / (z + 4);
    *b = 2 * y / (z + 4);
}

int main() {
    float x, y, z, a, b;
    int i, j, c[80][22];
    memset(c, 32, sizeof(c));

    for (;;) {
        q += T;
        R(q);
        memset(c, 32, sizeof(c));
        
        for (i = 0; i < 8; ++i) {
            x = (i & 1) * 2 - 1;
            y = (i & 2) - 1;
            z = (i & 4) / 2 - 1;
            M(Z(0,0) * x + Z(1,0) * y + Z(2,0) * z,
              Z(0,1) * x + Z(1,1) * y + Z(2,1) * z,
              Z(0,2) * x + Z(1,2) * y + Z(2,2) * z,
              &a, &b);
            a = 40 + 15 * a;
            b = 10 + 15 * b;
            if (a >= 0 && a < 80 && b >= 0 && b < 22)
                c[(int)a][(int)b] = '#';
        }
        
        for (j = 0; j < 22; ++j) {
            for (i = 0; i < 80; ++i)
                putchar(c[i][j]);
            putchar('\n');
        }
        
        usleep(100000);
        printf("\x1b[23A");
    }
}
