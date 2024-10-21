.PHONY: test install

CMOCKA_DIR=$(shell pwd)/cmocka-1.1.0
CMOCKA_BUILD_DIR=$(CMOCKA_DIR)/build
CMOCKA_OUT_DIR=$(CMOCKA_BUILD_DIR)/output

all: test

test:
	gcc test.c my_function.c -L./lib -I./ -I./include -lcmocka -o cmockatest

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

clean:
	rm -rf cmockatest