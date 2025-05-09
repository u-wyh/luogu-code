#include <stdio.h>
#include <math.h>

int a, n;
int b[1002010] = {0};
int la = 1002001;

int main() {
    scanf("%d%d", &a, &n);
    for (int i = (int)ceil(sqrt(a * 1.0)); i * i <= 1002001; i++) {
        for (int j = 1; j * i * i <= 1002001; j++) {
            b[j * i * i] = j * i * i;
        }
    }
    for (int i = 1002000; i >= 1; i--) {
        if (b[i] == i) {
            la = i;
        } else {
            b[i] = la;
        }
    }
    while (n--) {
        int x;
        scanf("%d", &x);
        if (b[x] == x) {
            puts("lucky");
        } else {
            printf("%d\n", b[x]);
        }
    }
    return 0;
}
