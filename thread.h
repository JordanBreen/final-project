#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include "bit_def.h"
#include "spell.h"
typedef struct thread thread;
typedef byte thread_id;
typedef pthread_t thread_handle;
extern void init_resources(byte);
//extern void load_spells(spell *, spell_id*, size_t);
extern void free_resources(byte);
#endif
