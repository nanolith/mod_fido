/**
 * \file models/auth_cache_entry_cmp/main.c
 *
 * \brief Model checks for \ref auth_cache_entry_cmp.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "auth_cache.h"

int main(int argc, char* argv[])
{
    int retval;
    auth_cache_entry lhs, rhs;

    __CPROVER_havoc_object(&lhs);
    __CPROVER_havoc_object(&rhs);

    /* compare the two instances. */
    retval = auth_cache_entry_cmp(&lhs, &rhs);
    if (retval < 0)
    {
        retval = 1;
        goto done;
    }
    else if (retval == 0)
    {
        retval = 2;
        goto done;
    }
    else
    {
        retval = 3;
        goto done;
    }

done:
    return retval;
}
