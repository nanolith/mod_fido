KMOD=mod_fido
SRCS=mod_fido.c auth_cache_entry_cmp.c auth_cache_table.c \
     vnode_if.h device_if.h bus_if.h
CFLAGS+=-DCBMC=0 -I${.CURDIR}/../include

.include <bsd.kmod.mk>
