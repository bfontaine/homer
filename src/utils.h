#ifndef _UTILS_H
#define _UTILS_H 1

#include <sys/types.h>

/* maximum number of bytes needed to represent a pid in ASCII. E.g.
* 74123 -> 5 chars. This can be computed with something like:
*   (int)log10(pow(2, 8*sizeof(pid))),
* but with 32 bytes we can represent numbers up to 2^102, which is
* sufficient here.
**/
enum {
        PID_WIDTH = 33
};

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

#endif /* _UTILS_H */
