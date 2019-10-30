/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * This file is part of the subprocess project.
 */

#include <string.h>

typedef void (*subprocess_entry_t)(void *arg_p);

struct subprocess_output_t {
    /* Always null-terminated. */
    char *buf_p;
    /* Buffer length, without null-termination. */
    size_t length;
    size_t size;
};

struct subprocess_result_t {
    int exit_code;
    struct subprocess_output_t stdout;
    struct subprocess_output_t stderr;
};

/**
 * Call given function with given argument in a subprocess. Retruns
 * captured subprocess' stdout, stderr and exit code.
 *
 * Returns NULL if the subprocess could not be started.
 */
struct subprocess_result_t *subprocess_call(subprocess_entry_t entry,
                                            void *arg_p);

/**
 * Print subprocess exit code, stdout and stderr.
 */
void subprocess_result_print(struct subprocess_result_t *self_p);

/**
 * Free given result.
 */
void subprocess_result_free(struct subprocess_result_t *self_p);
