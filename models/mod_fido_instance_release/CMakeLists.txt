SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/auth_cache/auth_cache_entry_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/auth_cache/auth_cache_table_next_simple_loop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/auth_cache/auth_cache_table_remove_simple_loop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/auth_cache/auth_cache_table_start_simple_loop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/kernel/mtx_destroy.c
    ${CMAKE_SOURCE_DIR}/models/shadow/kernel/mtx_lock.c
    ${CMAKE_SOURCE_DIR}/models/shadow/kernel/mtx_init.c
    ${CMAKE_SOURCE_DIR}/models/shadow/kernel/mtx_unlock.c
    ${CMAKE_SOURCE_DIR}/models/shadow/kernel/property_mtx_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/mod_fido/mod_fido_instance_create_random.c
    ${CMAKE_SOURCE_DIR}/models/shadow/mod_fido/mod_fido_instance_unhook_ioctl_locked_noop.c
    ${CMAKE_SOURCE_DIR}/models/shadow/mod_fido/property_mod_fido_auth_cache_entry_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/mod_fido/property_mod_fido_instance_hooked.c
    ${CMAKE_SOURCE_DIR}/models/shadow/mod_fido/property_mod_fido_instance_locked.c
    ${CMAKE_SOURCE_DIR}/src/auth_cache_entry_cmp.c
    ${CMAKE_SOURCE_DIR}/src/mod_fido_instance_release.c
    main.c)

ADD_EXECUTABLE(model_mod_fido_instance_release ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_mod_fido_instance_release PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_mod_fido_instance_release
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_mod_fido_instance_release
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_mod_fido_instance_release
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 model_mod_fido_instance_release
    USES_TERMINAL)
