#include <dbg.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "subprocess.h"

static void output_init(struct subprocess_output_t *self_p)
{
    self_p->length = 0;
    self_p->size = 4096;
    self_p->buf_p = malloc(self_p->size);
}

static struct subprocess_result_t *result_new(void)
{
    struct subprocess_result_t *result_p;

    result_p = malloc(sizeof(*result_p));

    if (result_p != NULL) {
        result_p->res = -1;
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
                       int *stderrfds_p,
                       int resfd)
{
    int res;

    while ((dup2(stdoutfds_p[1], STDOUT_FILENO) == -1) && (errno == EINTR));
    close(stdoutfds_p[1]);
    close(stdoutfds_p[0]);
    while ((dup2(stderrfds_p[1], STDERR_FILENO) == -1) && (errno == EINTR));
    close(stderrfds_p[1]);
    close(stderrfds_p[0]);
    res = entry(arg_p);
    write(resfd, &res, sizeof(res));
}

static struct subprocess_result_t *call_parent(int *stdoutfds_p,
                                            int *stderrfds_p,
                                            int *resfds_p)
{
    struct subprocess_result_t *result_p;
    int res;

    result_p = result_new();

    if (result_p == NULL) {
        return (NULL);
    }

    close(resfds_p[1]);
    close(stdoutfds_p[1]);
    close(stderrfds_p[1]);

    /* Poll result, stdout and stderr pipes. */
    output_append(&result_p->stdout, stdoutfds_p[0]);
    output_append(&result_p->stderr, stderrfds_p[0]);
    res = read(resfds_p[0], &result_p->res, sizeof(result_p->res));

    if (res != sizeof(result_p->res)) {
        fatal_error("read");
    }

    close(resfds_p[0]);
    close(stdoutfds_p[0]);
    close(stderrfds_p[0]);

    return (result_p);
}

struct subprocess_result_t *subprocess_call(subprocess_entry_t entry,
                                            void *arg_p)
{
    pid_t pid;
    int resfds[2];
    int stdoutfds[2];
    int stderrfds[2];
    struct subprocess_result_t *result_p;

    if (pipe(resfds) < 0) {
        return (NULL);
    }

    if (pipe(stdoutfds) < 0) {
        goto out1;
    }

    if (pipe(stderrfds) < 0) {
        goto out2;
    }

    pid = fork();

    if (pid < 0) {
        goto out3;
    } else if (pid == 0) {
        call_child(entry, arg_p, &stdoutfds[0], &stderrfds[0], resfds[1]);
        exit(0);
    } else {
        result_p = call_parent(&stdoutfds[0], &stderrfds[0], &resfds[0]);
    }

    return (result_p);

 out3:
    close(stderrfds[0]);
    close(stderrfds[1]);

 out2:
    close(stdoutfds[0]);
    close(stdoutfds[1]);

 out1:
    close(resfds[0]);
    close(resfds[1]);

    return (NULL);
}

void subprocess_result_print(struct subprocess_result_t *self_p)
{
    printf("res: %d\n", self_p->res);
    printf("stdout:\n");
    printf("%s", self_p->stdout.buf_p);
    printf("stderr:\n");
    printf("%s", self_p->stderr.buf_p);
}

void subprocess_result_free(struct subprocess_result_t *self_p)
{
    free(self_p->stdout.buf_p);
    free(self_p->stderr.buf_p);
    free(self_p);
}
