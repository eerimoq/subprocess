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

    MOCK(pipe)->mock_once(-1);
    MOCK(close)->mock_none();

    result_p = subprocess_call_output(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);

    MOCK(pipe)->assert_completed();
    MOCK(close)->assert_completed();
}

TEST(test_call_stderr_pipe_fail)
{
    struct subprocess_result_t *result_p;
    int stdoutfds[2] = { 3, 4 };

    MOCK(pipe)
        ->mock_once(0)
        ->set___pipedes_out(&stdoutfds[0], sizeof(stdoutfds));
    MOCK(pipe)->mock_once(-1);
    MOCK(fork)->mock_none();
    MOCK(close)->mock_once(stdoutfds[0], 0);
    MOCK(close)->mock_once(stdoutfds[1], 0);

    result_p = subprocess_call_output(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);

    MOCK(pipe)->assert_completed();
    MOCK(fork)->assert_completed();
    MOCK(close)->assert_completed();
}

TEST(test_call_fork_fail)
{
    struct subprocess_result_t *result_p;
    int stdoutfds[2] = { 3, 4 };
    int stderrfds[2] = { 5, 6 };

    MOCK(pipe)
        ->mock_once(0)
        ->set___pipedes_out(&stdoutfds[0], sizeof(stdoutfds));
    MOCK(pipe)
        ->mock_once(0)
        ->set___pipedes_out(&stderrfds[0], sizeof(stderrfds));
    MOCK(fork)->mock_once(-1);
    MOCK(close)->mock_once(stderrfds[0], 0);
    MOCK(close)->mock_once(stderrfds[1], 0);
    MOCK(close)->mock_once(stdoutfds[0], 0);
    MOCK(close)->mock_once(stdoutfds[1], 0);

    result_p = subprocess_call_output(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);

    MOCK(pipe)->assert_completed();
    MOCK(fork)->assert_completed();
    MOCK(close)->assert_completed();
}

TEST(test_completed_successfully_result_null)
{
    struct subprocess_result_t *result_p;

    MOCK(fork)->mock_once(-1);

    result_p = subprocess_call(call_no_output, NULL);

    ASSERT_EQ(result_p, NULL);
    ASSERT_EQ(subprocess_completed_successfully(result_p), false);

    MOCK(fork)->assert_completed();
}
