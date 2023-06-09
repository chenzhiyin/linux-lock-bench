#ifndef __LOCKBENCH_H__
#define __LOCKBENCH_H__

/* Configurations */
// #define MEASURE_WAITING_TIME

#define MAX_THREAD 16
#define MAX_TEST 16

// #define DELAY_CRITICAL_SECTION
#define SPIN_CRITICAL_SECTION

#define ITER 100000
#ifdef DELAY_CRITICAL_SECTION
#define DURATION 1 // us (todo: change to ns)
#endif // DELAY_CRITICAL_SECTION
#ifdef SPIN_CRITICAL_SECTION
#define ITER_SPIN 1000
#endif // SPIN_CRITICAL_SECTION


typedef enum {
  LOCKTYPE_MUTEX,
  LOCKTYPE_SPINLOCK,
  NONE
} LockType_t;

struct timeval bench(LockType_t locktype, int threads, int verbose, int idx);
void bench_multiple(LockType_t locktype, int threads, int tests, int verbose);

#endif