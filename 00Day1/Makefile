.PHONY: mk_objs_shared_lib mk_objs_static_lib mk_shared mk_static install all_shared_lib all_static_lib clean

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

mk_objs_static_lib:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS) $(PTHREAD_FLAG)
	$(CC) -c $(SRC_DIR)/ringbuf.c -o $(OBJ_DIR)/ringbuf.o $(INC_FLAGS)

mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME).a $(OBJ_DIR)/ringbuf.o 

all_static_lib: mk_objs_static_lib mk_static
	$(CC)  $(OBJ_DIR)/main.o  -L$(LIB_STATIC) -l$(LIB_NAME) -o $(BIN_DIR)/use-static-library $(PTHREAD_FLAG)

clean: 
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED)/*
	rm -rf $(LIB_STATIC)/*
	rm -rf $(BIN_DIR)/*






