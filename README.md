# homer(1)

**Homer** is a tool to daemonize a task written in pure ANSI C89.

This is currently more of a proof of concept, it doesn’t support PID files and
logging.

## Install

    git clone https://github.com/bfontaine/homer.git
    cd homer
    [sudo] make install

## Usage

    $ homer mycommand args ...

It’ll start `mycommand args ...` in a daemonized processus and print its PID.

Type `homer -h` to see all available options.

## License

MIT. See the [LICENSE][] file.

[LICENSE]: https://github.com/bfontaine/homer/blob/master/LICENSE
