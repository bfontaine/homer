#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <math.h>

#include "utils.h"

int write_pid(char *pathname, pid_t pid) {

        int fd,
            ret = 0,
            chars_count;
        char pid_str[PID_WIDTH+1];

        fd = open(pathname, O_WRONLY|O_CREAT|O_TRUNC, 0644);

        if (fd < 0) {
                perror("open");
                return -1;
        }

        if (flock(fd, LOCK_EX) == -1) {
                perror("flock");
                ret = -1;
                goto CLOSE_AND_RETURN;
        }

        chars_count = snprintf(pid_str, PID_WIDTH+1, "%d", pid);
        if (chars_count < 0) {
                perror("snprintf");
                ret = -1;
                goto CLOSE_AND_RETURN;
        }

        if (write(fd, pid_str, chars_count+1) < 0) {
                perror("write");
                ret = -1;
                goto CLOSE_AND_RETURN;
        }

CLOSE_AND_RETURN:
        if (close(fd) == -1) {
                perror("close");
                return -1;
        }
        return ret;
}

int open_log(char *pathname) {

        int fd;

        fd = open(pathname, O_WRONLY|O_CREAT|O_APPEND, 0644);

        if (fd < 0) {
                perror("open");
                return -1;
        }

        if (flock(fd, LOCK_SH) == -1) {
                perror("flock");
                close(fd);
                return -1;
        }

        return fd;
}
