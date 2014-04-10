#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "daemon.h"
#include "utils.h"
#include "version.h"

#include "cli.h"

int print_help(char *exe) {
        printf("Usage:\n"
               "\t%1$s [-q] [-p <file>] <command>\n"
               "\n"
               "Options:\n"
               "\t-h: show this help and exit\n"
               "\t-p <file>: print the PID in a file\n"
               "\t-q: quiet mode, don't print normal output\n"
               "\t-v: print the version and exit\n"
               "\n"
               "Example:\n"
               "\t%1$s mylongprocess --an-option arg1 arg2\n", exe);
        return 0;
}

int print_version(void) {
        printf("homer(1) - version %s\n", HOMER_VERSION);
        return 0;
}

int main(int argc, char **argv) {

        pid_t cmd_pid;
        int optch;
        extern int opterr;

        char verbose_flag = 1;
        char *pidfile = NULL;

        opterr = 1;

        while ((optch = getopt(argc, argv, "hp:qv")) != -1) {
                /* we'll eventually extend this statement to include more
                 * options. */
                switch (optch) {
                case 'h':
                        return print_help(argv[0]);
                case 'p':
                        pidfile = optarg;
                        break;
                case 'q':
                        verbose_flag = 0;
                        break;
                case 'v':
                        return print_version();
                }
        }

        /* No arguments */
        if (optind == argc) {
                return print_help(argv[0]);
        }

        cmd_pid = daemonize(argv + optind);

        if (cmd_pid < 0) {
                puts("Got an error.");
                return EXIT_FAILURE;
        }

        if (verbose_flag) {
                printf("Successfully launched command"
                       " with PID %d.\n", cmd_pid);
        }

        if (pidfile) {
                if (write_pid(pidfile, cmd_pid) < 0) {
                        return EXIT_FAILURE;
                }
                if (verbose_flag) {
                        printf("PID written in '%s'\n", pidfile);
                }
        }

        return EXIT_SUCCESS;
}
