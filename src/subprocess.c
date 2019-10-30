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

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "subprocess.h"

static void output_init(struct subprocess_output_t *self_p)
{
    self_p->length = 0;
    self_p->size = 4096;
    self_p->buf_p = malloc(self_p->size);
    self_p->buf_p[0] = '\0';
}

static void output_print(struct subprocess_output_t *self_p,
                         const char *name_p)
{
    printf("%s (length: %ld):\n", name_p, self_p->length);
    printf("%s\n", self_p->buf_p);
}

static struct subprocess_result_t *result_new(void)
{
    struct subprocess_result_t *result_p;

    result_p = malloc(sizeof(*result_p));

    if (result_p != NULL) {
        result_p->exit_code = -1;
        output_init(&result_p->stdout);
        output_init(&result_p->stderr);
    }

    return (result_p);
}

static void fatal_error(const char *message_p)
{
    perror(message_p);
    exit(1);
}

static void output_append(struct subprocess_output_t *self_p, int fd)
{
    ssize_t res;

    while (1) {
        res = read(fd,
                   &self_p->buf_p[self_p->length],
                   self_p->size - self_p->length - 1);

        if (res == 0) {
            break;
        } else if (res > 0) {
            self_p->length += res;
            self_p->buf_p[self_p->length] = '\0';

            if ((self_p->length + 1) == self_p->size) {
                self_p->size += 4096;
                self_p->buf_p = realloc(self_p->buf_p, self_p->size);
            }
        } else {
            if (errno != EINTR) {
                fatal_error("read");
            }
        }
    }
}

static void call_child(subprocess_entry_t entry,
                       void *arg_p,
                       int *stdoutfds_p,
                       int *stderrfds_p)
{
    while ((dup2(stdoutfds_p[1], STDOUT_FILENO) == -1) && (errno == EINTR));
    close(stdoutfds_p[1]);
    close(stdoutfds_p[0]);
    while ((dup2(stderrfds_p[1], STDERR_FILENO) == -1) && (errno == EINTR));
    close(stderrfds_p[1]);
    close(stderrfds_p[0]);
    entry(arg_p);
}

static struct subprocess_result_t *call_parent(pid_t child_pid,
                                               int *stdoutfds_p,
                                               int *stderrfds_p)
{
    struct subprocess_result_t *result_p;
    int status;

    result_p = result_new();

    if (result_p == NULL) {
        return (NULL);
    }

    close(stdoutfds_p[1]);
    close(stderrfds_p[1]);

    /* Poll result, stdout and stderr pipes. */
    output_append(&result_p->stdout, stdoutfds_p[0]);
    output_append(&result_p->stderr, stderrfds_p[0]);
    close(stdoutfds_p[0]);
    close(stderrfds_p[0]);

    waitpid(child_pid, &status, 0);

    if (WIFEXITED(status)) {
        result_p->exit_code = WEXITSTATUS(status);
    }

    return (result_p);
}

struct subprocess_result_t *subprocess_call(subprocess_entry_t entry,
                                            void *arg_p)
{
    pid_t pid;
    int stdoutfds[2];
    int stderrfds[2];
    struct subprocess_result_t *result_p;

    if (pipe(stdoutfds) < 0) {
        return (NULL);
    }

    if (pipe(stderrfds) < 0) {
        goto out1;
    }

    pid = fork();

    if (pid < 0) {
        goto out2;
    } else if (pid == 0) {
        call_child(entry, arg_p, &stdoutfds[0], &stderrfds[0]);
        exit(0);
    } else {
        result_p = call_parent(pid, &stdoutfds[0], &stderrfds[0]);
    }

    return (result_p);

 out2:
    close(stderrfds[0]);
    close(stderrfds[1]);

 out1:
    close(stdoutfds[0]);
    close(stdoutfds[1]);

    return (NULL);
}

void subprocess_result_print(struct subprocess_result_t *self_p)
{
    printf("exit_code: %d\n", self_p->exit_code);
    output_print(&self_p->stdout, "stdout");
    output_print(&self_p->stderr, "stderr");
}

void subprocess_result_free(struct subprocess_result_t *self_p)
{
    free(self_p->stdout.buf_p);
    free(self_p->stderr.buf_p);
    free(self_p);
}
