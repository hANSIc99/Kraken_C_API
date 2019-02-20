# Kraken C API

This API is intended for use on Linux/Unix-like systems.
The API depends on *Curl*.

On the most distributions curl is installed by default,
if not, you can get it from here:

https://curl.haxx.se/

## Infos

Compile with *make*.

Set/unset *DEBUG* or *TRACE* in the makefile to get trace/debug information
printed to stdout.

## Usage

Just include *kraken_api.h* in the sources of your own project.

Get Doxygen and create the documentation. 
If Doxygen is not installed you can get it from here:

http://www.doxygen.org

Once you have run *doxygen Doxyfile*, look in the documentation of *main.c*,
there you can find many examples.

If you dont want to use doxygen, simply look into *main.c*
to see how to execute a trade.

## Build

**Prerequisites**

To be able to build the API, you need the SSL-devel files on your system.
On Debian, Ubuntu or similar distributions type:
`sudo apt install libssl-dev`  

On Fedora, RHEL or similar distributions type:
`sudo dnf install openssl-devel` 

To build the examples inside main.c, simply
call `make` from within the source folder.

**Build with libssl < 1.10**

`make CFLAGS=-DOPENSSL_1_0`

**Build static library**

`make LIBRARY`



