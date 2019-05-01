#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define  FALSE 0
#define  TRUE  1

sem_t mutex; 
sem_t filled;
sem_t empty;

int buffer;

void produtor(int id) {
    int item = id;
    while(TRUE) {

        sem_wait(&empty);
        sem_wait(&mutex);
        
        buffer = item;
        printf("%d adicionado ao buffer\n", item);

        sem_post(&mutex);
        sem_post(&filled);  
        sleep(id);
    }  
}

void consumidor(int id) {
    int item;
    while(TRUE) {

        sem_wait(&filled);
        sem_wait(&mutex);

        item = buffer;

        sem_post(&mutex);
        sem_post(&empty);

        printf("%d retirado do buffer\n", item);
        sleep(id);
    }
}

int main() {
    printf("Iniciando programa...\n");

    sem_init(&mutex, 0, 1);
    sem_init(&filled, 0, 0);
    sem_init(&empty, 0, 1); 
    printf("Semáforos criados\n");

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