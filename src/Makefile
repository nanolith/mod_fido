KMOD=mod_fido
C_SRCS != ls ${.CURDIR}/*.c | xargs basename
SRCS=${C_SRCS} vnode_if.h device_if.h bus_if.h
CFLAGS+=-DCBMC=0 -I${.CURDIR}/../include

.include <bsd.kmod.mk>
