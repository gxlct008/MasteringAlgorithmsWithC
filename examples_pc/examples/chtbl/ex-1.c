/*****************************************************************************
*                                                                            *
*  ex-1.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates using a chained hash table (see Chapter 8).      *
*                                                                            *
*****************************************************************************/

#include <stdio.h>

#include "../../source/chtbl.c"

/*****************************************************************************
*                                                                            *
*  Define the size of the chained hash table.                                *
*                                                                            *
*****************************************************************************/

#define            TBLSIZ         11

/*****************************************************************************
*                                                                            *
*  ------------------------------ match_char ------------------------------  *
*                                                                            *
*****************************************************************************/

static int match_char(const void *char1, const void *char2) {

    /*****************************************************************************
    *                                                                            *
    *  Compare two characters.                                                   *
    *                                                                            *
    *****************************************************************************/

    return (*(const char *)char1 == *(const char *)char2);
}

/*****************************************************************************
*                                                                            *
*  -------------------------------- h_char --------------------------------  *
*                                                                            *
*****************************************************************************/

static int h_char(const void *key) {

    /*****************************************************************************
    *                                                                            *
    *  Define a simplistic hash function.                                        *
    *                                                                            *
    *****************************************************************************/

    return *(const char *)key % TBLSIZ;
}


/*****************************************************************************
*                                                                            *
*  ------------------------------ print_table -----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_table(const CHTbl *htbl) {
    ListElmt        *element;

    int             i;

    /*****************************************************************************
    *                                                                            *
    *  Display the chained hash table.                                           *
    *                                                                            *
    *****************************************************************************/

    fprintf(stdout, "Table size is %d\n", chtbl_size(htbl));

    for (i = 0; i < TBLSIZ; i++)
    {
        fprintf(stdout, "Bucket[%03d]=", i);

        for (element = list_head(&htbl->table[i]); element != NULL; element = list_next(element))
        {
            fprintf(stdout, "%c", *(char *)list_data(element));
        }

        fprintf(stdout, "\n");
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
    CHTbl          htbl;

    char           *data,
                    c;

    int             retval,
                    i;
    /*****************************************************************************
    *                                                                            *
    *  Initialize the chained hash table.                                        *
    *                                                                            *
    *****************************************************************************/

    if (chtbl_init(&htbl, TBLSIZ, h_char, match_char, free) != 0)
    {
        return 1;
    }

    /*****************************************************************************
    *                                                                            *
    *  Perform some chained hash table operations.                               *
    *                                                                            *
    *****************************************************************************/

    for (i = 0; i < TBLSIZ; i++)
    {
        if ((data = (char *)malloc(sizeof(char))) == NULL)
        {
            return 1;
        }

        *data = ((5 + (i * 6)) % 23) + 'A';

        if (chtbl_insert(&htbl, data) != 0)
        {
            return 1;
        }

        // 输出链式哈希表中的元素
        print_table(&htbl);
    }

    for (i = 0; i < TBLSIZ; i++)
    {
        if ((data = (char *)malloc(sizeof(char))) == NULL)
        {
            return 1;
        }

        *data = ((3 + (i * 4)) % 23) + 'a';

        if (chtbl_insert(&htbl, data) != 0)
        {
            return 1;
        }

        // 输出链式哈希表中的元素
        print_table(&htbl);
    }

    // =================================================
    if ((data = (char *)malloc(sizeof(char))) == NULL)
    {
        return 1;
    }

    *data = 'd';

    if ((retval = chtbl_insert(&htbl, data)) != 0)
    {
        free(data);
    }

    // ===========================================
    //    往链式哈希表中重复插入元素 d
    // ===========================================
    fprintf(stdout, "Trying to insert d again...Value=%d (1=OK)\n", retval);

    if ((data = (char *)malloc(sizeof(char))) == NULL)
    {
        return 1;
    }

    *data = 'G';

    if ((retval = chtbl_insert(&htbl, data)) != 0)
    {
        free(data);
    }

    // ===========================================
    //    往链式哈希表中重复插入元素 G
    // ===========================================
    fprintf(stdout, "Trying to insert G again...Value=%d (1=OK)\n", retval);


    // ===========================================
    //    从链式哈希表中删除元素 d, G, and S
    // ===========================================
    fprintf(stdout, "Removing d, G, and S\n");

    c = 'd';
    data = &c;

    if (chtbl_remove(&htbl, (void **)&data) == 0)
    {
        free(data);
    }

    c = 'G';
    data = &c;

    if (chtbl_remove(&htbl, (void **)&data) == 0)
    {
        free(data);
    }

    c = 'S';
    data = &c;

    if (chtbl_remove(&htbl, (void **)&data) == 0)
    {
        free(data);
    }

    // 输出链式哈希表中的元素
    print_table(&htbl);


    if ((data = (char *)malloc(sizeof(char))) == NULL)
    {
        return 1;
    }

    *data = 'd';

    if ((retval = chtbl_insert(&htbl, data)) != 0)
    {
        free(data);
    }

    // ===========================================
    //    往链式哈希表中重复插入元素 d
    // ===========================================
    fprintf(stdout, "Trying to insert d again...Value=%d (1=OK)\n", retval);

    if ((data = (char *)malloc(sizeof(char))) == NULL)
    {
        return 1;
    }

    *data = 'G';

    if ((retval = chtbl_insert(&htbl, data)) != 0)
    {
        free(data);
    }

    // ===========================================
    //    往链式哈希表中重复插入元素 G
    // ===========================================
    fprintf(stdout, "Trying to insert G again...Value=%d (1=OK)\n", retval);

    // 输出链式哈希表中的元素
    print_table(&htbl);


    // ===========================================
    //    往链式哈希表中插入元素 X and Y
    // ===========================================
    fprintf(stdout, "Inserting X, and Y\n");


    if ((data = (char *)malloc(sizeof(char))) == NULL)
    {
        return 1;
    }

    *data = 'X';

    if (chtbl_insert(&htbl, data) != 0)
    {
        return 1;
    }

    if ((data = (char *)malloc(sizeof(char))) == NULL)
    {
        return 1;
    }

    *data = 'Y';

    if (chtbl_insert(&htbl, data) != 0)
    {
        return 1;
    }

    // 输出链式哈希表中的元素
    print_table(&htbl);


    // ===========================================
    //    在链式哈希表中查找元素 X and Z
    // ===========================================
    c = 'X';
    data = &c;

    if (chtbl_lookup(&htbl, (void **)&data) == 0)
    {
        fprintf(stdout, "Found an occurrence of X\n");
    } else {
        fprintf(stdout, "Did not find an occurrence of X\n");
    }

    c = 'Z';
    data = &c;

    if (chtbl_lookup(&htbl, (void **)&data) == 0)
    {
        fprintf(stdout, "Found an occurrence of Z\n");
    } else {
        fprintf(stdout, "Did not find an occurrence of Z\n");
    }

    /*****************************************************************************
    *                                                                            *
    *  Destroy the chained hash table.                                           *
    *                                                                            *
    *****************************************************************************/

    fprintf(stdout, "Destroying the hash table\n");
    chtbl_destroy(&htbl);


    return 0;
}
