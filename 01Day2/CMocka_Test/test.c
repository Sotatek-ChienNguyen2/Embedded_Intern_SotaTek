#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "my_function.h"

#define TEST_SIZE 5

extern RingBuffer_t r;


static void test_ringbuffer_init(void **state) {
    (void) state; // Không dùng state trong test này
    ringbuffer_init(TEST_SIZE);
    assert_int_equal(ringbuffer_size(), 0);
    assert_int_equal(r.max_size, TEST_SIZE);
    assert_int_equal(r.head, 0);
    assert_int_equal(r.tail, 0);
}

static void test_ringbuffer_add(void **state) {
    (void) state;
    ringbuffer_init(TEST_SIZE);
    // Thêm các phần tử vào ring buffer
    for (int i = 0; i < TEST_SIZE; i++) {
        assert_int_equal(ringbuffer_add(i), 0);
    }
    // Buffer đầy, thử thêm phần tử khác
    assert_int_equal(ringbuffer_add(10), -1);
}

static void test_ringbuffer_remove(void **state) {
    (void) state;
    int value;
    
    ringbuffer_init(TEST_SIZE);
    // Thử loại bỏ phần tử từ buffer trống
    assert_int_equal(ringbuffer_remove(&value), -1);
    // Thêm phần tử vào ring buffer
    ringbuffer_add(1);
    ringbuffer_add(2);
    // Xóa phần tử và kiểm tra giá trị
    assert_int_equal(ringbuffer_remove(&value), 0);
    assert_int_equal(value, 1);
    // Xóa phần tử còn lại
    assert_int_equal(ringbuffer_remove(&value), 0);
    assert_int_equal(value, 2);
    // Buffer trống, thử xóa phần tử nữa
    assert_int_equal(ringbuffer_remove(&value), -1);
}

static void test_ringbuffer_is_full(void **state) {
    (void) state;
    ringbuffer_init(TEST_SIZE);
    assert_false(ringbuffer_is_full());
    // Thêm đủ phần tử để đầy buffer
    for (int i = 0; i < TEST_SIZE; i++) {
        ringbuffer_add(i);
    }
    assert_true(ringbuffer_is_full());
}

static void test_ringbuffer_is_empty(void **state) {
    (void) state;
    ringbuffer_init(TEST_SIZE);
    assert_true(ringbuffer_is_empty());
    ringbuffer_add(1);
    assert_false(ringbuffer_is_empty());
    int value;
    ringbuffer_remove(&value);
    assert_true(ringbuffer_is_empty());
}

static void test_ringbuffer_size(void **state) {
    (void) state;
    ringbuffer_init(TEST_SIZE);
    ringbuffer_add(1);
    ringbuffer_add(2);
    ringbuffer_add(3);
    assert_int_equal(ringbuffer_size(), 3);




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