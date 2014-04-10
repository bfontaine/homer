#ifndef _UTILS_H
#define _UTILS_H 1

#define _STR(x) #x
#define STR(x) _STR(x)

#include <sys/types.h>

/**
 * Write a PID into a file.
 * - pathname: the file path. It'll be created if it doesn't exist, and
 *   truncated if it does.
 * - pid: the PID to write
 **/
int write_pid(char *pathname, pid_t pid);

/**
 * Open a file for logging purposes. The file is created if it doesn't exist,
 * and opened in append mode. A shared lock is put on it, and the file
 * descriptor is returned.
 * - pathname: the file path
 **/
int open_log(char *pathname);

#endif
