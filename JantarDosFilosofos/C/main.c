#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
  
#define Filosofos 5 
#define Pensando 2 
#define Fome 1 
#define Comendo 0 
#define Esquerda (numfilosofo + 4) % Filosofos 
#define Direita (numfilosofo + 1) % Filosofos 


pthread_cond_t condicao[Filosofos];

int Estado[Filosofos]; 
int Filosofo[Filosofos]; 
  
sem_t mutex; 
sem_t S[Filosofos]; 

void *threadFilosofo(void *arg);
void testar(int);
void pegarGarfo(int);  
void devolverGarfo(int);  
  
int main() 
{ 
  
    int i; 
    pthread_t ph_thread[Filosofos]; 
  
    // initialize the semaphores 
    sem_init(&mutex, 0, 1); 
  
    for (i = 0; i < Filosofos; i++)
        sem_init(&S[i], 0, 0); 
        
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
        sleep(1); 
        pegarGarfo(*filosofo); 
        sleep(1); 
        devolverGarfo(*filosofo); 
    } 
} 

void testar(int numfilosofo) 
{ 
    if (Estado[numfilosofo] == Fome 
        && Estado[Esquerda] != Comendo 
        && Estado[Direita] != Comendo)
		{ 
	        Estado[numfilosofo] = Comendo; 
	  
	        sleep(2); 
	  
	        printf("Filosofo #%d pega o Garfo #%d e #%d.\n", 
	                      numfilosofo + 1, Esquerda + 1, numfilosofo + 1); 
	  
	        printf("Filosofo #%d esta Comendo.\n", numfilosofo + 1); 
	  
	        sem_post(&S[numfilosofo]); 
    	} 
} 

void pegarGarfo(int numfilosofo) 
{ 
  
    sem_wait(&mutex); 
    Estado[numfilosofo] = Fome; 
  
    printf("Filosofo #%d esta com Fome\n", numfilosofo + 1); 
  
    // Comer se os proximos nao estao comendo
    testar(numfilosofo); 
  
    sem_post(&mutex); 
  
    // Se nao puder comer esperar a sua vez
    sem_wait(&S[numfilosofo]); 
  
    sleep(1); 
} 


void devolverGarfo(int numfilosofo) 
{ 
  
    sem_wait(&mutex); 
   
    Estado[numfilosofo] = Pensando; 
  
    printf("Filosofo #%d devolveu o garfo #%d e #%d.\n", 
           numfilosofo + 1, Esquerda + 1, numfilosofo + 1); 
    printf("Filosofo #%d esta pensando\n", numfilosofo + 1); 
  
    testar(Esquerda); 
    testar(Direita); 
  
    sem_post(&mutex); 
} 
