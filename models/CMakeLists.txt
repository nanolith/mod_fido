SET(CBMC_OPTIONS
    "--bounds-check" "--pointer-check" "--memory-leak-check"
    "--malloc-may-fail" "--malloc-fail-null" "--div-by-zero-check"
    "--pointer-overflow-check" "--trace" "--stop-on-fail"
    "--drop-unused-functions" "--unwind" "10" "--unwinding-assertions")

#CBMC build options
SET(CBMC_BUILD_OPTIONS "-D_ANSI_LIBRARY -DCBMC=1 -nostdinc -I /usr/src/sys/amd64/include -I /usr/src/sys -I ${CMAKE_SOURCE_DIR}/models -I ${CMAKE_SOURCE_DIR}/src -I ${CMAKE_BINARY_DIR}/src")

ADD_SUBDIRECTORY(auth_cache_entry_cmp)
