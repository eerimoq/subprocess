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

struct _narmock_state_type_for_close
{
    const _narmock_state_type_for_close *(*mock_once)(int __fd, int return_value);
    const _narmock_state_type_for_close *(*set_errno)(int errno_value);
    const _narmock_state_type_for_close *(*ignore___fd_in)(void);
    const _narmock_state_type_for_close *(*mock_none)(void);
    const _narmock_state_type_for_close *(*mock_implementation)(int (*implementation)(int __fd));
    const _narmock_state_type_for_close *(*disable_mock)(void);
    const _narmock_state_type_for_close *(*reset)(void);
    const _narmock_state_type_for_close *(*assert_completed)(void);
};

const _narmock_state_type_for_close *_narmock_get_mock_for_close(const void *function);

// NARMOCK_DECLARATION fork
// NARMOCK_LINKER_FLAGS -Wl,--wrap=fork

typedef struct _narmock_state_type_for_fork _narmock_state_type_for_fork;

struct _narmock_state_type_for_fork
{
    const _narmock_state_type_for_fork *(*mock_once)(__pid_t return_value);
    const _narmock_state_type_for_fork *(*set_errno)(int errno_value);
    const _narmock_state_type_for_fork *(*mock_none)(void);
    const _narmock_state_type_for_fork *(*mock_implementation)(__pid_t (*implementation)(void));
    const _narmock_state_type_for_fork *(*disable_mock)(void);
    const _narmock_state_type_for_fork *(*reset)(void);
    const _narmock_state_type_for_fork *(*assert_completed)(void);
};

const _narmock_state_type_for_fork *_narmock_get_mock_for_fork(const void *function);

// NARMOCK_DECLARATION pipe
// NARMOCK_LINKER_FLAGS -Wl,--wrap=pipe

typedef struct _narmock_state_type_for_pipe _narmock_state_type_for_pipe;

struct _narmock_state_type_for_pipe
{
    const _narmock_state_type_for_pipe *(*mock_once)(int return_value);
    const _narmock_state_type_for_pipe *(*set_errno)(int errno_value);
    const _narmock_state_type_for_pipe *(*set___pipedes_in)(const void *buf_p, size_t size);
    const _narmock_state_type_for_pipe *(*set___pipedes_in_pointer)(int __pipedes[2]);
    const _narmock_state_type_for_pipe *(*set___pipedes_out)(const void *buf_p, size_t size);
    const _narmock_state_type_for_pipe *(*mock_none)(void);
    const _narmock_state_type_for_pipe *(*mock_implementation)(int (*implementation)(int __pipedes[2]));
    const _narmock_state_type_for_pipe *(*disable_mock)(void);
    const _narmock_state_type_for_pipe *(*reset)(void);
    const _narmock_state_type_for_pipe *(*assert_completed)(void);
};

const _narmock_state_type_for_pipe *_narmock_get_mock_for_pipe(const void *function);

#endif
