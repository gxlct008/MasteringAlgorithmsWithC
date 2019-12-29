/*****************************************************************************
*                                                                            *
*  lru-1.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates using a circular list (see Chapter 5).           *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../../source/page.c"

/*****************************************************************************
*                                                                            *
*  ------------------------------ print_list ------------------------------  *
*                                                                            *
*****************************************************************************/

static void print_list(const CList *list) {
    CListElmt       *element;
    int             *data, size, i;

    /*****************************************************************************
    *                                                                            *
    *  Display the circular list.                                                *
    *                                                                            *
    *****************************************************************************/

    fprintf(stdout, "List size is %d (circling twice)\n", clist_size(list));

    size = clist_size(list);
    element = clist_head(list);

    /*****************************************************************************
    *                                                                            *
    *  Iterate twice through the circular list to verify the circular links.     *
    *                                                                            *
    *****************************************************************************/

    i = 0;
    while (i < size * 2) {
        data = clist_data(element);
        fprintf(stdout, "list[%03d]=%03d\n", (i % size), *data);
        element = clist_next(element);
        i++;
    }

    return;
}

/*****************************************************************************
*                                                                            *
*  --------------------------------- main ---------------------------------  *
*                                                                            *
*****************************************************************************/

int main(int argc, char const *argv[])
{
    CList       list;
    CListElmt   *element;

    int         *data, i;

    /*****************************************************************************
    *                                                                            *
    *  Initialize the circular list.                                             *
    *                                                                            *
    *****************************************************************************/

    clist_init(&list, free);

    /*****************************************************************************
    *                                                                            *
    *  Perform some circular list operations.                                    *
    *                                                                            *
    *****************************************************************************/

    element = clist_head(&list);

    for (i = 0; i < 10; i++)
    {
        if ((data = (int *)malloc(sizeof(int))) == NULL)
        {
            return 1;
        }

        *data = 1;

        if (clist_ins_next(&list, element, data) != 0)
        {
            return 1;
        }

        if (element == NULL)
        {
            element = clist_next(clist_head(&list));
        } else {
            element = clist_next(element);
        }
    }

    // 打印出初始化后的循环链表元素
    print_list(&list);

    // ==========================================
    //    循环链表将元素的引用值设置为0
    // ==========================================

    // 获取头元素
    element = clist_head(&list);

    for (i = 0; i < 10; i++)
    {
        element = clist_next(element);
    }
    data = clist_data(element);
    fprintf(stdout, "Circling and seting the element value to 0" " %03d\n", *data);

    // for (i = 0; i < 10; i++)
    // {
        // replace_page(data);
    // }
    print_list(&list);
    return 0;
}

