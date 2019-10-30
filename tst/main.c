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

#include "subprocess.h"
#include "narwhal.h"

static void call_no_output(void *arg_p)
{
    (void)arg_p;
}

TEST(test_call_no_output)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call(call_no_output, NULL);
    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 0);
    ASSERT_EQ(result_p->stderr.length, 0);

    CAPTURE_OUTPUT(output) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout:\n"
              "\n"
              "stderr:\n"
              "\n");
}

static void call_stdout(const char *text_p)
{
    printf("%s", text_p);
}

TEST(test_call_stdout)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call((subprocess_entry_t)call_stdout, "Hello!");
    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 6);
    ASSERT_EQ(result_p->stderr.length, 0);

    CAPTURE_OUTPUT(output) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout:\n"
              "Hello!\n"
              "stderr:\n"
              "\n");
}

static void call_stderr(const char *text_p)
{
    fprintf(stderr, "%s", text_p);
}

TEST(test_call_stderr)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call((subprocess_entry_t)call_stderr, "Hello!");
    ASSERT_EQ(result_p->exit_code, 0);
    ASSERT_EQ(result_p->stdout.length, 0);
    ASSERT_EQ(result_p->stderr.length, 6);

    CAPTURE_OUTPUT(output) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 0\n"
              "stdout:\n"
              "\n"
              "stderr:\n"
              "Hello!\n");
}

static void call_exit(void *arg_p)
{
    printf("Hello!");
    exit(1);
}

TEST(test_call_exit)
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call(call_exit, NULL);

    CAPTURE_OUTPUT(output) {
        subprocess_result_print(result_p);
    }

    subprocess_result_free(result_p);

    ASSERT_EQ(output,
              "exit_code: 1\n"
              "stdout:\n"
              "Hello!\n"
              "stderr:\n"
              "\n");
}

int main()
{
    return RUN_TESTS(
        test_call_no_output,
        test_call_stdout,
        test_call_stderr,
        test_call_exit
    );
}
