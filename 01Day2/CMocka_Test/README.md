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
$ ./cmockatest
[==========] Running 6 test(s).
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
[==========] 6 test(s) run.
[  PASSED  ] 6 test(s).
```