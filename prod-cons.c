#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

#define  FALSE 0
#define  TRUE  1

sem_t mutex; 
sem_t filled;
sem_t empty;

int posWrite = 0;
int posRead = 0;
int buffer[10];
int cheio, vazio;

void produtor(int id) {
    int item;
    while(TRUE) {
        sem_getvalue(&filled, &cheio);
        if (cheio == 10) {
            printf("-----BUFFER CHEIO-----\n");
        }
        sem_wait(&empty);
        sem_wait(&mutex);
        
        item = rand() % 20;
        buffer[posWrite%10] = item;
        posWrite = (posWrite+1) % 10;
        printf("Produtor %d adicionou %d ao buffer\n", id, item);

        sem_post(&mutex);
        sem_post(&filled);  
        sleep(id*(rand() % 3));
    }  
}

void consumidor(int id) {
    int item;
    while(TRUE) {
        sem_getvalue(&empty, &vazio);
        if (vazio == 10) {
            printf("-----BUFFER VAZIO-----\n");
        }
        sem_wait(&filled);
        sem_wait(&mutex);

        item = buffer[posRead%10];
        posRead = (posRead+1) % 10;

        sem_post(&mutex);
        sem_post(&empty);

        printf("Consumidor %d retirou %d do buffer\n", id, item);
        sleep(id*(rand() % 3));
    }
}

int main() {
    printf("Iniciando programa...\n");

    sem_init(&mutex, 0, 1);
    sem_init(&filled, 0, 0);
    sem_init(&empty, 0, 10); 
    printf("Semáforos criados\n\n");

	pthread_t prod1, prod2, prod3, prod4, cons1, cons2, cons3, cons4;

	pthread_create(&prod1, NULL, produtor, 1);
	pthread_create(&prod2, NULL, produtor, 2);
	pthread_create(&prod3, NULL, produtor, 3);
    pthread_create(&prod4, NULL, produtor, 4);

	pthread_create(&cons1, NULL, consumidor, 1);
	pthread_create(&cons2, NULL, consumidor, 2);
    pthread_create(&cons3, NULL, consumidor, 3);
	pthread_create(&cons4, NULL, consumidor, 4);

	pthread_join(prod1, NULL);
	pthread_join(prod2, NULL);
	pthread_join(prod3, NULL);
    pthread_join(prod4, NULL);
	pthread_join(cons1, NULL);
	pthread_join(cons2, NULL);
    pthread_join(cons3, NULL);
	pthread_join(cons4, NULL);

    sem_destroy(&mutex);
    sem_destroy(&filled);
    sem_destroy(&empty);
    printf("Semáforos destruídos\n");

    printf("Programa finalizado\n");
    return 0;
}