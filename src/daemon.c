#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "daemon.h"

pid_t daemonize(char *const cmd[]) {

        pid_t child1, child2;

        int child1_st = 0;
        int pipefd[2];

        if (pipe(pipefd) == -1) {
                perror("pipe");
                return -1;
        }

        child1 = fork();

        if (child1 == -1) {
                perror("fork");
                return -1;
        }

        if (child1 > 0) {
                /* parent processus */
                /* get the grandchild PID */
                close(pipefd[1]);
                if (read(pipefd[0], &child2, sizeof(child2)) == -1) {
                        perror("read");
                        return -1;
                }

                wait(&child1_st);
                close(pipefd[0]);

                if (!WIFEXITED(child1_st) || WEXITSTATUS(child1_st) != 0) {
                        return -1;
                }

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
                        /* first, communicate the grandchild PID to their
                         * grandparent. */
                        close(pipefd[0]);
                        if (write(pipefd[1], &child2, sizeof(child2)) == -1) {
                                perror("write");
                                exit(EXIT_FAILURE);
                        }

                        /* wait to be sure the parent reads the child PID */
                        sleep(1);
                        close(pipefd[1]);

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
