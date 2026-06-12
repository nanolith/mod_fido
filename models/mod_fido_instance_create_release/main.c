/**
 * \file models/mod_fido_instance_create_release/main.c
 *
 * \brief Model checks for \ref mod_fido_instance_create and
 * \ref mod_fido_instance_release.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "mod_fido.h"

int main(int argc, char* argv[])
{
    int retval;
    auth_cache_entry lhs, rhs;
    mod_fido_instance* inst;

    /* create an instance. */
    retval = mod_fido_instance_create(&inst);
    MODEL_ASSERT(0 == retval);

    /* release the instance. */
    retval = mod_fido_instance_release(inst);
    if (0 != retval)
    {
        goto done;
    }

done:
    return retval;
}
