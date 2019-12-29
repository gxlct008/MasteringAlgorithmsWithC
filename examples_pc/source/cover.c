/*****************************************************************************
*                                                                            *
*  -------------------------------- cover.c -------------------------------  *
*                                                                            *
*****************************************************************************/

#include <stdlib.h>

#include "../include/cover.h"
#include "set.c"

/*****************************************************************************
*                                                                            *
*  --------------------------------- cover --------------------------------  *
*                                                                            *
*****************************************************************************/

/**
 * 挑选出能够覆盖集合 S 的近似最优解
 * @param  members    待覆盖的集合 S
 * @param  subsets    集合 P 的子集
 * @param  covering   挑选出的能满足覆盖条件的集合 C
 * @return
 */
int cover(Set *members, Set *subsets, Set *covering) {
    Set         intersection;
    KSet        *subset;

    ListElmt    *member,
                *max_member;

    void        *data;
    int         max_size;

    /*****************************************************************************
    *                                                                            *
    *  Initialize the covering.                                                  *
    *                                                                            *
    *****************************************************************************/

    set_init(covering, subsets->match, NULL);

    /*****************************************************************************
    *                                                                            *
    *  Continue while there are noncovered members and candidate subsets.        *
    *                                                                            *
    *****************************************************************************/

    while (set_size(members) > 0 && set_size(subsets) > 0) {
        /**************************************************************************
        *                                                                         *
        *  Find the subset that covers the most members.                          *
        *                                                                         *
        **************************************************************************/

        max_size = 0;

        for (member = list_head(subsets); member != NULL; member = list_next(member)) {

            if (set_intersection(&intersection, &((KSet *)list_data(member))->set, members) != 0) {
                return -1;
            }

            if (set_size(&intersection) > max_size) {
                max_member = member;
                max_size = set_size(&intersection);
            }

            set_destroy(&intersection);
        }
        /**************************************************************************
        *                                                                         *
        *  A covering is not possible if there was no intersection.               *
        *                                                                         *
        **************************************************************************/

        if (max_size == 0) {
            return 1;
        }

        /**************************************************************************
        *                                                                         *
        *  Insert the selected subset into the covering.                          *
        *                                                                         *
        **************************************************************************/

        subset = (KSet *)list_data(max_member);

        if (set_insert(covering, subset) != 0) {
            return -1;
        }

        /**************************************************************************
        *                                                                         *
        *  Remove each covered member from the set of noncovered members.         *
        *                                                                         *
        **************************************************************************/

        for (member = list_head(&((KSet *)list_data(max_member))->set); member != NULL; member = list_next(member)) {
            data = list_data(member);

            if (set_remove(members, (void **)&data) == 0 && members->destroy != NULL) {
                members->destroy(data);
            }
        }

        /**************************************************************************
        *                                                                         *
        *  Remove the subset from the set of candidate subsets.                   *
        *                                                                         *
        **************************************************************************/

        if (set_remove(subsets, (void **)&subset) != 0) {
            return -1;
        }
    }

    /*****************************************************************************
    *                                                                            *
    *  No covering is possible if there are still noncovered members.            *
    *                                                                            *
    *****************************************************************************/

    if (set_size(members) > 0) {
        return -1;
    }

    return 0;
}
