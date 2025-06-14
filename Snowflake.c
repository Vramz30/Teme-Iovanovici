#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define MAX_DEPTH 4

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double x, y;
} Point;

void svg_line(FILE *f, Point a, Point b) {
    fprintf(f, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"1\" />\n", a.x, a.y, b.x, b.y);
}

void koch(FILE *f, Point a, Point b, int depth) {
    if (depth == 0) {
        svg_line(f, a, b);
        return;
    }

    Point ab = { (2.0 * a.x + b.x) / 3.0, (2.0 * a.y + b.y) / 3.0 };
    Point ba = { (a.x + 2.0 * b.x) / 3.0, (a.y + 2.0 * b.y) / 3.0 };

    double angle = M_PI / 3.0;
    double dx = ba.x - ab.x;
    double dy = ba.y - ab.y;

    Point peak = {
        ab.x + dx * cos(angle) - dy * sin(angle),
        ab.y + dx * sin(angle) + dy * cos(angle)
    };

    koch(f, a, ab, depth - 1);
    koch(f, ab, peak, depth - 1);
    koch(f, peak, ba, depth - 1);
    koch(f, ba, b, depth - 1);
}

int main() {
    FILE *f = fopen("koch.svg", "w");
    if (!f) {
        perror("Nu pot deschide fișierul SVG");
        return 1;
    }

    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%d\" height=\"%d\">\n", WIDTH, HEIGHT);

    Point a = {200, 600};
    Point b = {600, 600};
    Point c;

    c.x = (a.x + b.x) / 2.0 - sqrt(3.0) / 2.0 * (b.y - a.y);
    c.y = (a.y + b.y) / 2.0 - sqrt(3.0) / 2.0 * (b.x - a.x);

    koch(f, a, b, MAX_DEPTH);
    koch(f, b, c, MAX_DEPTH);
    koch(f, c, a, MAX_DEPTH);

    fprintf(f, "</svg>\n");
    fclose(f);

    printf("Fractalul a fost salvat în koch.svg\n");
    return 0;
}
