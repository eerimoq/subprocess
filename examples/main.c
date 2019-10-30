#include <stdio.h>
#include <unistd.h>
#include "subprocess.h"

static int foo(void *arg_p)
{
    printf("foo pid: %d\n", getpid());
    printf("arg_p: \"%s\"\n", (char *)arg_p);
    printf("hello on stdout\n");
    fprintf(stderr, "hello on stderr\n");

    return (5);
}

int main()
{
    struct subprocess_result_t *result_p;

    printf("main pid: %d\n", getpid());
    result_p = subprocess_call(foo, "the argument");

    if (result_p == NULL) {
        printf("Call failed!\n");
        return (1);
    }

    printf("foo returned %d\n\n", result_p->res);
    printf("stdout:\n");
    printf("%s\n", result_p->stdout.buf_p);
    printf("stderr:\n");
    printf("%s\n", result_p->stderr.buf_p);
    subprocess_result_free(result_p);

    return (0);
}
