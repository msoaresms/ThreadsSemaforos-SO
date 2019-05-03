#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

#define  TRUE  1

sem_t mutex, escritex;

int readerCount = 0;
int item;

void leitor(int id) {
    while(TRUE) {
        sem_wait(&mutex);
        ++readerCount;

        if (readerCount == 1) {
            sem_wait(&escritex);
        }

        sem_post(&mutex);
        printf("Leitor %d leu o valor: %d\n", id, item);
        sem_wait(&mutex);
        --readerCount;

        if (readerCount == 0) {
            sem_post(&escritex);
        }

        sem_post(&mutex);
        sleep(id*(rand() % 3));
    }  
}

void escritor(int id) {
    while(TRUE) {
        sem_wait(&escritex);
        item = (rand() % 100);
        printf("Escritor %d escreveu o valor %d\n", id, item);
        sem_post(&escritex);
        sleep(id*(rand() % 3));
    }
}

int main() {
    printf("Iniciando programa...\n");

    sem_init(&mutex, 0, 1);
    sem_init(&escritex, 0, 1);
    printf("Semáforos criados\n\n");

	pthread_t esc1, esc2, lei1, lei2, lei3, lei4;

	pthread_create(&esc1, NULL, escritor, 1);
	pthread_create(&esc2, NULL, escritor, 2);

	pthread_create(&lei1, NULL, leitor, 1);
	pthread_create(&lei2, NULL, leitor, 2);
	pthread_create(&lei3, NULL, leitor, 3);

	pthread_join(esc1, NULL);
	pthread_join(esc2, NULL);
	pthread_join(lei1, NULL);
    pthread_join(lei2, NULL);
	pthread_join(lei3, NULL);

    sem_destroy(&mutex);
    sem_destroy(&escritex);
    printf("Semáforos destruídos\n");

    printf("Programa finalizado\n");
    return 0;
}