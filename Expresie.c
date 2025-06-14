#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int paranteze(const char* expr, int start) {
    int count = 0;
    for (int i = start; expr[i]; i++) {
        if (expr[i] == '(') count++;
        else if (expr[i] == ')') count--;
        if (count == 0) return i;
    }
    return -1; 
}

int toInt(const char* str, int start, int end) {
    char num[20];
    strncpy(num, str + start, end - start + 1);
    num[end - start + 1] = '\0';
    return atoi(num);
}

int eval(const char* expr, int start, int end) {
 
    while (expr[start] == '(' && paranteze(expr, start) == end) {
        start++;
        end--;
    }

    int par = 0;
 
    for (int i = end; i >= start; i--) {
        if (expr[i] == ')') par++;
        else if (expr[i] == '(') par--;
        else if (par == 0 && (expr[i] == '+' || expr[i] == '-')) {
            int left = eval(expr, start, i - 1);
            int right = eval(expr, i + 1, end);
            if (expr[i] == '+') return left + right;
            else return left - right;
        }
    }

    // inmultire si impartire
    for (int i = end; i >= start; i--) {
        if (expr[i] == ')') par++;
        else if (expr[i] == '(') par--;
        else if (par == 0 && (expr[i] == '*' || expr[i] == '/')) {
            int left = eval(expr, start, i - 1);
            int right = eval(expr, i + 1, end);
            if (expr[i] == '*') return left * right;
            else return left / right;
        }
    }


    return toInt(expr, start, end);
}

int main() {
    char expr[200];
    printf("Introdu expresia complet parantezata: ");
    scanf("%s", expr);

    int result = eval(expr, 0, strlen(expr) - 1);
    printf("Rezultatul este: %d\n", result);

    return 0;
}
