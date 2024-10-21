#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "my_function.h" 

#define TEST_SIZE 5
static RingBuffer_t r; 

static void test_ringbuffer_init(void **state) {
    (void) state; 
    ringbuffer_init(&r, TEST_SIZE); 
    assert_int_equal(ringbuffer_size(&r), 0);
    assert_int_equal(r.max_size, TEST_SIZE);
    assert_int_equal(r.head, 0);
    assert_int_equal(r.tail, 0);
}

static void test_ringbuffer_add(void **state) {
    (void) state;
    ringbuffer_init(&r, TEST_SIZE);

    for (int i = 0; i < TEST_SIZE; i++) {
        assert_int_equal(ringbuffer_add(&r, i), 0);
    }
    assert_int_equal(ringbuffer_add(&r, 10), -1);
}


static void test_ringbuffer_remove(void **state) {
    (void) state;
    int value;

    ringbuffer_init(&r, TEST_SIZE);
    
    assert_int_equal(ringbuffer_remove(&r, &value), -1);
    
    ringbuffer_add(&r, 1);
    ringbuffer_add(&r, 2);
 
    assert_int_equal(ringbuffer_remove(&r, &value), 0);
    assert_int_equal(value, 1);
    
    assert_int_equal(ringbuffer_remove(&r, &value), 0);
    assert_int_equal(value, 2);
    
    assert_int_equal(ringbuffer_remove(&r, &value), -1);
}


static void test_ringbuffer_is_full(void **state) {
    (void) state;
    ringbuffer_init(&r, TEST_SIZE);
    assert_false(ringbuffer_is_full(&r));

    for (int i = 0; i < TEST_SIZE; i++) {
        ringbuffer_add(&r, i);
    }
    assert_true(ringbuffer_is_full(&r));
}


static void test_ringbuffer_is_empty(void **state) {
    (void) state;
    ringbuffer_init(&r, TEST_SIZE);
    
    assert_true(ringbuffer_is_empty(&r));
    
    ringbuffer_add(&r, 1);
    assert_false(ringbuffer_is_empty(&r));
    
    int value;
    ringbuffer_remove(&r, &value);
    assert_true(ringbuffer_is_empty(&r));
}


static void test_ringbuffer_size(void **state) {
    (void) state;
    ringbuffer_init(&r, TEST_SIZE);
    
    ringbuffer_add(&r, 1);
    ringbuffer_add(&r, 2);
    ringbuffer_add(&r, 3);
    
    assert_int_equal(ringbuffer_size(&r), 3);
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ringbuffer_init),
        cmocka_unit_test(test_ringbuffer_add),
        cmocka_unit_test(test_ringbuffer_remove),
        cmocka_unit_test(test_ringbuffer_is_full),
        cmocka_unit_test(test_ringbuffer_is_empty),
        cmocka_unit_test(test_ringbuffer_size),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}
