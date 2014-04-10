# homer(1)

[![Build Status](https://travis-ci.org/bfontaine/homer.svg?branch=master)](https://travis-ci.org/bfontaine/homer)

**Homer** is a command-line tool to daemonize a task.

## Install

    git clone https://github.com/bfontaine/homer.git
    cd homer
    [sudo] make install

## Usage

    $ homer mycommand args ...

It’ll start `mycommand args ...` in a daemonized processus and print its PID.

Type `homer -h` to see all available options as well as usage examples.

## Tests

    git clone https://github.com/bfontaine/homer.git
    cd homer
    make test

## License

[MIT][LICENSE].

[LICENSE]: https://github.com/bfontaine/homer/blob/master/LICENSE

## Why?

![](https://github.com/bfontaine/homer/raw/master/images/all_the_things.png)
