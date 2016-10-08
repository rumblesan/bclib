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
  int pos;
  pos = rb_push(rb, vin1);
  mu_assert(rb->tail == 1, "Tail should have moved to 1");
  mu_assert(pos == 0, "Should have pushed value to pos 0");

  pos = rb_push(rb, vin2);
  mu_assert(rb->tail == 2, "Tail should have moved to 2");
  mu_assert(pos == 1, "Should have pushed value to pos 1");

  pos = rb_push(rb, vin3);
  log_info("tail is %d", rb->tail);
  mu_assert(rb->tail == 3, "Tail should have moved to 3");
  mu_assert(pos == 2, "Should have pushed value to pos 2");

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
  rb_pop(rb);
  mu_assert(rb->head == 0, "Head should have moved to 0");

  mu_assert(rb_empty(rb) == 1, "Should be empty");

  int *empty = rb_pop(rb);
  mu_assert(rb->head == 0, "Head should not have moved");
  mu_assert(empty == NULL, "Value is NULL");

  rb_destroy(rb);
  free(vin1);
  free(vin2);
  free(vin3);
  free(vin4);
  
  return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_ringbuffer_create);
    mu_run_test(test_ringbuffer_push_pop);
    mu_run_test(test_ringbuffer_full);

    return NULL;
}

RUN_TESTS(all_tests);
