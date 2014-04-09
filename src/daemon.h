#ifndef _DAEMON_H
#define _DAEMON_H 1

#include <sys/types.h>

/**
 * Launch a command as a daemon. This creates a fork which itself creates
 * another fork which executes the command. The first child exits and cause the
 * second child to be re-parented to init.
 * - cmd: the command to daemonize
 * - verbose: 1 for a (slightly) verbose forking, 0 for a silent one.
 **/
int daemonize(char *const cmd[], char verbose);

#endif /* _DAEMON_H */
