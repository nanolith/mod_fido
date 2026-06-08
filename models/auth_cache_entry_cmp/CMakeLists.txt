SET(MC_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/mod_fido/property_mod_fido_auth_cache_entry_valid.c
    ${CMAKE_SOURCE_DIR}/src/auth_cache_entry_cmp.c
    main.c)

ADD_EXECUTABLE(model_auth_cache_entry_cmp ${MC_SOURCES})
SET_TARGET_PROPERTIES(
    model_auth_cache_entry_cmp PROPERTIES
    C_COMPILER_LAUNCHER "${COMPILER_CHOOSER};goto-cc"
    C_LINKER_LAUNCHER "${LINKER_CHOOSER};goto-ld")
TARGET_COMPILE_OPTIONS(
    model_auth_cache_entry_cmp
        PRIVATE ${CBMC_BUILD_OPTIONS})
SET_PROPERTY(
    TARGET model_auth_cache_entry_cmp
    PROPERTY JOB_POOL_LINK console)

ADD_CUSTOM_COMMAND(
    TARGET model_auth_cache_entry_cmp
    POST_BUILD
    COMMAND cbmc ${CBMC_OPTIONS}
                 model_auth_cache_entry_cmp
    USES_TERMINAL)
