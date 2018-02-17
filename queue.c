//
// Created by Hang Gong on 2/17/18.
//

#include "csapp.h"
#include "queue.h"

#define SIZE 50

static void **buffer;
static int inbuf;
static int outbuf;
static sem_t *empty;
static sem_t *full;
static pthread_mutex_t mutex;

void buffer_init() {
    buffer = Malloc(SIZE * (sizeof(void *)));

    inbuf = 0;
    outbuf = 0;

    empty = malloc(sizeof(sem_t));
    Sem_init(empty, 0, 0);

    full = malloc(sizeof(sem_t));
    Sem_init(full, 0, SIZE);

    pthread_mutex_init(&mutex, NULL);
}

void queue_put(void *item) {
    sem_wait(full);
    pthread_mutex_lock(&mutex);
    buffer[inbuf] = item;
    inbuf = (inbuf + 1) % SIZE;
    pthread_mutex_unlock(&mutex);
    sem_post(empty);

}

void *queue_get() {
    void *item = NULL;
    sem_wait(empty);
    pthread_mutex_lock(&mutex);
    item = buffer[outbuf];
    outbuf = (outbuf + 1) % SIZE;
    pthread_mutex_unlock(&mutex);
    sem_post(full);
    return item;
}

