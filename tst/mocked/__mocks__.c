/*
Mocks source file

Generated with Narmock v0.2.12 (https://github.com/vberlier/narmock)
Do not edit manually
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "narwhal.h"

#include <errno.h>
#include <stddef.h>

#include "__mocks__.h"

typedef struct _narmock_set_param _narmock_set_param;

struct _narmock_set_param {
    void *buf_p;
    size_t size;
};

static void *xmalloc(size_t size)
{
    void *buf_p;

    buf_p = malloc(size);

    if (buf_p == NULL) {
        perror("malloc");
        exit(1);
    }

    return (buf_p);
}

void narmock_reset_all_mocks(void)
{
    MOCK(close)->reset();
    MOCK(fork)->reset();
    MOCK(pipe)->reset();
    MOCK(read)->reset();
}

// NARMOCK_IMPLEMENTATION close

int __real_close(int __fd);

typedef struct _narmock_params_type_for_close _narmock_params_type_for_close;

struct _narmock_params_type_for_close
{
    int __fd;
    int return_value;
};

typedef struct _narmock_instance_type_for_close _narmock_instance_type_for_close;

struct _narmock_instance_type_for_close
{
    _narmock_params_type_for_close params;
    bool ignore___fd_in;
    int errno_value;
    _narmock_instance_type_for_close *next_p;
};

typedef struct _narmock_instances_type_for_close _narmock_instances_type_for_close;

struct _narmock_instances_type_for_close {
    _narmock_instance_type_for_close *head_p;
    _narmock_instance_type_for_close *tail_p;
};

typedef struct _narmock_private_state_type_for_close _narmock_private_state_type_for_close;

struct _narmock_private_state_type_for_close
{
    _narmock_state_type_for_close public;
    int mode;
    _narmock_instances_type_for_close instances;
    int (*implementation)(int __fd);
};

static const _narmock_state_type_for_close *_narmock_mock_once_function_for_close(int __fd, int return_value);
static const _narmock_state_type_for_close *_narmock_set_errno_function_for_close(int errno_value);
static const _narmock_state_type_for_close *_narmock_ignore___fd_in_function_for_close(void);
static const _narmock_state_type_for_close *_narmock_mock_none_function_for_close(void);
static const _narmock_state_type_for_close *_narmock_mock_implementation_function_for_close(int (*implementation)(int __fd));
static const _narmock_state_type_for_close *_narmock_disable_mock_function_for_close(void);
static const _narmock_state_type_for_close *_narmock_reset_function_for_close(void);
static const _narmock_state_type_for_close *_narmock_assert_completed_function_for_close(void);

static _narmock_private_state_type_for_close _narmock_state_for_close =
{
    .public = {
        .mock_once = _narmock_mock_once_function_for_close,
        .set_errno = _narmock_set_errno_function_for_close,
        .ignore___fd_in = _narmock_ignore___fd_in_function_for_close,
        .mock_none = _narmock_mock_none_function_for_close,
        .mock_implementation = _narmock_mock_implementation_function_for_close,
        .disable_mock = _narmock_disable_mock_function_for_close,
        .reset = _narmock_reset_function_for_close,
        .assert_completed = _narmock_assert_completed_function_for_close
    },
    .mode = 0,
    .instances = {
        .head_p = NULL,
        .tail_p = NULL
    }
};

int __wrap_close(int __fd)
{
    struct _narmock_instance_type_for_close *instance_p;
    int return_value;

    switch (_narmock_state_for_close.mode) {

    case 1:
        instance_p = _narmock_state_for_close.instances.head_p;

        if (instance_p == NULL) {
            FAIL();
            while (1);
        }

        if (!instance_p->ignore___fd_in) {
            ASSERT_EQ(__fd, instance_p->params.__fd);
        }


        _narmock_state_for_close.instances.head_p = instance_p->next_p;
        errno = instance_p->errno_value;
        return_value = instance_p->params.return_value;
        free(instance_p);
        break;

    case 2:
        return_value =
        _narmock_state_for_close.implementation(__fd);
        break;

    case 3:
        FAIL();
        while (1);
        break;

    default:
        return_value =
        __real_close(__fd);
        break;
    }

    return return_value;
}

static const _narmock_state_type_for_close *_narmock_mock_once_function_for_close(int __fd, int return_value)
{
    struct _narmock_instance_type_for_close *instance_p;

    _narmock_state_for_close.mode = 1;
    instance_p = xmalloc(sizeof(*instance_p));
    instance_p->params.__fd = __fd;
    instance_p->ignore___fd_in = false;
    instance_p->params.return_value = return_value;
    instance_p->errno_value = 0;
    instance_p->next_p = NULL;

    if (_narmock_state_for_close.instances.head_p == NULL) {
        _narmock_state_for_close.instances.head_p = instance_p;
    } else {
        _narmock_state_for_close.instances.tail_p->next_p = instance_p;
    }

    _narmock_state_for_close.instances.tail_p = instance_p;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_set_errno_function_for_close(int errno_value)
{
    if (_narmock_state_for_close.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_close.instances.tail_p->errno_value = errno_value;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_ignore___fd_in_function_for_close(void)
{
    if (_narmock_state_for_close.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_close.instances.tail_p->ignore___fd_in = true;

    return &_narmock_state_for_close.public;
}


static const _narmock_state_type_for_close *_narmock_mock_none_function_for_close(void)
{
    _narmock_state_for_close.mode = 3;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_mock_implementation_function_for_close(int (*implementation)(int __fd))
{
    _narmock_state_for_close.mode = 2;
    _narmock_state_for_close.implementation = implementation;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_disable_mock_function_for_close(void)
{
    _narmock_state_for_close.mode = 0;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_reset_function_for_close(void)
{
    _narmock_state_for_close.mode = 0;
    _narmock_state_for_close.instances.head_p = NULL;
    _narmock_state_for_close.instances.tail_p = NULL;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_assert_completed_function_for_close(void)
{
    ASSERT_EQ(_narmock_state_for_close.instances.head_p, NULL);

    return &_narmock_state_for_close.public;
}

const _narmock_state_type_for_close *_narmock_get_mock_for_close(const void *function)
{
    (void)function;

    return &_narmock_state_for_close.public;
}

// NARMOCK_IMPLEMENTATION fork

__pid_t __real_fork(void);

typedef struct _narmock_params_type_for_fork _narmock_params_type_for_fork;

struct _narmock_params_type_for_fork
{
    __pid_t return_value;
};

typedef struct _narmock_instance_type_for_fork _narmock_instance_type_for_fork;

struct _narmock_instance_type_for_fork
{
    _narmock_params_type_for_fork params;
    int errno_value;
    _narmock_instance_type_for_fork *next_p;
};

typedef struct _narmock_instances_type_for_fork _narmock_instances_type_for_fork;

struct _narmock_instances_type_for_fork {
    _narmock_instance_type_for_fork *head_p;
    _narmock_instance_type_for_fork *tail_p;
};

typedef struct _narmock_private_state_type_for_fork _narmock_private_state_type_for_fork;

struct _narmock_private_state_type_for_fork
{
    _narmock_state_type_for_fork public;
    int mode;
    _narmock_instances_type_for_fork instances;
    __pid_t (*implementation)(void);
};

static const _narmock_state_type_for_fork *_narmock_mock_once_function_for_fork(__pid_t return_value);
static const _narmock_state_type_for_fork *_narmock_set_errno_function_for_fork(int errno_value);
static const _narmock_state_type_for_fork *_narmock_mock_none_function_for_fork(void);
static const _narmock_state_type_for_fork *_narmock_mock_implementation_function_for_fork(__pid_t (*implementation)(void));
static const _narmock_state_type_for_fork *_narmock_disable_mock_function_for_fork(void);
static const _narmock_state_type_for_fork *_narmock_reset_function_for_fork(void);
static const _narmock_state_type_for_fork *_narmock_assert_completed_function_for_fork(void);

static _narmock_private_state_type_for_fork _narmock_state_for_fork =
{
    .public = {
        .mock_once = _narmock_mock_once_function_for_fork,
        .set_errno = _narmock_set_errno_function_for_fork,
        .mock_none = _narmock_mock_none_function_for_fork,
        .mock_implementation = _narmock_mock_implementation_function_for_fork,
        .disable_mock = _narmock_disable_mock_function_for_fork,
        .reset = _narmock_reset_function_for_fork,
        .assert_completed = _narmock_assert_completed_function_for_fork
    },
    .mode = 0,
    .instances = {
        .head_p = NULL,
        .tail_p = NULL
    }
};

__pid_t __wrap_fork(void)
{
    struct _narmock_instance_type_for_fork *instance_p;
    __pid_t return_value;

    switch (_narmock_state_for_fork.mode) {

    case 1:
        instance_p = _narmock_state_for_fork.instances.head_p;

        if (instance_p == NULL) {
            FAIL();
            while (1);
        }



        _narmock_state_for_fork.instances.head_p = instance_p->next_p;
        errno = instance_p->errno_value;
        return_value = instance_p->params.return_value;
        free(instance_p);
        break;

    case 2:
        return_value =
        _narmock_state_for_fork.implementation();
        break;

    case 3:
        FAIL();
        while (1);
        break;

    default:
        return_value =
        __real_fork();
        break;
    }

    return return_value;
}

static const _narmock_state_type_for_fork *_narmock_mock_once_function_for_fork(__pid_t return_value)
{
    struct _narmock_instance_type_for_fork *instance_p;

    _narmock_state_for_fork.mode = 1;
    instance_p = xmalloc(sizeof(*instance_p));
    instance_p->params.return_value = return_value;
    instance_p->errno_value = 0;
    instance_p->next_p = NULL;

    if (_narmock_state_for_fork.instances.head_p == NULL) {
        _narmock_state_for_fork.instances.head_p = instance_p;
    } else {
        _narmock_state_for_fork.instances.tail_p->next_p = instance_p;
    }

    _narmock_state_for_fork.instances.tail_p = instance_p;

    return &_narmock_state_for_fork.public;
}

static const _narmock_state_type_for_fork *_narmock_set_errno_function_for_fork(int errno_value)
{
    if (_narmock_state_for_fork.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_fork.instances.tail_p->errno_value = errno_value;

    return &_narmock_state_for_fork.public;
}



static const _narmock_state_type_for_fork *_narmock_mock_none_function_for_fork(void)
{
    _narmock_state_for_fork.mode = 3;

    return &_narmock_state_for_fork.public;
}

static const _narmock_state_type_for_fork *_narmock_mock_implementation_function_for_fork(__pid_t (*implementation)(void))
{
    _narmock_state_for_fork.mode = 2;
    _narmock_state_for_fork.implementation = implementation;

    return &_narmock_state_for_fork.public;
}

static const _narmock_state_type_for_fork *_narmock_disable_mock_function_for_fork(void)
{
    _narmock_state_for_fork.mode = 0;

    return &_narmock_state_for_fork.public;
}

static const _narmock_state_type_for_fork *_narmock_reset_function_for_fork(void)
{
    _narmock_state_for_fork.mode = 0;
    _narmock_state_for_fork.instances.head_p = NULL;
    _narmock_state_for_fork.instances.tail_p = NULL;

    return &_narmock_state_for_fork.public;
}

static const _narmock_state_type_for_fork *_narmock_assert_completed_function_for_fork(void)
{
    ASSERT_EQ(_narmock_state_for_fork.instances.head_p, NULL);

    return &_narmock_state_for_fork.public;
}

const _narmock_state_type_for_fork *_narmock_get_mock_for_fork(const void *function)
{
    (void)function;

    return &_narmock_state_for_fork.public;
}

// NARMOCK_IMPLEMENTATION pipe

int __real_pipe(int __pipedes[2]);

typedef struct _narmock_params_type_for_pipe _narmock_params_type_for_pipe;

struct _narmock_params_type_for_pipe
{
    int *__pipedes;
    int return_value;
};

typedef struct _narmock_instance_type_for_pipe _narmock_instance_type_for_pipe;

struct _narmock_instance_type_for_pipe
{
    _narmock_params_type_for_pipe params;
    bool ignore___pipedes_in;
    _narmock_set_param __pipedes_in;
    _narmock_set_param __pipedes_out;
    int errno_value;
    _narmock_instance_type_for_pipe *next_p;
};

typedef struct _narmock_instances_type_for_pipe _narmock_instances_type_for_pipe;

struct _narmock_instances_type_for_pipe {
    _narmock_instance_type_for_pipe *head_p;
    _narmock_instance_type_for_pipe *tail_p;
};

typedef struct _narmock_private_state_type_for_pipe _narmock_private_state_type_for_pipe;

struct _narmock_private_state_type_for_pipe
{
    _narmock_state_type_for_pipe public;
    int mode;
    _narmock_instances_type_for_pipe instances;
    int (*implementation)(int __pipedes[2]);
};

static const _narmock_state_type_for_pipe *_narmock_mock_once_function_for_pipe(int return_value);
static const _narmock_state_type_for_pipe *_narmock_set_errno_function_for_pipe(int errno_value);
static const _narmock_state_type_for_pipe *_narmock_set___pipedes_in_function_for_pipe(const void *buf_p, size_t size);
static const _narmock_state_type_for_pipe *_narmock_set___pipedes_in_pointer_function_for_pipe(int __pipedes[2]);
static const _narmock_state_type_for_pipe *_narmock_set___pipedes_out_function_for_pipe(const void *buf_p, size_t size);
static const _narmock_state_type_for_pipe *_narmock_mock_none_function_for_pipe(void);
static const _narmock_state_type_for_pipe *_narmock_mock_implementation_function_for_pipe(int (*implementation)(int __pipedes[2]));
static const _narmock_state_type_for_pipe *_narmock_disable_mock_function_for_pipe(void);
static const _narmock_state_type_for_pipe *_narmock_reset_function_for_pipe(void);
static const _narmock_state_type_for_pipe *_narmock_assert_completed_function_for_pipe(void);

static _narmock_private_state_type_for_pipe _narmock_state_for_pipe =
{
    .public = {
        .mock_once = _narmock_mock_once_function_for_pipe,
        .set_errno = _narmock_set_errno_function_for_pipe,
        .set___pipedes_in = _narmock_set___pipedes_in_function_for_pipe,
        .set___pipedes_in_pointer = _narmock_set___pipedes_in_pointer_function_for_pipe,
        .set___pipedes_out = _narmock_set___pipedes_out_function_for_pipe,
        .mock_none = _narmock_mock_none_function_for_pipe,
        .mock_implementation = _narmock_mock_implementation_function_for_pipe,
        .disable_mock = _narmock_disable_mock_function_for_pipe,
        .reset = _narmock_reset_function_for_pipe,
        .assert_completed = _narmock_assert_completed_function_for_pipe
    },
    .mode = 0,
    .instances = {
        .head_p = NULL,
        .tail_p = NULL
    }
};

int __wrap_pipe(int __pipedes[2])
{
    struct _narmock_instance_type_for_pipe *instance_p;
    int return_value;

    switch (_narmock_state_for_pipe.mode) {

    case 1:
        instance_p = _narmock_state_for_pipe.instances.head_p;

        if (instance_p == NULL) {
            FAIL();
            while (1);
        }

        if (!instance_p->ignore___pipedes_in) {
            ASSERT_EQ(__pipedes, instance_p->params.__pipedes);
        }

        if (instance_p->__pipedes_out.buf_p != NULL) {
            memcpy((void *)__pipedes, instance_p->__pipedes_out.buf_p, instance_p->__pipedes_out.size);
            free(instance_p->__pipedes_out.buf_p);
        }

        if (instance_p->__pipedes_in.buf_p != NULL) {
            ASSERT_MEMORY(__pipedes,
                          instance_p->__pipedes_in.buf_p,
                          instance_p->__pipedes_in.size);
            free(instance_p->__pipedes_in.buf_p);
        }

        _narmock_state_for_pipe.instances.head_p = instance_p->next_p;
        errno = instance_p->errno_value;
        return_value = instance_p->params.return_value;
        free(instance_p);
        break;

    case 2:
        return_value =
        _narmock_state_for_pipe.implementation(__pipedes);
        break;

    case 3:
        FAIL();
        while (1);
        break;

    default:
        return_value =
        __real_pipe(__pipedes);
        break;
    }

    return return_value;
}

static const _narmock_state_type_for_pipe *_narmock_mock_once_function_for_pipe(int return_value)
{
    struct _narmock_instance_type_for_pipe *instance_p;

    _narmock_state_for_pipe.mode = 1;
    instance_p = xmalloc(sizeof(*instance_p));
    instance_p->__pipedes_out.buf_p = NULL;
    instance_p->__pipedes_out.size = 0;
    instance_p->__pipedes_in.buf_p = NULL;
    instance_p->__pipedes_in.size = 0;
    instance_p->params.__pipedes = NULL;
    instance_p->ignore___pipedes_in = true;
    instance_p->params.return_value = return_value;
    instance_p->errno_value = 0;
    instance_p->next_p = NULL;

    if (_narmock_state_for_pipe.instances.head_p == NULL) {
        _narmock_state_for_pipe.instances.head_p = instance_p;
    } else {
        _narmock_state_for_pipe.instances.tail_p->next_p = instance_p;
    }

    _narmock_state_for_pipe.instances.tail_p = instance_p;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_set_errno_function_for_pipe(int errno_value)
{
    if (_narmock_state_for_pipe.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_pipe.instances.tail_p->errno_value = errno_value;

    return &_narmock_state_for_pipe.public;
}


static const _narmock_state_type_for_pipe *_narmock_set___pipedes_in_function_for_pipe(const void *buf_p, size_t size)
{
    if (_narmock_state_for_pipe.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_pipe.instances.tail_p->__pipedes_in.buf_p = xmalloc(size);
    _narmock_state_for_pipe.instances.tail_p->__pipedes_in.size = size;
    memcpy(_narmock_state_for_pipe.instances.tail_p->__pipedes_in.buf_p, buf_p, size);

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_set___pipedes_in_pointer_function_for_pipe(int __pipedes[2])
{
    if (_narmock_state_for_pipe.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_pipe.instances.tail_p->ignore___pipedes_in = false;
    _narmock_state_for_pipe.instances.tail_p->params.__pipedes = __pipedes;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_set___pipedes_out_function_for_pipe(const void *buf_p, size_t size)
{
    if (_narmock_state_for_pipe.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_pipe.instances.tail_p->__pipedes_out.buf_p = xmalloc(size);
    _narmock_state_for_pipe.instances.tail_p->__pipedes_out.size = size;
    memcpy(_narmock_state_for_pipe.instances.tail_p->__pipedes_out.buf_p, buf_p, size);

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_mock_none_function_for_pipe(void)
{
    _narmock_state_for_pipe.mode = 3;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_mock_implementation_function_for_pipe(int (*implementation)(int __pipedes[2]))
{
    _narmock_state_for_pipe.mode = 2;
    _narmock_state_for_pipe.implementation = implementation;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_disable_mock_function_for_pipe(void)
{
    _narmock_state_for_pipe.mode = 0;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_reset_function_for_pipe(void)
{
    _narmock_state_for_pipe.mode = 0;
    _narmock_state_for_pipe.instances.head_p = NULL;
    _narmock_state_for_pipe.instances.tail_p = NULL;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_assert_completed_function_for_pipe(void)
{
    ASSERT_EQ(_narmock_state_for_pipe.instances.head_p, NULL);

    return &_narmock_state_for_pipe.public;
}

const _narmock_state_type_for_pipe *_narmock_get_mock_for_pipe(const void *function)
{
    (void)function;

    return &_narmock_state_for_pipe.public;
}

// NARMOCK_IMPLEMENTATION read

ssize_t __real_read(int __fd, void *__buf, size_t __nbytes);

typedef struct _narmock_params_type_for_read _narmock_params_type_for_read;

struct _narmock_params_type_for_read
{
    int __fd;
    void *__buf;
    size_t __nbytes;
    ssize_t return_value;
};

typedef struct _narmock_instance_type_for_read _narmock_instance_type_for_read;

struct _narmock_instance_type_for_read
{
    _narmock_params_type_for_read params;
    bool ignore___fd_in;
    bool ignore___buf_in;
    _narmock_set_param __buf_in;
    _narmock_set_param __buf_out;
    bool ignore___nbytes_in;
    int errno_value;
    _narmock_instance_type_for_read *next_p;
};

typedef struct _narmock_instances_type_for_read _narmock_instances_type_for_read;

struct _narmock_instances_type_for_read {
    _narmock_instance_type_for_read *head_p;
    _narmock_instance_type_for_read *tail_p;
};

typedef struct _narmock_private_state_type_for_read _narmock_private_state_type_for_read;

struct _narmock_private_state_type_for_read
{
    _narmock_state_type_for_read public;
    int mode;
    _narmock_instances_type_for_read instances;
    ssize_t (*implementation)(int __fd, void *__buf, size_t __nbytes);
};

static const _narmock_state_type_for_read *_narmock_mock_once_function_for_read(int __fd, size_t __nbytes, ssize_t return_value);
static const _narmock_state_type_for_read *_narmock_set_errno_function_for_read(int errno_value);
static const _narmock_state_type_for_read *_narmock_ignore___fd_in_function_for_read(void);
static const _narmock_state_type_for_read *_narmock_ignore___nbytes_in_function_for_read(void);
static const _narmock_state_type_for_read *_narmock_set___buf_in_function_for_read(const void *buf_p, size_t size);
static const _narmock_state_type_for_read *_narmock_set___buf_in_pointer_function_for_read(void *__buf);
static const _narmock_state_type_for_read *_narmock_set___buf_out_function_for_read(const void *buf_p, size_t size);
static const _narmock_state_type_for_read *_narmock_mock_none_function_for_read(void);
static const _narmock_state_type_for_read *_narmock_mock_implementation_function_for_read(ssize_t (*implementation)(int __fd, void *__buf, size_t __nbytes));
static const _narmock_state_type_for_read *_narmock_disable_mock_function_for_read(void);
static const _narmock_state_type_for_read *_narmock_reset_function_for_read(void);
static const _narmock_state_type_for_read *_narmock_assert_completed_function_for_read(void);

static _narmock_private_state_type_for_read _narmock_state_for_read =
{
    .public = {
        .mock_once = _narmock_mock_once_function_for_read,
        .set_errno = _narmock_set_errno_function_for_read,
        .ignore___fd_in = _narmock_ignore___fd_in_function_for_read,
        .ignore___nbytes_in = _narmock_ignore___nbytes_in_function_for_read,
        .set___buf_in = _narmock_set___buf_in_function_for_read,
        .set___buf_in_pointer = _narmock_set___buf_in_pointer_function_for_read,
        .set___buf_out = _narmock_set___buf_out_function_for_read,
        .mock_none = _narmock_mock_none_function_for_read,
        .mock_implementation = _narmock_mock_implementation_function_for_read,
        .disable_mock = _narmock_disable_mock_function_for_read,
        .reset = _narmock_reset_function_for_read,
        .assert_completed = _narmock_assert_completed_function_for_read
    },
    .mode = 0,
    .instances = {
        .head_p = NULL,
        .tail_p = NULL
    }
};

ssize_t __wrap_read(int __fd, void *__buf, size_t __nbytes)
{
    struct _narmock_instance_type_for_read *instance_p;
    ssize_t return_value;

    switch (_narmock_state_for_read.mode) {

    case 1:
        instance_p = _narmock_state_for_read.instances.head_p;

        if (instance_p == NULL) {
            FAIL();
            while (1);
        }

        if (!instance_p->ignore___fd_in) {
            ASSERT_EQ(__fd, instance_p->params.__fd);
        }
        if (!instance_p->ignore___buf_in) {
            ASSERT_EQ(__buf, instance_p->params.__buf);
        }
        if (!instance_p->ignore___nbytes_in) {
            ASSERT_EQ(__nbytes, instance_p->params.__nbytes);
        }

        if (instance_p->__buf_out.buf_p != NULL) {
            memcpy((void *)__buf, instance_p->__buf_out.buf_p, instance_p->__buf_out.size);
            free(instance_p->__buf_out.buf_p);
        }

        if (instance_p->__buf_in.buf_p != NULL) {
            ASSERT_MEMORY(__buf,
                          instance_p->__buf_in.buf_p,
                          instance_p->__buf_in.size);
            free(instance_p->__buf_in.buf_p);
        }

        _narmock_state_for_read.instances.head_p = instance_p->next_p;
        errno = instance_p->errno_value;
        return_value = instance_p->params.return_value;
        free(instance_p);
        break;

    case 2:
        return_value =
        _narmock_state_for_read.implementation(__fd, __buf, __nbytes);
        break;

    case 3:
        FAIL();
        while (1);
        break;

    default:
        return_value =
        __real_read(__fd, __buf, __nbytes);
        break;
    }

    return return_value;
}

static const _narmock_state_type_for_read *_narmock_mock_once_function_for_read(int __fd, size_t __nbytes, ssize_t return_value)
{
    struct _narmock_instance_type_for_read *instance_p;

    _narmock_state_for_read.mode = 1;
    instance_p = xmalloc(sizeof(*instance_p));
    instance_p->__buf_out.buf_p = NULL;
    instance_p->__buf_out.size = 0;
    instance_p->__buf_in.buf_p = NULL;
    instance_p->__buf_in.size = 0;
    instance_p->params.__buf = NULL;
    instance_p->ignore___buf_in = true;
    instance_p->params.__fd = __fd;
    instance_p->ignore___fd_in = false;
    instance_p->params.__nbytes = __nbytes;
    instance_p->ignore___nbytes_in = false;
    instance_p->params.return_value = return_value;
    instance_p->errno_value = 0;
    instance_p->next_p = NULL;

    if (_narmock_state_for_read.instances.head_p == NULL) {
        _narmock_state_for_read.instances.head_p = instance_p;
    } else {
        _narmock_state_for_read.instances.tail_p->next_p = instance_p;
    }

    _narmock_state_for_read.instances.tail_p = instance_p;

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_set_errno_function_for_read(int errno_value)
{
    if (_narmock_state_for_read.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_read.instances.tail_p->errno_value = errno_value;

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_ignore___fd_in_function_for_read(void)
{
    if (_narmock_state_for_read.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_read.instances.tail_p->ignore___fd_in = true;

    return &_narmock_state_for_read.public;
}
static const _narmock_state_type_for_read *_narmock_ignore___nbytes_in_function_for_read(void)
{
    if (_narmock_state_for_read.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_read.instances.tail_p->ignore___nbytes_in = true;

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_set___buf_in_function_for_read(const void *buf_p, size_t size)
{
    if (_narmock_state_for_read.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_read.instances.tail_p->__buf_in.buf_p = xmalloc(size);
    _narmock_state_for_read.instances.tail_p->__buf_in.size = size;
    memcpy(_narmock_state_for_read.instances.tail_p->__buf_in.buf_p, buf_p, size);

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_set___buf_in_pointer_function_for_read(void *__buf)
{
    if (_narmock_state_for_read.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_read.instances.tail_p->ignore___buf_in = false;
    _narmock_state_for_read.instances.tail_p->params.__buf = __buf;

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_set___buf_out_function_for_read(const void *buf_p, size_t size)
{
    if (_narmock_state_for_read.instances.tail_p == NULL) {
        printf("No mock instance.\n");
        exit(1);
    }

    _narmock_state_for_read.instances.tail_p->__buf_out.buf_p = xmalloc(size);
    _narmock_state_for_read.instances.tail_p->__buf_out.size = size;
    memcpy(_narmock_state_for_read.instances.tail_p->__buf_out.buf_p, buf_p, size);

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_mock_none_function_for_read(void)
{
    _narmock_state_for_read.mode = 3;

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_mock_implementation_function_for_read(ssize_t (*implementation)(int __fd, void *__buf, size_t __nbytes))
{
    _narmock_state_for_read.mode = 2;
    _narmock_state_for_read.implementation = implementation;

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_disable_mock_function_for_read(void)
{
    _narmock_state_for_read.mode = 0;

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_reset_function_for_read(void)
{
    _narmock_state_for_read.mode = 0;
    _narmock_state_for_read.instances.head_p = NULL;
    _narmock_state_for_read.instances.tail_p = NULL;

    return &_narmock_state_for_read.public;
}

static const _narmock_state_type_for_read *_narmock_assert_completed_function_for_read(void)
{
    ASSERT_EQ(_narmock_state_for_read.instances.head_p, NULL);

    return &_narmock_state_for_read.public;
}

const _narmock_state_type_for_read *_narmock_get_mock_for_read(const void *function)
{
    (void)function;

    return &_narmock_state_for_read.public;
}
