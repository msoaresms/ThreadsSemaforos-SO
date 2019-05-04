#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

#define TRUE  1
#define NUMFIL 5
#define ESQUERDA (i+NUMFIL-1)%NUMFIL
#define DIREITA (i+1)%NUMFIL
#define PENSANDO 0
#define FAMINTO 1
#define COMENDO 2

sem_t mutex, s[NUMFIL];

int estado[NUMFIL];

void pensar(int i) {
    printf("Filósofo %d está pensando...\n", i);
    sleep(rand()%10);
}

void comer(int i) {
    printf("Filósofo %d está comendo...\n", i);
    sleep(rand()%5);
}

void tentar(int i) {
    if (estado[i] == FAMINTO && estado[ESQUERDA] != COMENDO && estado[DIREITA] != COMENDO) {
        estado[i] = COMENDO;
        sem_post(&s[i]);
    }
}

void pegarGarfos(int i) {
    sem_wait(&mutex);
    estado[i] = FAMINTO;
    tentar(i);
    sem_post(&mutex);
    sem_wait(&s[i]);
}

void liberarGarfos(int i) {
    sem_wait(&mutex);
    estado[i] = PENSANDO;
    tentar(ESQUERDA);
    tentar(DIREITA);
    sem_post(&mutex);
}

void filosofo(int i) {
    while(TRUE) {
        pensar(i);
        pegarGarfos(i);
        comer(i);
        liberarGarfos(i);
    }
}

int main() {
    printf("Iniciando programa...\n");

    sem_init(&mutex, 0, 1);
    sem_init(&s[0], 0, 1);
    sem_init(&s[1], 0, 1);
    sem_init(&s[2], 0, 1);
    sem_init(&s[3], 0, 1);
    sem_init(&s[4], 0, 1);
    printf("Semáforos criados\n\n");

	pthread_t fil1, fil2, fil3, fil4, fil5;

	pthread_create(&fil1, NULL, filosofo, 0);
	pthread_create(&fil2, NULL, filosofo, 1);
	pthread_create(&fil3, NULL, filosofo, 2);
	pthread_create(&fil4, NULL, filosofo, 3);
	pthread_create(&fil5, NULL, filosofo, 4);

	pthread_join(fil1, NULL);
	pthread_join(fil2, NULL);
	pthread_join(fil3, NULL);
    pthread_join(fil4, NULL);
	pthread_join(fil5, NULL);

    sem_destroy(&mutex);
    printf("Semáforos destruídos\n");

    printf("Programa finalizado\n");
    return 0;
}