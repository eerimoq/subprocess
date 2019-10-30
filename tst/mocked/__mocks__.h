/*
Mocks header file

Generated with Narmock v0.2.12 (https://github.com/vberlier/narmock)
Do not edit manually
*/

#ifndef MOCKS_H
#define MOCKS_H

#include <unistd.h>

#ifndef MOCK
#define MOCK(function) (_narmock_get_mock_for_##function((void *)&function))
#endif

#ifndef _NARMOCK_RESET_ALL_MOCKS
#define _NARMOCK_RESET_ALL_MOCKS 1
void narmock_reset_all_mocks(void);
#endif

// NARMOCK_DECLARATION close
// NARMOCK_LINKER_FLAGS -Wl,--wrap=close

typedef struct _narmock_state_type_for_close _narmock_state_type_for_close;
typedef struct _narmock_params_type_for_close _narmock_params_type_for_close;

struct _narmock_state_type_for_close
{
    const _narmock_state_type_for_close *(*mock_return)(int return_value);
    const _narmock_state_type_for_close *(*mock_implementation)(int (*implementation)(int arg1));
    const _narmock_state_type_for_close *(*mock_errno)(int errno_value);
    const _narmock_state_type_for_close *(*disable_mock)(void);
    const _narmock_state_type_for_close *(*reset)(void);
    int call_count;
    const _narmock_params_type_for_close *last_call;
};

struct _narmock_params_type_for_close
{
    int arg1;
    int return_value;
    int errsv;
};

const _narmock_state_type_for_close *_narmock_get_mock_for_close(const void *function);

// NARMOCK_DECLARATION fork
// NARMOCK_LINKER_FLAGS -Wl,--wrap=fork

typedef struct _narmock_state_type_for_fork _narmock_state_type_for_fork;
typedef struct _narmock_params_type_for_fork _narmock_params_type_for_fork;

struct _narmock_state_type_for_fork
{
    const _narmock_state_type_for_fork *(*mock_return)(__pid_t return_value);
    const _narmock_state_type_for_fork *(*mock_implementation)(__pid_t (*implementation)(void));
    const _narmock_state_type_for_fork *(*mock_errno)(int errno_value);
    const _narmock_state_type_for_fork *(*disable_mock)(void);
    const _narmock_state_type_for_fork *(*reset)(void);
    int call_count;
    const _narmock_params_type_for_fork *last_call;
};

struct _narmock_params_type_for_fork
{
    __pid_t return_value;
    int errsv;
};

const _narmock_state_type_for_fork *_narmock_get_mock_for_fork(const void *function);

// NARMOCK_DECLARATION pipe
// NARMOCK_LINKER_FLAGS -Wl,--wrap=pipe

typedef struct _narmock_state_type_for_pipe _narmock_state_type_for_pipe;
typedef struct _narmock_params_type_for_pipe _narmock_params_type_for_pipe;

struct _narmock_state_type_for_pipe
{
    const _narmock_state_type_for_pipe *(*mock_return)(int return_value);
    const _narmock_state_type_for_pipe *(*mock_implementation)(int (*implementation)(int arg1[2]));
    const _narmock_state_type_for_pipe *(*mock_errno)(int errno_value);
    const _narmock_state_type_for_pipe *(*disable_mock)(void);
    const _narmock_state_type_for_pipe *(*reset)(void);
    int call_count;
    const _narmock_params_type_for_pipe *last_call;
};

struct _narmock_params_type_for_pipe
{
    int *arg1;
    int return_value;
    int errsv;
};

const _narmock_state_type_for_pipe *_narmock_get_mock_for_pipe(const void *function);

#endif
