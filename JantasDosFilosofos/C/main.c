#include <pthread.h> 
#include <stdio.h> 
#include <stdbool.h>
  
#define Filosofos 5 
#define Pensando 2 
#define Fome 1 
#define Comendo 0 
#define Esquerda (numfilosofo + 4) % Filosofos
#define Direita (numfilosofo + 1) % Filosofos

pthread_cond_t condicao[Filosofos];

bool forks[Filosofos];

int Estado[Filosofos]; 
int Filosofo[Filosofos]; 

struct element {
    bool left;
    bool right;
    bool put_left;
    bool put_right;
};

struct element philo[Filosofos];

void *threadFilosofo(void *arg);
void pegarGarfoEsquerda(int);  
void pegarGarfoDireita(int);  
void devolverGarfoEsquerda(int);
void devolverGarfoDireita(int);  
void tentarComer(int);
void pensar(int);

int main() 
{ 
  
    int i; 
    pthread_t ph_thread[Filosofos]; 
    
    for (i = 0; i < Filosofos; i++){
    	philo[i].left = false;
    	philo[i].right = false;
	}
	
  	for (i = 0; i < Filosofos; i++)
  		forks[i] = false;
  	
        
	for (i = 0; i < Filosofos; i++) {
		pthread_cond_init(&condicao[i], NULL);
		Filosofo[i] = i;
	}
  
    for (i = 0; i < Filosofos; i++) { 
    	printf("Filosofo #%d sentou na mesa.\n", i + 1);
        pthread_create(&ph_thread[i], NULL, threadFilosofo, &Filosofo[i]);
        sleep(0);
    } 
  
    for (i = 0; i < Filosofos; i++) 
        pthread_join(ph_thread[i], NULL); 
        
	/* Cleanup */
	
	for (i = 0; i < Filosofos; i++)
		pthread_cond_destroy(&condicao[i]);
		
	
	return(0);
} 

void *threadFilosofo(void *arg)
{ 
  int *filosofo = arg;
    while (1) {   
		//tempo pensando (sleep)
		sleep(1);
		//Tenta pegar garfo Esquerda
		pegarGarfoEsquerda(*filosofo);
		//Tenta pegar garfo Direita
		pegarGarfoDireita(*filosofo); 
		//Devolve garfo Esquerda
		devolverGarfoEsquerda(*filosofo);
		//Devolve garfo Direita
		devolverGarfoDireita(*filosofo);
			
	    //DeadLock Test
	    if (
			Estado[0] == Fome
		&&	Estado[1] == Fome
		&&	Estado[2] == Fome
		&& 	Estado[3] == Fome
		&&	Estado[4] == Fome
		&&	(philo[0].left == true || philo[0].right == true)
		&&	(philo[1].left == true || philo[1].right == true)
		&&	(philo[2].left == true || philo[2].right == true)
		&&	(philo[3].left == true || philo[3].right == true)
		&&	(philo[4].left == true || philo[4].right == true)
		){
			printf("|>->-> Deadlock <-<-<|\n");
			return(0);
		}
	    } 
} 

void tentarComer(int numfilosofo){
	if (
		philo[numfilosofo].left == true
		&&philo[numfilosofo].right == true
	){
		printf("Filosofo #%d esta comendo.\n", numfilosofo+1);
		sleep(1);
		Estado [numfilosofo] = Comendo;
	}else{
		//printf("Filosofo #%d Left Fork -> %s \n", numfilosofo+1, philo[numfilosofo].left ? "true" : "false");
		//printf("Filosofo #%d Right Fork -> %s \n", numfilosofo+1, philo[numfilosofo].right ? "true" : "false");
	}
}

void pensar(int numfilosofo){
	if (
		philo[numfilosofo].put_left == true
		&&philo[numfilosofo].put_right == true
	){
		printf("Filosofo #%d esta pensando.\n", numfilosofo+1);
		sleep(1);
		Estado [numfilosofo] = Pensando;
		philo[numfilosofo].put_left = false;
		philo[numfilosofo].put_right = false;
	}else{
		//printf("Filosofo #%d Left Put -> %s \n", numfilosofo+1, philo[numfilosofo].put_left ? "true" : "false");
		//printf("Filosofo #%d Right Put -> %s \n", numfilosofo+1, philo[numfilosofo].put_right ? "true" : "false");
	}
}


void pegarGarfoEsquerda(int numfilosofo) 
{ 
    Estado[numfilosofo] = Fome; 
    printf("Filosofo #%d esta com Fome\n", numfilosofo+1);
    if (Estado[numfilosofo] == Fome 
        && Estado[Esquerda-1] != Comendo
		&& philo[Esquerda-1].right == false )
		{ 
	        forks[Esquerda] = true;
	        philo[numfilosofo].left = true;
	        printf("Filosofo #%d pega o Garfo #%d.\n",numfilosofo+1, Esquerda+1 );
	        tentarComer(numfilosofo);
    	} 
} 

void pegarGarfoDireita(int numfilosofo) 
{ 
    Estado[numfilosofo] = Fome; 
    printf("Filosofo #%d esta com Fome\n", numfilosofo+1); 
    if (Estado[numfilosofo] == Fome 
        && Estado[Direita+1] != Comendo
		&& philo[Direita+1].left == false)
	{
			        
        forks[Direita] = true;
        philo[numfilosofo].right = true;
        printf("Filosofo #%d pega o Garfo #%d.\n",numfilosofo+1, Direita+1); 
        tentarComer(numfilosofo);
	} 
} 



void devolverGarfoEsquerda(int numfilosofo) 
{ 
	if (Estado[numfilosofo] == Comendo) {
		printf("Filosofo #%d devolveu o garfo #%d.\n", numfilosofo+1, Esquerda+1); 
		forks[Esquerda] = false;
		philo[numfilosofo].left = false;
		philo[numfilosofo].put_left = true;
		pensar(numfilosofo); 
	}  
} 

void devolverGarfoDireita(int numfilosofo) 
{ 
  	if (Estado[numfilosofo] == Comendo) {
	    Estado[numfilosofo] = Pensando; 
	    printf("Filosofo #%d devolveu o garfo #%d.\n", numfilosofo+1, Direita+1); 
	    forks[Direita] = false;
	    philo[numfilosofo].right = false;
	  	philo[numfilosofo].put_right = true;
		  pensar(numfilosofo);
	}
} 
