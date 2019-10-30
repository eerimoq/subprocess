/*
Mocks source file

Generated with Narmock v0.2.12 (https://github.com/vberlier/narmock)
Do not edit manually
*/

#include <errno.h>
#include <stddef.h>

#include "__mocks__.h"

void narmock_reset_all_mocks(void)
{
    MOCK(close)->reset();
    MOCK(fork)->reset();
    MOCK(pipe)->reset();
}

// NARMOCK_IMPLEMENTATION close

int __real_close(int arg1);

typedef struct _narmock_private_state_type_for_close _narmock_private_state_type_for_close;

struct _narmock_private_state_type_for_close
{
    _narmock_state_type_for_close public;

    int mode;
    int return_value;
    int (*implementation)(int arg1);
    int errno_value;
    _narmock_params_type_for_close last_call;
};

static const _narmock_state_type_for_close *_narmock_mock_return_function_for_close(int return_value);
static const _narmock_state_type_for_close *_narmock_mock_implementation_function_for_close(int (*implementation)(int arg1));
static const _narmock_state_type_for_close *_narmock_mock_errno_function_for_close(int errno_value);
static const _narmock_state_type_for_close *_narmock_disable_mock_function_for_close(void);
static const _narmock_state_type_for_close *_narmock_reset_function_for_close(void);

static _narmock_private_state_type_for_close _narmock_state_for_close =
{
    .public = {
        .mock_return = _narmock_mock_return_function_for_close,
        .mock_implementation = _narmock_mock_implementation_function_for_close,
        .mock_errno = _narmock_mock_errno_function_for_close,
        .disable_mock = _narmock_disable_mock_function_for_close,
        .reset = _narmock_reset_function_for_close,
        .call_count = 0,
        .last_call = NULL
    },

    .mode = 0,
    .errno_value = 0
};

int __wrap_close(int arg1)
{
    int return_value;

    switch (_narmock_state_for_close.mode)
    {
        case 1:
            return_value =
            _narmock_state_for_close.return_value;
            break;
        case 2:
            return_value =
            _narmock_state_for_close.implementation(arg1);
            break;
        default:
            return_value =
            __real_close(arg1);
            break;
    }

    if (_narmock_state_for_close.errno_value != 0)
    {
        errno = _narmock_state_for_close.errno_value;
    }

    _narmock_state_for_close.public.call_count++;

    _narmock_params_type_for_close last_call = { arg1, return_value, errno };

    _narmock_state_for_close.last_call = last_call;
    _narmock_state_for_close.public.last_call = &_narmock_state_for_close.last_call;

    return return_value;
}

static const _narmock_state_type_for_close *_narmock_mock_return_function_for_close(int return_value)
{
    _narmock_state_for_close.mode = 1;
    _narmock_state_for_close.return_value = return_value;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_mock_implementation_function_for_close(int (*implementation)(int arg1))
{
    _narmock_state_for_close.mode = 2;
    _narmock_state_for_close.implementation = implementation;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_mock_errno_function_for_close(int errno_value)
{
    _narmock_state_for_close.errno_value = errno_value;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_disable_mock_function_for_close(void)
{
    _narmock_state_for_close.mode = 0;
    _narmock_state_for_close.errno_value = 0;

    return &_narmock_state_for_close.public;
}

static const _narmock_state_type_for_close *_narmock_reset_function_for_close(void)
{
    _narmock_state_for_close.mode = 0;
    _narmock_state_for_close.errno_value = 0;
    _narmock_state_for_close.public.call_count = 0;
    _narmock_state_for_close.public.last_call = NULL;

    return &_narmock_state_for_close.public;
}

const _narmock_state_type_for_close *_narmock_get_mock_for_close(const void *function)
{
    (void)function;

    return &_narmock_state_for_close.public;
}

// NARMOCK_IMPLEMENTATION fork

__pid_t __real_fork(void);

typedef struct _narmock_private_state_type_for_fork _narmock_private_state_type_for_fork;

struct _narmock_private_state_type_for_fork
{
    _narmock_state_type_for_fork public;

    int mode;
    __pid_t return_value;
    __pid_t (*implementation)(void);
    int errno_value;
    _narmock_params_type_for_fork last_call;
};

static const _narmock_state_type_for_fork *_narmock_mock_return_function_for_fork(__pid_t return_value);
static const _narmock_state_type_for_fork *_narmock_mock_implementation_function_for_fork(__pid_t (*implementation)(void));
static const _narmock_state_type_for_fork *_narmock_mock_errno_function_for_fork(int errno_value);
static const _narmock_state_type_for_fork *_narmock_disable_mock_function_for_fork(void);
static const _narmock_state_type_for_fork *_narmock_reset_function_for_fork(void);

static _narmock_private_state_type_for_fork _narmock_state_for_fork =
{
    .public = {
        .mock_return = _narmock_mock_return_function_for_fork,
        .mock_implementation = _narmock_mock_implementation_function_for_fork,
        .mock_errno = _narmock_mock_errno_function_for_fork,
        .disable_mock = _narmock_disable_mock_function_for_fork,
        .reset = _narmock_reset_function_for_fork,
        .call_count = 0,
        .last_call = NULL
    },

    .mode = 0,
    .errno_value = 0
};

__pid_t __wrap_fork(void)
{
    __pid_t return_value;

    switch (_narmock_state_for_fork.mode)
    {
        case 1:
            return_value =
            _narmock_state_for_fork.return_value;
            break;
        case 2:
            return_value =
            _narmock_state_for_fork.implementation();
            break;
        default:
            return_value =
            __real_fork();
            break;
    }

    if (_narmock_state_for_fork.errno_value != 0)
    {
        errno = _narmock_state_for_fork.errno_value;
    }

    _narmock_state_for_fork.public.call_count++;

    _narmock_params_type_for_fork last_call = { return_value, errno };

    _narmock_state_for_fork.last_call = last_call;
    _narmock_state_for_fork.public.last_call = &_narmock_state_for_fork.last_call;

    return return_value;
}

static const _narmock_state_type_for_fork *_narmock_mock_return_function_for_fork(__pid_t return_value)
{
    _narmock_state_for_fork.mode = 1;
    _narmock_state_for_fork.return_value = return_value;

    return &_narmock_state_for_fork.public;
}

static const _narmock_state_type_for_fork *_narmock_mock_implementation_function_for_fork(__pid_t (*implementation)(void))
{
    _narmock_state_for_fork.mode = 2;
    _narmock_state_for_fork.implementation = implementation;

    return &_narmock_state_for_fork.public;
}

static const _narmock_state_type_for_fork *_narmock_mock_errno_function_for_fork(int errno_value)
{
    _narmock_state_for_fork.errno_value = errno_value;

    return &_narmock_state_for_fork.public;
}

static const _narmock_state_type_for_fork *_narmock_disable_mock_function_for_fork(void)
{
    _narmock_state_for_fork.mode = 0;
    _narmock_state_for_fork.errno_value = 0;

    return &_narmock_state_for_fork.public;
}

static const _narmock_state_type_for_fork *_narmock_reset_function_for_fork(void)
{
    _narmock_state_for_fork.mode = 0;
    _narmock_state_for_fork.errno_value = 0;
    _narmock_state_for_fork.public.call_count = 0;
    _narmock_state_for_fork.public.last_call = NULL;

    return &_narmock_state_for_fork.public;
}

const _narmock_state_type_for_fork *_narmock_get_mock_for_fork(const void *function)
{
    (void)function;

    return &_narmock_state_for_fork.public;
}

// NARMOCK_IMPLEMENTATION pipe

int __real_pipe(int arg1[2]);

typedef struct _narmock_private_state_type_for_pipe _narmock_private_state_type_for_pipe;

struct _narmock_private_state_type_for_pipe
{
    _narmock_state_type_for_pipe public;

    int mode;
    int return_value;
    int (*implementation)(int arg1[2]);
    int errno_value;
    _narmock_params_type_for_pipe last_call;
};

static const _narmock_state_type_for_pipe *_narmock_mock_return_function_for_pipe(int return_value);
static const _narmock_state_type_for_pipe *_narmock_mock_implementation_function_for_pipe(int (*implementation)(int arg1[2]));
static const _narmock_state_type_for_pipe *_narmock_mock_errno_function_for_pipe(int errno_value);
static const _narmock_state_type_for_pipe *_narmock_disable_mock_function_for_pipe(void);
static const _narmock_state_type_for_pipe *_narmock_reset_function_for_pipe(void);

static _narmock_private_state_type_for_pipe _narmock_state_for_pipe =
{
    .public = {
        .mock_return = _narmock_mock_return_function_for_pipe,
        .mock_implementation = _narmock_mock_implementation_function_for_pipe,
        .mock_errno = _narmock_mock_errno_function_for_pipe,
        .disable_mock = _narmock_disable_mock_function_for_pipe,
        .reset = _narmock_reset_function_for_pipe,
        .call_count = 0,
        .last_call = NULL
    },

    .mode = 0,
    .errno_value = 0
};

int __wrap_pipe(int arg1[2])
{
    int return_value;

    switch (_narmock_state_for_pipe.mode)
    {
        case 1:
            return_value =
            _narmock_state_for_pipe.return_value;
            break;
        case 2:
            return_value =
            _narmock_state_for_pipe.implementation(arg1);
            break;
        default:
            return_value =
            __real_pipe(arg1);
            break;
    }

    if (_narmock_state_for_pipe.errno_value != 0)
    {
        errno = _narmock_state_for_pipe.errno_value;
    }

    _narmock_state_for_pipe.public.call_count++;

    _narmock_params_type_for_pipe last_call = { arg1, return_value, errno };

    _narmock_state_for_pipe.last_call = last_call;
    _narmock_state_for_pipe.public.last_call = &_narmock_state_for_pipe.last_call;

    return return_value;
}

static const _narmock_state_type_for_pipe *_narmock_mock_return_function_for_pipe(int return_value)
{
    _narmock_state_for_pipe.mode = 1;
    _narmock_state_for_pipe.return_value = return_value;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_mock_implementation_function_for_pipe(int (*implementation)(int arg1[2]))
{
    _narmock_state_for_pipe.mode = 2;
    _narmock_state_for_pipe.implementation = implementation;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_mock_errno_function_for_pipe(int errno_value)
{
    _narmock_state_for_pipe.errno_value = errno_value;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_disable_mock_function_for_pipe(void)
{
    _narmock_state_for_pipe.mode = 0;
    _narmock_state_for_pipe.errno_value = 0;

    return &_narmock_state_for_pipe.public;
}

static const _narmock_state_type_for_pipe *_narmock_reset_function_for_pipe(void)
{
    _narmock_state_for_pipe.mode = 0;
    _narmock_state_for_pipe.errno_value = 0;
    _narmock_state_for_pipe.public.call_count = 0;
    _narmock_state_for_pipe.public.last_call = NULL;

    return &_narmock_state_for_pipe.public;
}

const _narmock_state_type_for_pipe *_narmock_get_mock_for_pipe(const void *function)
{
    (void)function;

    return &_narmock_state_for_pipe.public;
}
