# homer(1)

[![Build Status](https://travis-ci.org/bfontaine/homer.svg?branch=master)](https://travis-ci.org/bfontaine/homer)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/4255/badge.svg)](https://scan.coverity.com/projects/4255)

**Homer** is a command-line tool to daemonize a task.

## Install

### With Homebrew (OSX)

    brew tap bfontaine/utils
    brew install homer

### From sources

    git clone https://github.com/bfontaine/homer.git
    cd homer
    [sudo] make install

## Usage

    $ homer mycommand args ...

It’ll start `mycommand args ...` in a daemonized processus and print its PID.

Type `homer -h` or see [the man page][man] to see all available options as well
as usage examples.

[man]: https://bfontaine.github.io/homer

### Features

- PID file support
- stdout/stderr log files support

## Tests

    git clone https://github.com/bfontaine/homer.git
    cd homer
    make test

## License

[MIT][LICENSE].

[LICENSE]: https://github.com/bfontaine/homer/blob/master/LICENSE

## Why?

![](https://github.com/bfontaine/homer/raw/master/images/all_the_things.png)
