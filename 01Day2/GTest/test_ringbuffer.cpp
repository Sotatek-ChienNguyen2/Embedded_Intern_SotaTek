#include <gtest/gtest.h>
extern "C" {
    #include "my_function.h"  // Bao gồm mã C vào C++
}

extern RingBuffer_t r;

// Kiểm thử hàm khởi tạo (init)
TEST(RingBufferTest, InitBuffer) {
    ringbuffer_init(5);  // Khởi tạo buffer với kích thước 5
    EXPECT_EQ(r.max_size, 5);  // Kích thước tối đa là 5
    EXPECT_EQ(r.size, 0);      // Ban đầu kích thước là 0
    EXPECT_EQ(r.head, 0);      // Vị trí đầu là 0
    EXPECT_EQ(r.tail, 0);      // Vị trí đuôi là 0
}

// Kiểm thử thêm phần tử vào buffer
TEST(RingBufferTest, AddElement) {
    ringbuffer_init(3);  // Khởi tạo buffer với kích thước 3
    EXPECT_EQ(ringbuffer_add(10), 0);  // Thêm giá trị 10
    EXPECT_EQ(r.buffer[0], 10);        // Kiểm tra phần tử đầu tiên
    EXPECT_EQ(r.size, 1);              // Kích thước buffer tăng lên 1
}

// Kiểm thử khi buffer đầy
TEST(RingBufferTest, AddWhenFull) {
    ringbuffer_init(2);  // Khởi tạo buffer với kích thước 2
    ringbuffer_add(10);  // Thêm giá trị 10
    ringbuffer_add(20);  // Thêm giá trị 20
    EXPECT_EQ(ringbuffer_add(30), -1);  // Không thể thêm, buffer đầy
    EXPECT_EQ(r.size, 2);               // Kích thước tối đa là 2
}

// Kiểm thử loại bỏ phần tử từ buffer
TEST(RingBufferTest, RemoveElement) {
    ringbuffer_init(3);  // Khởi tạo buffer
    ringbuffer_add(10);  // Thêm giá trị 10
    ringbuffer_add(20);  // Thêm giá trị 20
    int value;
    EXPECT_EQ(ringbuffer_remove(&value), 0);  // Loại bỏ thành công
    EXPECT_EQ(value, 10);                     // Giá trị đầu tiên bị loại bỏ là 10
    EXPECT_EQ(r.size, 1);                     // Kích thước giảm còn 1
}

// Kiểm thử khi buffer rỗng
TEST(RingBufferTest, RemoveWhenEmpty) {
    ringbuffer_init(3);  // Khởi tạo buffer
    int value;
    EXPECT_EQ(ringbuffer_remove(&value), -1);  // Không thể loại bỏ, buffer rỗng
    EXPECT_EQ(r.size, 0);                      // Kích thước vẫn là 0
}

// Kiểm thử hàm kiểm tra đầy (is_full)
TEST(RingBufferTest, IsFull) {
    ringbuffer_init(2);  // Khởi tạo buffer với kích thước 2
    ringbuffer_add(10);
    ringbuffer_add(20);
    EXPECT_EQ(ringbuffer_is_full(), 1);  // Buffer đã đầy
}

// Kiểm thử hàm kiểm tra rỗng (is_empty)
TEST(RingBufferTest, IsEmpty) {
    ringbuffer_init(2);  // Khởi tạo buffer
    EXPECT_EQ(ringbuffer_is_empty(), 1);  // Ban đầu buffer rỗng
    ringbuffer_add(10);
    EXPECT_EQ(ringbuffer_is_empty(), 0);  // Sau khi thêm buffer không rỗng nữa
}

// Kiểm thử kích thước buffer
TEST(RingBufferTest, SizeCheck) {
    ringbuffer_init(5);  // Khởi tạo buffer
    ringbuffer_add(10);
    ringbuffer_add(20);
    EXPECT_EQ(ringbuffer_size(), 2);  // Kích thước là 2
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
