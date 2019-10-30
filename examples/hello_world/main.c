#include <stdio.h>
#include <unistd.h>
#include "subprocess.h"

static void hello(void *arg_p)
{
    printf("Hello %s on stdout!\n", (char *)arg_p);
    fprintf(stderr, "Hello %s on stderr!\n", (char *)arg_p);
}

int main()
{
    struct subprocess_result_t *result_p;

    result_p = subprocess_call(hello, "World");

    if (result_p != NULL) {
        subprocess_result_print(result_p);
        subprocess_result_free(result_p);
    } else {
        printf("hello() never called.\n");
    }

    return (0);
}
