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
