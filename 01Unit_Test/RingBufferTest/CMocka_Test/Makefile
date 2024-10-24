.PHONY: test install

CUR_DIR := .

CMOCKA_DIR=$(shell pwd)/cmocka-1.1.0
CMOCKA_BUILD_DIR=$(CMOCKA_DIR)/build
CMOCKA_OUT_DIR=$(CMOCKA_BUILD_DIR)/output


LCOV_FLAG := --coverage
LCOV := lcov
GENHTML := genhtml
COVERAGE_DIR := $(CUR_DIR)/coverage


all: test

test:
	gcc test.c my_function.c -L./lib -I./ -I./include -lcmocka -o cmockatest $(LCOV_FLAG)

install:
	curl https://cmocka.org/files/1.1/cmocka-1.1.0.tar.xz -o cmocka.tar
	tar xf cmocka.tar
	rm cmocka.tar
	mkdir -p $(CMOCKA_OUT_DIR)
	cd $(CMOCKA_BUILD_DIR) && \
		 cmake -DWITH_STATIC_LIB=1 -DCMAKE_INSTALL_PREFIX=$(CMOCKA_OUT_DIR) .. && \
		 make && \
		 make install
	mkdir -p lib include
	cp $(CMOCKA_OUT_DIR)/lib/libcmocka.a lib
	cp $(CMOCKA_OUT_DIR)/include/*.h include
	rm -R $(CMOCKA_DIR)

run:
	./cmockatest

# Mục để thu thập và tạo báo cáo coverage
coverage: test run
	@mkdir -p $(COVERAGE_DIR)  # Đảm bảo thư mục coverage tồn tại
	$(LCOV) --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info
	$(GENHTML) $(COVERAGE_DIR)/coverage.info --output-directory $(COVERAGE_DIR)

clean:
	rm -rf cmockatest
