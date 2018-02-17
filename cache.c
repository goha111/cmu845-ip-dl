//
// Created by Hang Gong on 2/17/18.
//

#include "csapp.h"
#include "dlfcn.h"

#define CACHE_CAP 30

typedef struct block {
    struct block *prev;
    struct block *next;
    char *name;
    void *func;
} block_t;


static size_t cache_size;
static pthread_rwlock_t mutex = PTHREAD_MUTEX_INITIALIZER;
static block_t *head;
static block_t *tail;


void put(char *name, void *handle);
block_t *block_remove(block_t *block);
void block_add(block_t *block);
block_t *block_visit(block_t *block);


void init() {
    cache_size = 0;
    head = Malloc(sizeof(block_t));
    tail = Malloc(sizeof(block_t));
    head->next = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;
}


block_t *block_init(char *name, void *handle) {
    block_t *node = Malloc(sizeof(block_t));

    node->prev = NULL;
    node->next = NULL;

    node->name = Malloc((strlen(name) + 1) * sizeof(char));
    strncpy(node->name, name, strlen(name));

    node->func = dlsym(handle, name);
    return node;
}

void block_destroy(block_t *block) {
    free(block->name);
    free(block->func);
    free(block);
}

block_t *get(char *name) {
    pthread_rwlock_rdlock(&mutex);
    block_t *node = head->next;
    while (node != tail) {
        if (strcmp(name, node->name) == 0) {
            break;
        } else {
            node = node->next;
        }
    }
    pthread_rwlock_unlock(&mutex);
    if (node != tail) {
        return block_visit(node);
    } else {
        return NULL;
    }
}

void put(char *name, void *handle) {
    pthread_rwlock_wrlock(&mutex);
    if (get(name) == NULL) {
        if (cache_size == CACHE_CAP) {
            block_t *temp = block_remove(tail->prev);
            block_destroy(temp);
            cache_size -= 1;
        }
        block_t *node = block_init(name, handle);
        block_add(node);
        cache_size += 1;
    }
    pthread_rwlock_unlock(&mutex);
}


block_t *block_remove(block_t *block) {
    block->prev->next = block->next;
    block->next->prev = block->prev;
    return block;
}

void block_add(block_t *block) {
    block->next = head->next;
    block->next->prev = block;
    block->prev = head;
    head->next = block;
}

block_t *block_visit(block_t *block) {
    block_remove(block);
    block_add(block);
    return block;
}



