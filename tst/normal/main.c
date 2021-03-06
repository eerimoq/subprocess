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

#include <stdlib.h>
#include "subprocess.h"
#include "nala.h"

static void call_no_output(void *arg_p)
{
    (void)arg_p;
}

TEST(test_call)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call(call_no_output, NULL);

    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 0);
    ASSERT_EQ(result_p->stderr.length, 0);

    CAPTURE_OUTPUT(output, errput) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout (length: 0):\n"
              "\n"
              "stderr (length: 0):\n"
              "\n");
}

TEST(test_call_output_no_output)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call_output(call_no_output, NULL);

    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 0);
    ASSERT_EQ(result_p->stderr.length, 0);

    CAPTURE_OUTPUT(output, errput) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout (length: 0):\n"
              "\n"
              "stderr (length: 0):\n"
              "\n");
}

static void call_stdout(const char *text_p)
{
    printf("%s", text_p);
}

TEST(test_call_output_stdout)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call_output((subprocess_entry_t)call_stdout, "Hello!");

    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 6);
    ASSERT_EQ(result_p->stderr.length, 0);

    CAPTURE_OUTPUT(output, errput) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout (length: 6):\n"
              "Hello!\n"
              "stderr (length: 0):\n"
              "\n");
}

TEST(test_call_no_captured_stdout)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call((subprocess_entry_t)call_stdout, "Hello!");

    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 0);
    ASSERT_EQ(result_p->stderr.length, 0);

    CAPTURE_OUTPUT(output, errput) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout (length: 0):\n"
              "\n"
              "stderr (length: 0):\n"
              "\n");
}

static void call_stderr(const char *text_p)
{
    fprintf(stderr, "%s", text_p);
}

TEST(test_call_output_stderr)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call_output((subprocess_entry_t)call_stderr, "Hello!");

    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 0);
    ASSERT_EQ(result_p->stderr.length, 6);

    CAPTURE_OUTPUT(output, errput) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout (length: 0):\n"
              "\n"
              "stderr (length: 6):\n"
              "Hello!\n");
}

static void call_exit(void *arg_p)
{
    printf("Hello!");
    exit(1);
}

TEST(test_call_output_exit)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call_output(call_exit, NULL);

    CAPTURE_OUTPUT(output, errput) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 1\n"
              "stdout (length: 6):\n"
              "Hello!\n"
              "stderr (length: 0):\n"
              "\n");
}

/**
 * Hopefully big enough to fill the output pipes.
 */
static void call_long_output(void *arg_p)
{
    int i;

    for (i = 0; i < 200000; i++) {
        printf("123");
        fprintf(stderr, "456");
    }
}

TEST(test_call_output_long_output)
{
    int i;
    struct subprocess_result_t *result_p;

    result_p = subprocess_call_output(call_long_output, NULL);

    ASSERT_EQ(result_p->stdout.length, 600000);
    ASSERT_EQ(result_p->stderr.length, 600000);

    for (i = 0; i < 200000; i++) {
        ASSERT_EQ(result_p->stdout.buf_p[3 * i + 0], '1');
        ASSERT_EQ(result_p->stdout.buf_p[3 * i + 1], '2');
        ASSERT_EQ(result_p->stdout.buf_p[3 * i + 2], '3');
        ASSERT_EQ(result_p->stderr.buf_p[3 * i + 0], '4');
        ASSERT_EQ(result_p->stderr.buf_p[3 * i + 1], '5');
        ASSERT_EQ(result_p->stderr.buf_p[3 * i + 2], '6');
    }

    subprocess_result_free(result_p);
}

TEST(test_exec_no_captured_stdout)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_exec("cat test_exec_stdout.txt");

    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 0);
    ASSERT_EQ(result_p->stderr.length, 0);

    CAPTURE_OUTPUT(output, errput) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout (length: 0):\n"
              "\n"
              "stderr (length: 0):\n"
              "\n");
}

TEST(test_exec_output_stdout)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_exec_output("cat test_exec_stdout.txt");

    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 7);
    ASSERT_EQ(result_p->stderr.length, 0);

    CAPTURE_OUTPUT(output, errput) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout (length: 7):\n"
              "hello!\n"
              "\n"
              "stderr (length: 0):\n"
              "\n");
}

TEST(test_exec_output_false)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_exec_output("false");

    ASSERT_EQ(result_p->exit_code, 1);
    ASSERT_EQ(result_p->stdout.length, 0);
    ASSERT_EQ(result_p->stderr.length, 0);

    subprocess_result_free(result_p);
}

TEST(test_exec_output_error_bad_command)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_exec_output("test_exec_error_bad_command");

    ASSERT_EQ(result_p->exit_code, 127);
    ASSERT_EQ(result_p->stdout.length, 0);
    ASSERT_EQ(result_p->stderr.length, 46);

    CAPTURE_OUTPUT(output, errput) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 127\n"
              "stdout (length: 0):\n"
              "\n"
              "stderr (length: 46):\n"
              "sh: 1: test_exec_error_bad_command: not found\n"
              "\n");
}

TEST(test_completed_successfully)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call(call_no_output, NULL);

    ASSERT_NE(result_p, NULL);
    ASSERT_EQ(subprocess_completed_successfully(result_p), true);
    subprocess_result_free(result_p);
}

TEST(test_completed_successfully_exit_1)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call(call_exit, NULL);

    ASSERT_NE(result_p, NULL);
    ASSERT_EQ(subprocess_completed_successfully(result_p), false);
    subprocess_result_free(result_p);
}
