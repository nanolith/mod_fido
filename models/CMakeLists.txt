SET(CBMC_OPTIONS
    "--bounds-check" "--pointer-check" "--memory-leak-check"
#   Note: in the kernel, we specifically use M_WAITOK, which pauses the kernel
#   thread until the allocation succeeds.
#    "--malloc-may-fail" "--malloc-fail-null"
    "--no-malloc-may-fail" "--div-by-zero-check"
    "--pointer-overflow-check" "--trace" "--stop-on-fail"
    "--drop-unused-functions" "--unwind" "10" "--unwinding-assertions")

set(MAKE_DEBUG_FLAG "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MAKE_DEBUG_FLAG "-DDEBUG=1")
endif()

#CBMC build options
SET(CBMC_BUILD_OPTIONS "-D_ANSI_LIBRARY -DCBMC=1 -I ${CMAKE_SOURCE_DIR}/models -I ${CMAKE_SOURCE_DIR}/src -I ${CMAKE_BINARY_DIR}/src ${MAKE_DEBUG_FLAG}")

ADD_SUBDIRECTORY(auth_cache_entry_cmp)
ADD_SUBDIRECTORY(mod_fido_handler)
ADD_SUBDIRECTORY(mod_fido_instance_create_release)
ADD_SUBDIRECTORY(mod_fido_instance_hook_ioctl_locked)
ADD_SUBDIRECTORY(mod_fido_instance_hook_ioctl_locked_shadow)
ADD_SUBDIRECTORY(mod_fido_instance_ioctl_tty_get)
ADD_SUBDIRECTORY(mod_fido_instance_ioctl_tty_get_shadow)
ADD_SUBDIRECTORY(mod_fido_instance_release)
ADD_SUBDIRECTORY(mod_fido_instance_unhook_ioctl_locked)
ADD_SUBDIRECTORY(mod_fido_instance_unhook_ioctl_locked_noop_shadow)
