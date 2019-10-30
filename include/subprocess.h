#include <string.h>

typedef int (*subprocess_entry_t)(void *arg_p);

struct subprocess_output_t {
    /* Always null-terminated. */
    char *buf_p;
    /* Buffer length, without null-termination. */
    size_t length;
    size_t size;
};

struct subprocess_result_t {
    /* Entry function return value. */
    int res;
    struct subprocess_output_t stdout;
    struct subprocess_output_t stderr;
};

/**
 * Call given function with given argument in a subprocess. Captures
 * stdout and stderr.
 */
struct subprocess_result_t *subprocess_call(subprocess_entry_t entry,
                                            void *arg_p);

void subprocess_result_free(struct subprocess_result_t *self_p);
