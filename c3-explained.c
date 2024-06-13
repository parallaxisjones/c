#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h> // For abs function

#define W 80
#define H 22

// Macro to define a 3D point (x, y, z) with local variables (a, b, c)
#define A(x, y, z, a, b, c) float a = x, b = y, c = z

// Macro to convert 3D point (x, y, z) to 2D point (a, b) on screen
#define M(a, b, x, y, z) float f = 2 / (z + 5); a = 40 + 15 * x * f; b = 10 + 15 * y * f

// Macro to perform matrix multiplication on (x, y, z) with the transformation matrix m
#define P(i, j) (m[i][0] * x + m[i][1] * y + m[i][2] * z)

// Macro to set up a rotation matrix for angle a around the axis (b, c, d)
#define R(a, b, c, d) float c = cos(a), d = sin(a); m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[1][0] = 0; m[1][1] = c; m[1][2] = -d; m[2][0] = 0; m[2][1] = d; m[2][2] = c

int main() {
    float m[3][3], t = 0; // Rotation matrix and time variable
    int x, y, z, i, j, k; // Loop counters and temporary variables
    char c[W * H]; // Screen buffer
    float vertices[8][3], transformed[8][2]; // Vertex arrays for 3D and 2D points
    int faces[6][4] = {
        {0, 1, 3, 2},
        {4, 5, 7, 6},
        {0, 1, 5, 4},
        {2, 3, 7, 6},
        {0, 2, 6, 4},
        {1, 3, 7, 5}
    }; // Face definitions of the cube
    char shades[] = " .:-=+*#%@"; // Shading characters

    memset(c, ' ', sizeof(c)); // Initialize screen buffer with spaces

    for (;;) {
        t += 0.05; // Increment time
        R(t, 1, c1, s1); // Set up rotation matrix

        // Calculate transformed 3D vertices
        for (i = 0; i < 8; i++) {
            // Calculate the 3D coordinates of the cube's vertices
            A((i & 1) * 2 - 1, ((i >> 1) & 1) * 2 - 1, ((i >> 2) & 1) * 2 - 1, x, y, z);
            // Apply the rotation matrix
            float px = P(0, 1), py = P(1, 1), pz = P(2, 1);
            vertices[i][0] = px;
            vertices[i][1] = py;
            vertices[i][2] = pz;
            // Project the 3D point onto the 2D screen
            float a, b;
            M(a, b, px, py, pz);
            transformed[i][0] = a;
            transformed[i][1] = b;
        }

        // Draw each face of the cube
        for (i = 0; i < 6; i++) {
            float normal_x = 0, normal_y = 0, normal_z = 0;
            // Calculate the normal vector of the face
            for (j = 0; j < 4; j++) {
                int next = (j + 1) % 4;
                normal_x += (vertices[faces[i][j]][1] - vertices[faces[i][next]][1]) * (vertices[faces[i][j]][2] + vertices[faces[i][next]][2]);
                normal_y += (vertices[faces[i][j]][2] - vertices[faces[i][next]][2]) * (vertices[faces[i][j]][0] + vertices[faces[i][next]][0]);
                normal_z += (vertices[faces[i][j]][0] - vertices[faces[i][next]][0]) * (vertices[faces[i][j]][1] + vertices[faces[i][next]][1]);
            }
            // Calculate the shading based on the normal vector
            float shade = normal_z / sqrt(normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);
            char shade_char = shades[(int)((shade + 1) * 4.5)];

            // Draw the edges of the face
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

        // Print the screen buffer
        for (i = 0; i < H; i++) {
            for (j = 0; j < W; j++) putchar(c[i * W + j]);
            putchar('\n');
        }

        usleep(100000); // Wait for 100 milliseconds
        printf("\x1b[%dA", H); // Move the cursor back to the top of the screen
        memset(c, ' ', sizeof(c)); // Clear the screen buffer
    }
}
