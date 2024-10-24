.PHONY: mk_objs_shared_lib mk_objs_static_lib mk_shared mk_static install all_shared_lib all_static_lib clean coverage

LIB_NAME := test
CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/objs

LIB_DIR := $(CUR_DIR)/libs
LIB_STATIC := $(LIB_DIR)/static
LIB_SHARED := $(LIB_DIR)/shared

INC_FLAGS := -I $(INC_DIR)
CC := gcc
PTHREAD_FLAG := -pthread  # Thêm cờ pthread
LCOV_FLAG := --coverage
LCOV := lcov
GENHTML := genhtml
COVERAGE_DIR := $(CUR_DIR)/coverage

mk_objs_static_lib:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS) $(PTHREAD_FLAG) $(LCOV_FLAG)
	$(CC) -c $(SRC_DIR)/ringbuf.c -o $(OBJ_DIR)/ringbuf.o $(INC_FLAGS) $(LCOV_FLAG)

mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME).a $(OBJ_DIR)/ringbuf.o 

all_static_lib: mk_objs_static_lib mk_static
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC) -l$(LIB_NAME) -o $(BIN_DIR)/use-static-library $(PTHREAD_FLAG) $(LCOV_FLAG)

run_tests:
	$(BIN_DIR)/use-static-library

# Mục để thu thập và tạo báo cáo coverage
coverage: all_static_lib run_tests
	@mkdir -p $(COVERAGE_DIR)  # Đảm bảo thư mục coverage tồn tại
	$(LCOV) --capture --directory $(OBJ_DIR) --output-file $(COVERAGE_DIR)/coverage.info
	$(GENHTML) $(COVERAGE_DIR)/coverage.info --output-directory $(COVERAGE_DIR)

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED)/*
	rm -rf $(LIB_STATIC)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(COVERAGE_DIR)/*
