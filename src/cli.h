#ifndef _CLI_H
#define _CLI_H 1

/**
 * Print an help text.
 * - exe: the name of the executable for this program. This should be argv[0].
 **/
int print_help(char *exe);

/** Print the current version **/
int print_version(void);

#endif /* _CLI_H */
