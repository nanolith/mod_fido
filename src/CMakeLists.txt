set(KMOD_OBJ_DIR "${CMAKE_CURRENT_BINARY_DIR}")

set(MAKE_DEBUG_FLAG "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MAKE_DEBUG_FLAG "DEBUG=1")
endif()

file(MAKE_DIRECTORY "${KMOD_OBJ_DIR}")

add_custom_target(mod_fido_target ALL
    COMMAND cd "${CMAKE_CURRENT_SOURCE_DIR}" && make MAKEOBJDIR=${KMOD_OBJ_DIR} ${MAKE_DEBUG_FLAG} obj
    COMMAND cd "${CMAKE_CURRENT_SOURCE_DIR}" && make MAKEOBJDIR=${KMOD_OBJ_DIR} ${MAKE_DEBUG_FLAG}
    BYPRODUCTS "${KMOD_OBJ_DIR}/mod_fido.ko"
)

add_custom_target(mod_fido ALL DEPENDS mod_fido_target)
