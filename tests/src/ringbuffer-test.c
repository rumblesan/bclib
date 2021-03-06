#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#include "minunit.h"
#include "ringbuffer.h"

char *test_ringbuffer_create() {
  int size = 10;
  RingBuffer *rb = rb_create(size);
  mu_assert(rb != NULL, "Could not create ring buffer");
  mu_assert(rb->size == size, "Size incorrect");
  mu_assert(rb->head == 0, "Head should be at 0");
  mu_assert(rb->tail == 0, "Tail should be at 0");
  rb_destroy(rb);
  return NULL;
}

char *test_ringbuffer_push_pop() {
  int size = 10;
  int *vin = malloc(sizeof(int));
  *vin = 1000;

  RingBuffer *rb = rb_create(size);
  int pos = rb_push(rb, vin);
  mu_assert(pos == 0, "Ring buffer should have pushed value to position 0");
  mu_assert(rb->tail == 1, "Ring buffer tail should have moved by 1");

  int *vout = rb_pop(rb);
  mu_assert(rb->head == 1, "Ring buffer head should have moved by 1");
  mu_assert(*vout == *vin, "input value should equal output value");

  rb_destroy(rb);
  free(vin);
  
  return NULL;
}

char *test_ringbuffer_full() {
  int size = 3;
  int *vin1 = malloc(sizeof(int));
  *vin1 = 1;
  int *vin2 = malloc(sizeof(int));
  *vin2 = 2;
  int *vin3 = malloc(sizeof(int));
  *vin3 = 3;
  int *vin4 = malloc(sizeof(int));
  *vin4 = 4;

  RingBuffer *rb = rb_create(size);
  mu_assert(rb_empty(rb) == true, "Buffer should be empty");
  mu_assert(rb_full(rb) == false, "Buffer should not be full");
  mu_assert(rb_size(rb) == 0, "Should have size of 0");
  int pos;
  pos = rb_push(rb, vin1);
  mu_assert(rb->tail == 1, "Tail should have moved to 1");
  mu_assert(pos == 0, "Should have pushed value to pos 0");

  pos = rb_push(rb, vin2);
  mu_assert(rb->tail == 2, "Tail should have moved to 2");
  mu_assert(pos == 1, "Should have pushed value to pos 1");
  mu_assert(rb_size(rb) == 2, "Should have size of 2");

  pos = rb_push(rb, vin3);
  mu_assert(rb->tail == 3, "Tail should have moved to 3");
  mu_assert(pos == 2, "Should have pushed value to pos 2");
  mu_assert(rb_size(rb) == 3, "Should have size of 3");

  pos = rb_push(rb, vin4);
  mu_assert(rb->tail == 3, "Tail should not have moved");
  mu_assert(pos == -1, "Should not have been able to push value");

  int *vout = rb_pop(rb);
  mu_assert(rb->head == 1, "Head should have moved to 1");
  mu_assert(*vout == *vin1, "Input value should equal output value");

  pos = rb_push(rb, vin4);
  mu_assert(rb->tail == 0, "Tail should have moved to 0");
  mu_assert(pos == 3, "Should have pushed value to pos 3");

  rb_pop(rb);
  mu_assert(rb->head == 2, "Head should have moved to 2");
  rb_pop(rb);
  mu_assert(rb->head == 3, "Head should have moved to 3");
  mu_assert(rb_size(rb) == 1, "Should have size of 1");
  rb_pop(rb);
  mu_assert(rb->head == 0, "Head should have moved to 0");

  mu_assert(rb_empty(rb) == 1, "Should be empty");
  mu_assert(rb_size(rb) == 0, "Should have size of 0");

  int *empty = rb_pop(rb);
  mu_assert(rb->head == 0, "Head should not have moved");
  mu_assert(empty == NULL, "Value is NULL");
  mu_assert(rb_size(rb) == 0, "Should have size of 0");
  pos = rb_push(rb, vin3);
  mu_assert(rb_size(rb) == 1, "Should have size of 1");
  rb_pop(rb);
  mu_assert(rb_size(rb) == 0, "Should have size of 0");

  rb_destroy(rb);
  free(vin1);
  free(vin2);
  free(vin3);
  free(vin4);
  
  return NULL;
}

void *relay_thread(void *_rbuffer) {

  RingBuffer *rbuffer = _rbuffer;
  int *vout = NULL;
  struct timespec tim, tim2;
  tim.tv_sec = 0;
  tim.tv_nsec = 1000000;
  while (1) {
    nanosleep(&tim, &tim2);

    vout = rb_pop(rbuffer);
    if (vout == NULL) continue;

    if (*vout == -2) {
      printf("Received kill signal\n");
      free(vout);
      break;
    } else {
      printf("Received %d\n", *vout);
      free(vout);
    }
  }

  pthread_exit(NULL);
}

char *test_ringbuffer_threads() {

  RingBuffer *rb  = rb_create(20);

  pthread_t thread1;
  printf("In main: creating relay thread\n");
  int rc1 = pthread_create(&thread1, NULL, &relay_thread, rb);
  if (rc1) {
    printf("ERROR; return code from pthread_create() is %d\n", rc1);
    exit(-1);
  }

  pthread_t thread2;
  printf("In main: creating relay thread\n");
  int rc2 = pthread_create(&thread2, NULL, &relay_thread, rb);
  if (rc2) {
    printf("ERROR; return code from pthread_create() is %d\n", rc2);
    exit(-1);
  }

  int msgs = 10;

  int *val1 = NULL;
  for (int m = 0; m < msgs; m++) {
    val1 = malloc(sizeof(int));
    *val1 = m;
    rb_push(rb, val1);
  }

  sleep(1);

  int *val2 = NULL;
  for (int m = 0; m < msgs; m++) {
    val2 = malloc(sizeof(int));
    *val2 = m;
    rb_push(rb, val2);
  }

  int *kill1 = malloc(sizeof(int));
  *kill1 = -2;
  rb_push(rb, kill1);

  int *kill2 = malloc(sizeof(int));
  *kill2 = -2;
  rb_push(rb, kill2);

  sleep(1);

  pthread_exit(NULL);

  rb_destroy(rb);
  return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_ringbuffer_create);
    mu_run_test(test_ringbuffer_push_pop);
    mu_run_test(test_ringbuffer_full);
    mu_run_test(test_ringbuffer_threads);

    return NULL;
}

RUN_TESTS(all_tests);
