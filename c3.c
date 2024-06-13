#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h> // For abs function

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
    float vertices[8][3], transformed[8][2];
    int faces[6][4] = {
        {0, 1, 3, 2},
        {4, 5, 7, 6},
        {0, 1, 5, 4},
        {2, 3, 7, 6},
        {0, 2, 6, 4},
        {1, 3, 7, 5}
    };
    char shades[] = " .:-=+*#%@";

    memset(c, ' ', sizeof(c));

    for (;;) {
        t += 0.05;
        R(t, 1, c1, s1);

        for (i = 0; i < 8; i++) {
            A((i & 1) * 2 - 1, ((i >> 1) & 1) * 2 - 1, ((i >> 2) & 1) * 2 - 1, x, y, z);
            float px = P(0, 1), py = P(1, 1), pz = P(2, 1);
            vertices[i][0] = px;
            vertices[i][1] = py;
            vertices[i][2] = pz;
            float a, b;
            M(a, b, px, py, pz);
            transformed[i][0] = a;
            transformed[i][1] = b;
        }

        for (i = 0; i < 6; i++) {
            float normal_x = 0, normal_y = 0, normal_z = 0;
            for (j = 0; j < 4; j++) {
                int next = (j + 1) % 4;
                normal_x += (vertices[faces[i][j]][1] - vertices[faces[i][next]][1]) * (vertices[faces[i][j]][2] + vertices[faces[i][next]][2]);
                normal_y += (vertices[faces[i][j]][2] - vertices[faces[i][next]][2]) * (vertices[faces[i][j]][0] + vertices[faces[i][next]][0]);
                normal_z += (vertices[faces[i][j]][0] - vertices[faces[i][next]][0]) * (vertices[faces[i][j]][1] + vertices[faces[i][next]][1]);
            }
            float shade = normal_z / sqrt(normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);
            char shade_char = shades[(int)((shade + 1) * 4.5)];

            for (j = 0; j < 4; j++) {
                int next = (j + 1) % 4;
                int x0 = (int)transformed[faces[i][j]][0], y0 = (int)transformed[faces[i][j]][1];
                int x1 = (int)transformed[faces[i][next]][0], y1 = (int)transformed[faces[i][next]][1];
                int dx = abs(x1 - x0), dy = abs(y1 - y0);
                int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
                int err = (dx > dy ? dx : -dy) / 2, e2;
                while (1) {
                    if (x0 >= 0 && x0 < W && y0 >= 0 && y0 < H) c[y0 * W + x0] = shade_char;
                    if (x0 == x1 && y0 == y1) break;
                    e2 = err;
                    if (e2 > -dx) { err -= dy; x0 += sx; }
                    if (e2 < dy) { err += dx; y0 += sy; }
                }
            }
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
