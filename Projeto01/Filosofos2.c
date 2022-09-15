#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


#define N 5
#define Pensando 2
#define com_Fome 1
#define Comendo 0
#define ESQUERDA (filosofos + 4) % N
#define DIREITA (filosofos + 1) % N

int garfo[N];
int vet[N] = { 0, 1, 2, 3, 4 };

// Aqui vamos utilizar dois semaf�ros com opera��es diferentes
// Um ser� para para pegar o garfo (sem_wait) outro para devolver garfo(sem_post)
sem_t mutex; //Declarando semaf�ro
sem_t S[N]; //Declarando semaf�ro

void mesa(int filosofos) {
	if (garfo[filosofos] == com_Fome && garfo[ESQUERDA] != Comendo && garfo[DIREITA] != Comendo) {
		
		garfo[filosofos] = Comendo;
		sleep(2);

		printf("Filosofos %d pega garfo %d e %d\n", filosofos + 1, ESQUERDA + 1, filosofos + 1);
		printf("\n");
		printf("*** Filosofos %d esta comendo ***\n", filosofos + 1);

		sem_post(&S[filosofos]);
	}
}

void pega_Garfo(int filosofos) {

	sem_wait(&mutex);
	garfo[filosofos] = com_Fome;
	printf("Filosofos %d esta com fome\n", filosofos + 1);
	mesa(filosofos);
	sem_post(&mutex);
	sem_wait(&S[filosofos]);
	sleep(1);
}

void devolve_Garfo(int filosofos) {

	sem_wait(&mutex);
	garfo[filosofos] = Pensando;

	printf("Filosofos %d devolve garfo %d e %d\n",filosofos + 1, ESQUERDA + 1, filosofos + 1);
	printf("\n");
	printf("Filosofos %d esta pensando\n", filosofos + 1);
	
	mesa(ESQUERDA);
	mesa(DIREITA);
	sem_post(&mutex);
}

void* Filosofos(void* num) {

	while (1) {
		int* i = num;
		sleep(1);
		pega_Garfo(*i);
		sleep(0);
		devolve_Garfo(*i);
	}
}

int main() {
	int i;
	pthread_t thread_id[N];

	sem_init(&mutex, 0, 1);
	for (i = 0; i < N; i++)
		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {
		pthread_create(&thread_id[i], NULL,Filosofos, &vet[i]);
		printf("Filosofos %d esta pensando\n", i + 1);
	}

	for (i = 0; i < N; i++) {
		pthread_join(thread_id[i], NULL);
	}
}
