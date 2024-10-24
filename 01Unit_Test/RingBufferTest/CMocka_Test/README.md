### Installation

```sh
$ make install
```

This will copy `libcmoacka` static library to `lib/libcmocka.a` and two `.h` files into `include`.

### Compilation

```sh
$ make test
```

### Running test

```
$ make run
[==========] Running 14 test(s).
[ RUN      ] test_ringbuffer_init
[       OK ] test_ringbuffer_init
[ RUN      ] test_ringbuffer_add
[       OK ] test_ringbuffer_add
[ RUN      ] test_ringbuffer_remove
[       OK ] test_ringbuffer_remove
[ RUN      ] test_ringbuffer_is_full
[       OK ] test_ringbuffer_is_full
[ RUN      ] test_ringbuffer_is_empty
[       OK ] test_ringbuffer_is_empty
[ RUN      ] test_ringbuffer_size
[       OK ] test_ringbuffer_size
[ RUN      ] test_ringbuffer_init_null
[       OK ] test_ringbuffer_init_null
[ RUN      ] test_ringbuffer_add_null
[       OK ] test_ringbuffer_add_null
[ RUN      ] test_ringbuffer_remove_null
[       OK ] test_ringbuffer_remove_null
[ RUN      ] test_ringbuffer_is_full_null
[       OK ] test_ringbuffer_is_full_null
[ RUN      ] test_ringbuffer_is_empty_null
[       OK ] test_ringbuffer_is_empty_null
[ RUN      ] test_ringbuffer_size_null
[       OK ] test_ringbuffer_size_null
[ RUN      ] test_ringbuffer_init_invalid_size
[       OK ] test_ringbuffer_init_invalid_size
[ RUN      ] test_ringbuffer_wraparound
[       OK ] test_ringbuffer_wraparound
[==========] 14 test(s) run.
[  PASSED  ] 14 test(s).
```

### Clean
```
$ make clean

```
