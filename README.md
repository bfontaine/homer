# homer(1)

[![Build Status](https://travis-ci.org/bfontaine/homer.svg?branch=master)](https://travis-ci.org/bfontaine/homer)

**Homer** is a command-line tool to daemonize a task.

This is an alpha release, it doesn’t support PID files and logging.

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
