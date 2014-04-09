#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "daemon.h"

pid_t daemonize(char *const cmd[]) {

        pid_t child1 = fork(),
              child2 = 0;

        int pipefd[2];

        if (pipe(pipefd) == -1) {
                perror("pipe");
                return -1;
        }

        if (child1 == -1) {
                perror("fork");
                return -1;
        }

        if (child1 > 0) {
                /* parent processus */
                /* first, read the grandchild PID. */
                close(pipefd[1]);
                if (read(pipefd[0], &child2, sizeof(child2)) == -1) {
                        perror("read");
                        return -1;
                }
                close(pipefd[0]);
                wait(NULL);

                /* then return it to the caller. */
                return child2;

        } else {
                /* child processus */
                child2 = fork();

                if (child2 == -1) {
                        perror("fork");
                        exit(EXIT_FAILURE);
                }

                if (child2 > 0) {
                        /* child-parent processus */
                        /* first, send the grandchild PID to its grandparent.
                         */
                        close(pipefd[0]);
                        if (write(pipefd[1], &child2, sizeof(child2)) == -1) {
                                perror("write");
                                exit(EXIT_FAILURE);
                        }
                        close(pipefd[1]);

                        /* then exit */
                        exit(EXIT_SUCCESS);

                } else {
                        /* grandchild process */
                        if (execvp(cmd[0], cmd) == -1) {
                                perror("execlp");
                                exit(EXIT_FAILURE);
                        }
                        /* this will never happen but the compiler gives a
                         * warning if we don't put it. */
                        return -1;
                }
        }

}
