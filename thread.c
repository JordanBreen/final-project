#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include "resource.h"

static thread *threads;
static byte num_threads;
static pthread_barrier_t barrier;
static pthread_mutex_t mutex;

const byte MASTER = 0;

struct thread {
  thread_id     _id;
  thread_handle _handle;
};

typedef struct bag_of_tasks {
  int cur_task;
  int num_task;
} bag_of_tasks;

bag_of_tasks bot;

// obscured functions
void* _init_resources(void *ext);
void* _free_resources(void *ext);

// bag of task functions //
int get_task() {
  int ret;
  pthread_mutex_lock(&mutex);
  ret = (bot.cur_task < bot.num_task) ? bot.cur_task++ : -1;
  pthread_mutex_unlock(&mutex);
  return ret;
}

void set_num_tasks(int arg) {
  bot.num_task = arg;
}

void reset_bag_of_tasks() {
  bot.cur_task = 0;
}

void init_threads(byte arg_num_threads) {
  num_threads = arg_num_threads;
  threads = (thread*) malloc(num_threads * sizeof(thread));
  pthread_barrier_init(&barrier, NULL, num_threads);
  pthread_mutex_init(&mutex, NULL);
}

void process_threads(void*(*task)(void *)) {
  int rc;
  reset_bag_of_tasks();
  for (int i = 0; i < num_threads; i++) {
    threads[i]._id = i;
    rc = pthread_create(&(threads[i]._handle), NULL, task, &(threads[i]));
    if(rc) {
      fprintf(stderr, "Could not create thread %d\n", i);
      exit(1);
    }
  }
}

void* _init_resources(void *ext) {
  task   * _tasks;
  size_t   _num_tasks;
  thread * _thread;
  int      _task_index;
  _num_tasks = get_initializer_tasks(&_tasks);
  _thread    = (thread *) ext;
  if(_thread->_id == MASTER)
    set_num_tasks(_num_tasks);
  pthread_barrier_wait(&barrier);
  while ((_task_index = get_task()) != -1)
    _tasks[_task_index]();
  return NULL;
}

void* _free_resources(void *ext) {
  task   * _tasks;
  size_t   _num_tasks;
  thread * _thread;
  int      _task_index;
  _num_tasks = get_destructor_tasks(&_tasks);
  _thread    = (thread *) ext;
  if(_thread->_id == MASTER)
    set_num_tasks(_num_tasks);
  pthread_barrier_wait(&barrier);
  while ((_task_index = get_task()) != -1)
    _tasks[_task_index]();
  return NULL;
}

void destroy_threads() {
  for (int i = 0; i < num_threads; i++)
    pthread_join(threads[i]._handle, NULL);
  pthread_barrier_destroy(&barrier);
  pthread_mutex_destroy(&mutex);
}

void init_resources(byte arg_num_threads) {
  init_threads(arg_num_threads);
  process_threads(_init_resources);
  destroy_threads();
}

void free_resources(byte arg_num_threads) {
  init_threads(arg_num_threads);
  process_threads(_free_resources);
  destroy_threads();
}
