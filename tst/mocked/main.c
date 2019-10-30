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
#include "__mocks__.h"
#include "narwhal.h"

static void call_no_output(void *arg_p)
{
    (void)arg_p;
}

TEST(test_call_stdout_pipe_fail)
{
    struct subprocess_result_t *result_p;

    MOCK(close)->reset();
    MOCK(pipe)->reset();
    MOCK(pipe)->mock_return(-1);

    result_p = subprocess_call(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);
    ASSERT_EQ(MOCK(pipe)->call_count, 1);
    ASSERT_EQ(MOCK(close)->call_count, 0);
}

#if 0

TEST(test_call_stderr_pipe_fail)
{
    struct subprocess_result_t *result_p;

    MOCK(pipe)
        ->mock_return_once(0)
        ->mock_return_once(-1);

    result_p = subprocess_call(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);
}

#endif

static int test_call_fork_fail_pipe(int arg1[2])
{
    static int fd = 1;

    arg1[0] = fd++;
    arg1[1] = fd++;

    return (0);
}

TEST(test_call_fork_fail)
{
    struct subprocess_result_t *result_p;

    MOCK(close)->reset();
    MOCK(close)->mock_return(0);
    MOCK(pipe)->mock_implementation(test_call_fork_fail_pipe);
    MOCK(fork)->mock_return(-1);

    result_p = subprocess_call(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);
    ASSERT_EQ(MOCK(close)->call_count, 4);
    ASSERT_EQ(MOCK(close)->last_call->arg1, 2);
}

int main()
{
    return RUN_TESTS(
        test_call_stdout_pipe_fail,
#if 0
        test_call_stderr_pipe_fail,
#endif
        test_call_fork_fail
    );
}
