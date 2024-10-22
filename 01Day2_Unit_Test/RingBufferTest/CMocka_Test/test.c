#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "my_function.h" 

#define TEST_SIZE 5
static RingBuffer_t r; 

static void test_ringbuffer_init(void **state) {
    (void) state;  
    assert_int_equal(ringbuffer_init(&r, TEST_SIZE), 0);
    assert_int_equal(r.max_size, TEST_SIZE);
    assert_int_equal(r.head, 0);
    assert_int_equal(r.tail, 0);
}

/* Khởi tạo buffer với size < 2 hoặc size > MAX_SIZE */
static void test_ringbuffer_init_invalid_size(void **state) {
    (void) state;
    assert_int_equal(ringbuffer_init(&r, 1), -1);  // Kích thước nhỏ hơn tối thiểu
    assert_int_equal(ringbuffer_init(&r, MAX_SIZE + 1), -1);  // Kích thước lớn hơn tối đa
}
/*Khởi tạo buffer với con trỏ NULL*/
static void test_ringbuffer_init_null(void **state) {
    (void) state;
    assert_int_equal(ringbuffer_init(NULL, TEST_SIZE), -1);
}
/*Thêm phần tử vào ringbuffer với con trỏ NULL*/
static void test_ringbuffer_add_null(void **state) {
    (void) state;
    assert_int_equal(ringbuffer_add(NULL, 10), -1);
}
/* Remove phần tử với con trỏ NULL */
static void test_ringbuffer_remove_null(void **state) {
    (void) state;
    int value;
    assert_int_equal(ringbuffer_remove(NULL, &value), -1);
}

/* Thêm phần phần tử đến khi đầy và tiếp tục add thêm một phần tử nữa*/
static void test_ringbuffer_add(void **state) {
    (void) state;
    ringbuffer_init(&r, TEST_SIZE);

    for (int i = 1; i < TEST_SIZE + 1; i++) {
        assert_int_equal(ringbuffer_add(&r, i), 0);
    }
    assert_int_equal(ringbuffer_add(&r, 10), -1);
}
/*Remove phần tử với buffer rỗng và buffer có phần tử*/
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
/* Kiểm tra buffer có full hay không bằng cách truyền vào con trỏ NULL*/
static void test_ringbuffer_is_full_null(void **state) {
    (void) state;
    assert_int_equal(ringbuffer_is_full(NULL), -1);
}

/* Kiểm tra full khi mới khởi tạo và sau khi add đầy*/
static void test_ringbuffer_is_full(void **state) {
    (void) state;
    ringbuffer_init(&r, TEST_SIZE);
    assert_false(ringbuffer_is_full(&r));

    for (int i = 1; i < TEST_SIZE + 1; i++) {
        ringbuffer_add(&r, i);
    }
    assert_true(ringbuffer_is_full(&r));
}

/* Kiểm tra empty truyền vào con trỏ NULL*/
static void test_ringbuffer_is_empty_null(void **state) {
    (void) state;
    assert_int_equal(ringbuffer_is_empty(NULL), -1);
}

/* Kiểm tra empty sau khi khởi tạo và sau khi add 1 phần tử*/
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
/* Kiểm tra size truyền vào con trỏ NULL*/
static void test_ringbuffer_size_null(void **state) {
    (void) state;
    assert_int_equal(ringbuffer_size(NULL), -1);
}

/* Kiểm tra size sau khi add thêm 3 phần tử */
static void test_ringbuffer_size(void **state) {
    (void) state;
    ringbuffer_init(&r, TEST_SIZE);
    
    ringbuffer_add(&r, 1);
    ringbuffer_add(&r, 2);
    ringbuffer_add(&r, 3);
    
    assert_int_equal(ringbuffer_size(&r), 3);
}
/* Kiểm tra thêm và xóa giá trị trong trường hợp buffer đã đầy rồi bị rỗng */
static void test_ringbuffer_wraparound(void **state) {
    (void) state;
    int value;
    ringbuffer_init(&r, TEST_SIZE);

    for (int i = 1; i < TEST_SIZE + 1; i++) {
        ringbuffer_add(&r, i);
    }

    // Xóa một vài phần tử
    ringbuffer_remove(&r, &value);
    ringbuffer_remove(&r, &value);

    // Thêm lại để kiểm tra tail có quay vòng không
    ringbuffer_add(&r, 100);
    ringbuffer_add(&r, 101);
    
    assert_int_equal(r.tail, 2);
    
}



int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ringbuffer_init),
        cmocka_unit_test(test_ringbuffer_add),
        cmocka_unit_test(test_ringbuffer_remove),
        cmocka_unit_test(test_ringbuffer_is_full),
        cmocka_unit_test(test_ringbuffer_is_empty),
        cmocka_unit_test(test_ringbuffer_size),

        cmocka_unit_test(test_ringbuffer_init_null),
        cmocka_unit_test(test_ringbuffer_add_null),
        cmocka_unit_test(test_ringbuffer_remove_null),
        cmocka_unit_test(test_ringbuffer_is_full_null),
        cmocka_unit_test(test_ringbuffer_is_empty_null),
        cmocka_unit_test(test_ringbuffer_size_null),
        cmocka_unit_test(test_ringbuffer_init_invalid_size),
        cmocka_unit_test(test_ringbuffer_wraparound),

    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}
