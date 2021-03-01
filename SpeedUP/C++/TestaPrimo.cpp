#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

int TestaPrimo(int n) {

    int EhPrimo = 1, d = 2;
    if (n <= 1)
        EhPrimo = 0;

    while (EhPrimo == 1 && d <= n / 2) {
        if (n % d == 0)
            EhPrimo = 0;
        d = d + 1;
    }

    return EhPrimo;
}

int main()
{
    int valor = 2147483647; // Valor para ser testado
    float timer = 0; // Tempo de execução
    float media = 0; // Média do tempo de execução

    for (int i = 0; i < 30; i++) {
        clock_t tStart = clock();
        int teste = TestaPrimo(valor);

        if (teste == 1) {
            printf("Numero Primo\n");
        }
        else if (teste == 0) {
            printf("Numero nao e primo\n");
        }

        timer = (double)(clock() - tStart) / CLOCKS_PER_SEC;

        media += timer;

    }

    media = media / 30;

    printf("Media --> %.2f", media*1000);

}


