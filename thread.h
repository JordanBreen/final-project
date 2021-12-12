#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include "bit_def.h"
typedef struct thread thread;
typedef byte thread_id;
typedef pthread_t thread_handle;
extern void init_resources(byte);
extern void free_resources(byte);
#endif
