#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double valoare, greutate;
} Obiect;

int cmp(const void *a, const void *b) {
    Obiect *x = (Obiect *)a;
    Obiect *y = (Obiect *)b;
    double r1 = x->valoare / x->greutate;
    double r2 = y->valoare / y->greutate;
    return (r2 > r1) - (r2 < r1);  // Descrescător
}

double knapsackContinuu(Obiect obiecte[], int n, double capacitate) {
    qsort(obiecte, n, sizeof(Obiect), cmp);

    double total = 0.0;
    for (int i = 0; i < n && capacitate > 0; i++) {
        if (obiecte[i].greutate <= capacitate) {
            total += obiecte[i].valoare;
            capacitate -= obiecte[i].greutate;
        } else {
            total += obiecte[i].valoare * (capacitate / obiecte[i].greutate);
            break;
        }
    }
    return total;
}

int main() {
    int n;
    double W;
    scanf("%d %lf", &n, &W);

    Obiect obiecte[1000];
    for (int i = 0; i < n; i++)
        scanf("%lf %lf", &obiecte[i].valoare, &obiecte[i].greutate);

    double maxVal = knapsackContinuu(obiecte, n, W);
    printf("%.6lf\n", maxVal);

    return 0;
}
