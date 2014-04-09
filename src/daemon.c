#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "daemon.h"

int daemonize(char *const cmd[], char verbose) {

        pid_t child1 = fork(),
              child2;

        int child1_st = 0;

        if (child1 == -1) {
                perror("fork");
                return -1;
        }

        if (child1 > 0) {
                /* parent processus */
                wait(&child1_st);

                if (!WIFEXITED(child1_st) || WEXITSTATUS(child1_st) != 0) {
                        return -1;
                }

                return 0;

        } else {
                /* child processus */
                child2 = fork();

                if (child2 == -1) {
                        perror("fork");
                        exit(EXIT_FAILURE);
                }

                if (child2 > 0) {
                        /* child-parent processus */
                        if (verbose) {
                                printf("Successfully launched "
                                       "command with PID %d\n", child2);
                        }

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
