mod_fido
========

fido, or "filtered do", is a simple doas / sudo clone. This FreeBSD kernel
module allows fido to persist authentication to a terminal for a time, in a way
similar to how doas does this on OpenBSD. This eliminates the need for tracking
authentication through any other means (e.g. filesystem database) and reduces
the attack surface to a single IOCTL over the tty device. These IOCTL is
intercepted by this kernel module, which verifies that the root effective uid,
scans its cache for the given device, then checks the uid and either sets or
returns the last authenticated time.

To use this module, build it and load it. Ideally, configure it to load at boot
time. Re-configure and rebuild fido. It will detect the existence of this
module, which will enable a persistence window of 300 seconds.

Disclaimer
==========

Please note that this module hooks syscalls and the global file operations
table. This is a didactic example and probably shouldn't be used in production.
You have been warned.

Building
========

This utility is for FreeBSD only. It has only been tested on FreeBSD 15.0.

This utility requires cmake and GNU Make / ninja to build. Additionally, you
will need the FreeBSD 15 source tree.  The first two can be installed via
`pkg install`. This can be downloaded as per instructions in the [FreeBSD
Developer's Handbook][freebsd-dev-handbook].

[freebsd-dev-handbook]: https://docs.freebsd.org/en/books/developers-handbook/book/

To build this project, from the project root, create a separate build directory
(e.g. `build`) change into this directory, and run cmake. Make sure that minunit
is in your `PKG_CONFIG_PATH` so it can be detected.

    $ mkdir build
    $ cd build
    $ cmake .. 
    #### or
    $ cmake -G Ninja ..

If you would like to run the model checks, you will also need a recent release
of [cbmc][cbmc]. When configuring cmake, pass `-DMODEL_CHECKING_ENABLED=true`.

    $ cmake -DMODEL_CHECKING_ENABLED=true

[cbmc]: https://github.com/diffblue/cbmc
