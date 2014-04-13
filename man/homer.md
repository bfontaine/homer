# homer(1) -- Launch daemons

## SYNOPSIS

`homer` [`-q`] [`-p` <file>] [[`-o` <file>] [`-e` <file>] | `-O` <file>] &lt;command&gt;

## DESCRIPTION

Launch the command &lt;command&gt; as a daemon. All options must be given *before*
the command, anything given after it will be passed to the command itself.

## OPTIONS

  * `-e` <file>:
    Redirect `stderr` to a file. If it already exists, new data will be
    appended to its content.

  * `-h`:
    Print the help and exit

  * `-o` <file>:
    Redirect `stdout` to a file. See also `-e`.

  * `-O` <file>:
    Redirect both `stdout` and `stderr` to the same file. This is equivalent to
    using `-e` and `-o` with the same file.

  * `-p` <file>:
    Write the PID of the daemon to a file.

  * `-q`:
    Quiet mode. By default, a success message with the PID of the new process
    is printed. This option removes it but doesn't suppress possible error
    messages.

  * `-v`:
    Print the version and exit


## EXAMPLES

  * Start a program with an unique log::
    `homer -O myserver.log myserver --my-option my-arg`

  * Quiet mode and PID file::
    `homer  -q -p mycmd.pid -o mycmd.out -e mycmd.err mycmd`

## AUTHOR

Written by Baptiste Fontaine <<b@ptistefontaine.fr>\>.

## BUGS

Bugs should be reported at <https://github.com/bfontaine/homer/issues>.

## SEE ALSO

The projet homepage is at <https://github.com/bfontaine/homer>.
