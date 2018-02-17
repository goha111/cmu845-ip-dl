#define CACHE_CAP 1

typedef struct block {
    struct block *prev;
    struct block *next;
    char *name;
    void *handle;
    void *func;
} block_t;


static size_t cache_size;
static pthread_rwlock_t mutex = PTHREAD_MUTEX_INITIALIZER;
static block_t *head;
static block_t *tail;

void cache_init();
void *put(char *name, void *handle);
void *get(char *name);
void block_destroy(block_t *block);

block_t *block_init(char *name, void *handle);
block_t *block_remove(block_t *block);
void block_add(block_t *block);
block_t *block_visit(block_t *block);