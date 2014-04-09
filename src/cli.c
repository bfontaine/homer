#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cli.h"
#include "daemon.h"

int print_help(char *exe) {
        printf("Usage:\n\t%s [-h] <command>\n", exe);
        return 0;
}

int main(int argc, char **argv) {

        pid_t cmd_pid;
        int optch;
        extern int opterr;

        opterr = 1;

        while ((optch = getopt(argc, argv, "h")) != -1) {
                /* we'll eventually extend this statement to include more
                 * options. */
                switch (optch) {
                case 'h':
                        return print_help(argv[0]);
                }
        }

        /* No arguments */
        if (optind == argc) {
                return print_help(argv[0]);
        }

        cmd_pid = daemonize(argv + optind);

        if (cmd_pid == 0) {
                /* cannot get the grandchild PID. */
                puts("Successfully daemonized the command.");
                exit(EXIT_SUCCESS);
        }

        if (cmd_pid < 0) {
                puts("Got an error.");
                exit(EXIT_FAILURE);
        }

        printf("Successfully daemonized the command with PID %d.\n", cmd_pid);

        return 0;
}
