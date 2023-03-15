#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "spin.h"
#include "lockbench.h"

/* Shared variables */
pthread_mutex_t mutex[MAX_TEST];
pthread_spinlock_t spinlock[MAX_TEST];
pthread_barrier_t barrier[MAX_TEST]; 

int var = 0;

static void *writer_func_mutex(void *data)
{
  int idx = *((int *) data);
  free(data);

  pthread_barrier_wait(&barrier[idx]);

  for (int i = 0; i < ITER; i++) {
    pthread_mutex_lock(&mutex[idx]);
    var++;
#ifdef SPIN_CRITICAL_SECTION
    for (int j = 0; j < ITER_SPIN; j++) { ; }
#endif
#ifdef DELAY_CRITICAL_SECTION
    spin(DURATION);
#endif
    pthread_mutex_unlock(&mutex[idx]);
  }

  return 0;
}
static void *writer_func_spin(void *data)
{
  int idx = *((int *) data);
  free(data);

  pthread_barrier_wait(&barrier[idx]);

  for (int i = 0; i < ITER; i++) {
    pthread_spin_lock(&spinlock[idx]);
    var++;
#ifdef SPIN_CRITICAL_SECTION
    for (int j = 0; j < ITER_SPIN; j++) { ; }
#endif
#ifdef DELAY_CRITICAL_SECTION
    spin(DURATION);
#endif
    pthread_spin_unlock(&spinlock[idx]);
  }

  return 0;
}

char *name_list[] = {
  "mutex",
  "spinlock"
};
void *(*func_list[]) (void *) = {
  writer_func_mutex,
  writer_func_spin,
};

struct timeval bench(LockType_t locktype, int threads, int verbose, int idx)
{
  pthread_t tid[MAX_THREAD];
  struct timeval start, end, elapsed;
  int ret, i;
  int *arg;
  void *(*func) (void *);

  func = func_list[locktype];

  pthread_mutex_init(&mutex[idx], NULL);
  pthread_spin_init(&spinlock[idx], PTHREAD_PROCESS_SHARED);
  pthread_barrier_init(&barrier[idx], NULL, threads + 1);

  for (i = 0; i < threads; i++) {
    arg = (int *) malloc(sizeof(int));
    *arg = idx;
    ret = pthread_create(&tid[i], NULL, func, arg);
    if (ret < 0) {
      perror("pthread create error");
      exit(EXIT_FAILURE);    
    }
  }

  gettimeofday(&start, NULL);
  pthread_barrier_wait(&barrier[idx]);

  for (i = 0; i < threads; i++) {
    pthread_join(tid[i], NULL);
  }

  gettimeofday(&end, NULL);
  timersub(&end, &start, &elapsed);

  if (var != threads * ITER)
    perror("synchronization failed\n");

  return elapsed;
}

void bench_multiple(LockType_t locktype, int threads, int tests, int verbose)
{
  int i;
  struct timeval total, cur, pre;

  total.tv_sec = 0;
  total.tv_usec = 0;
  for (i = 0; i < tests; i++) {
    var = 0;
    pre = total;
    cur = bench(locktype, threads, verbose, i);
    timeradd(&pre, &cur, &total);
  }
  printf("%-8s\t%-7d\t%-5d\t%ld.%06ld\n", name_list[locktype], threads, tests, ((total.tv_sec*1000000)/tests + total.tv_usec/tests)/1000000, ((total.tv_sec*1000000)/tests + total.tv_usec/tests)%1000000);
/*
  for (i = 0; i < tests; i++) {
    arg = (int *)malloc(sizeof(int));
    *arg = i;
    ret = pthread_create(&tid[i], NULL, bench, arg);
    if (ret < 0) {
      perror("pthread create error");
      exit(EXIT_FAILURE);    
    }
  }

  for (i = 0; i < tests; i++) {
    pthread_join(tid[i], NULL);
  }
*/
}