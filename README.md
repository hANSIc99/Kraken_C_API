# Kraken C API

This API is intended for use on Linux/Unix-like systems.
Furthermore, it depends on *Curl*.

On the most distributions curl is installed by default,
if not, you can get it here:

https://curl.haxx.se/

## Infos

Compile it with *make*.

Set/unset *DEBUG* or *TRACE* in the makefile to get trace/debug information
printed to stdout.

## Usage

Just include *kraken_api.h* and the source files to your own program.

Look into *main.c* to see how to execute a trade.

## ToDo's

A lot:

- rework trace/debug output
- add private user data queries
- add puplic market data query






