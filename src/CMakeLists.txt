set(KMOD_OBJ_DIR "${CMAKE_CURRENT_BINARY_DIR}")

file(MAKE_DIRECTORY "${KMOD_OBJ_DIR}")

add_custom_target(mod_fido_target ALL
    COMMAND cd "${CMAKE_CURRENT_SOURCE_DIR}" && make MAKEOBJDIR=${KMOD_OBJ_DIR} obj
    COMMAND cd "${CMAKE_CURRENT_SOURCE_DIR}" && make MAKEOBJDIR=${KMOD_OBJ_DIR}
    BYPRODUCTS "${KMOD_OBJ_DIR}/mod_fido.ko"
)

add_custom_target(mod_fido ALL DEPENDS mod_fido_target)
