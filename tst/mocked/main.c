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

#include <sys/wait.h>
#include "subprocess.h"
#include "__mocks__.h"
#include "narwhal.h"
#include "mock_libc.h"

static void call_no_output(void *arg_p)
{
    (void)arg_p;
}

TEST(test_call_stdout_pipe_fail)
{
    struct subprocess_result_t *result_p;

    MOCK(pipe)->mock_return(-1);

    result_p = subprocess_call(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);
    ASSERT_EQ(MOCK(pipe)->call_count, 1);
    ASSERT_EQ(MOCK(close)->call_count, 0);
}

TEST(test_call_stderr_pipe_fail)
{
    struct subprocess_result_t *result_p;
    int stdoutfds[2] = { 3, 4 };
    int stderrfds[2] = { -1, -1 };

    mock_push_pipe(&stdoutfds[0], 0);
    mock_push_pipe(&stderrfds[0], -1);
    mock_push_close(stdoutfds[0], 0);
    mock_push_close(stdoutfds[1], 0);

    MOCK(pipe)->mock_implementation(mock_pipe);
    MOCK(close)->mock_implementation(mock_close);

    result_p = subprocess_call(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);
    ASSERT_EQ(MOCK(fork)->call_count, 0);
}

TEST(test_call_fork_fail)
{
    struct subprocess_result_t *result_p;
    int stdoutfds[2] = { 3, 4 };
    int stderrfds[2] = { 5, 6 };

    mock_push_pipe(&stdoutfds[0], 0);
    mock_push_pipe(&stderrfds[0], 0);
    mock_push_close(stderrfds[0], 0);
    mock_push_close(stderrfds[1], 0);
    mock_push_close(stdoutfds[0], 0);
    mock_push_close(stdoutfds[1], 0);

    MOCK(pipe)->mock_implementation(mock_pipe);
    MOCK(close)->mock_implementation(mock_close);
    MOCK(fork)->mock_return(-1);

    result_p = subprocess_call(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);
}

int main()
{
    return RUN_TESTS(
        test_call_stdout_pipe_fail,
        test_call_stderr_pipe_fail,
        test_call_fork_fail
    );
}
