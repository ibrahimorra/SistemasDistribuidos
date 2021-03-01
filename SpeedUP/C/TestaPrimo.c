#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//
//  TestaPrimo.c
//  TestaPrimo
//
//  Created by Ricardo de Carvalho Destro on 12/08/20.
//  Copyright © 2020 Ricardo de Carvalho Destro. All rights reserved.
//

#include "TestaPrimo.h"

/* Convencao: EhPrimo = 1 se o numero dado 'e primo */
/*  EhPrimo = 0 se o numero dado nao 'e primo       */



int TestaPrimo(int n) {
  
    int EhPrimo = 1, d=2;
    if (n <= 1)
    EhPrimo = 0;

    while (EhPrimo == 1 && d <= n /2) {
    if (n % d  == 0)
        EhPrimo = 0;
    d = d + 1;
    }

    return EhPrimo;
}

int main(void) {
	int valor = 2147483647; // valor para teste
	
	float media = 0; // para calcular a media de tempo rodado em ms
	
	float medias[30]; // medias de tempo salvas num vetor para calculo do desvio padrao
	float soma = 0; // soma para calcular desvio padrao
	float dp = 0; // desvio padrao
	
	int i = 0;
	
	clock_t start, end;
	double cpu_time_used;
	
	for (i = 0; i < 30; i++){
		start = clock();
		int teste = TestaPrimo(valor);
		
		if (teste == 1){
		  printf("Número Primo\n");
		}else if(teste == 0){
		  printf("Número não é primo\n");
		}
	
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		
		printf("primeira: %f\n",cpu_time_used);
		
		media = media + cpu_time_used*1000;
		
		medias[i] = cpu_time_used*1000;
		
		printf("segunda: %f\n",medias[i]);
		
	}
	
	media = media/30;
	
	for (i = 0; i < 30; i++){
		//printf("calculando agora: %f - ", medias[i]);
		soma += pow(medias[i] - media,2);
	}
	
	dp = sqrt(soma/30);
	
	
	printf("Desvio Padrão = %f\n", dp);
	
	printf("Média -> %f ms", media);
}
