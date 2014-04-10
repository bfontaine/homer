#ifndef _DAEMON_H
#define _DAEMON_H 1

#include <sys/types.h>

/**
 * Launch a command as a daemon. This creates a fork which itself creates
 * another fork which executes the command. The first child exits and cause the
 * second child to be re-parented to init. The function returns the PID of the
 * second child or -1 on error.
 * - cmd: the command to daemonize
 * - verbose: 1 for a (slightly) verbose forking, 0 for a silent one.
 **/
pid_t daemonize(char *const cmd[]);

#endif /* _DAEMON_H */
