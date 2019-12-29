/*****************************************************************************
*                                                                            *
*  ex-1.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates using a stack (see Chapter 6).                   *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../../source/stack.c"

/*****************************************************************************
*                                                                            *
*  ------------------------------ print_stack -----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_stack(const Stack *stack) {
    ListElmt        *element;
    int             *data,
                    size,
                    i;

    /*****************************************************************************
    *                                                                            *
    *  Display the stack.                                                        *
    *                                                                            *
    *****************************************************************************/

    fprintf(stdout, "Stack size is %d\n", size = stack_size(stack));

    i = 0;
    element = list_head(stack);

    while (i < size) {
        data = list_data(element);
        fprintf(stdout, "stack[%03d]=%03d\n", i, *data);
        element = list_next(element);
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
    Stack           stack;
    int             *data,
                    i;
    /*****************************************************************************
    *                                                                            *
    *  Initialize the stack.                                                     *
    *                                                                            *
    *****************************************************************************/

    stack_init(&stack, free);

    /*****************************************************************************
    *                                                                            *
    *  Perform some stack operations.                                            *
    *                                                                            *
    *****************************************************************************/

    // ===========================================
    //    往栈中压入10个元素
    // ===========================================
    fprintf(stdout, "Pushing 10 elements\n");

    for (i = 0; i < 10; i++)
    {
        if ((data = (int *)malloc(sizeof(int))) == NULL)
        {
            return 1;
        }

        *data = i + 1;

        if (stack_push(&stack, data) != 0)
        {
            return 1;
        }
    }

    // 打印出栈中的元素
    print_stack(&stack);


    // ===========================================
    //    从栈中弹出5个元素
    // ===========================================
    fprintf(stdout, "Poping 5 elements\n");

    for (i = 0; i < 5; i++)
    {
        if (stack_pop(&stack, (void **)&data) == 0)
        {
            free(data);
        } else {
            return 1;
        }
    }

    // 打印出栈中剩余的元素
    print_stack(&stack);

    // ===========================================
    //    元素100 和 200压入栈中
    // ===========================================
    fprintf(stdout, "Pushing 100 and 200\n");

    if ((data = (int *)malloc(sizeof(int))) == NULL)
    {
        return 1;
    }

    *data = 100;

    if (stack_push(&stack, data) != 0)
    {
        return 1;
    }

    if ((data = (int *)malloc(sizeof(int))) == NULL)
    {
        return 1;
    }

    *data = 200;

    if (stack_push(&stack, data) != 0)
    {
        return 1;
    }

    // 打印出插入新元素后栈中的所有元素
    print_stack(&stack);

    // ===========================================
    //    检测栈顶元素
    // ===========================================
    if ((data = stack_peek(&stack)) != NULL)
    {
        fprintf(stdout, "Peeking at the top element ... Value=%03d\n", *data);
    } else {
        fprintf(stdout, "Peeking at the top element ... Value=NULL\n");
    }

    // 打印出检测栈顶元素后栈中的所有元素
    print_stack(&stack);

    // ===========================================
    //    弹出栈中所有的元素
    // ===========================================
    fprintf(stdout, "Poping all elements\n");

    while (stack_size(&stack) > 0) {
        if (stack_pop(&stack, (void *)&data) == 0)
        {
            free(data);
        }
    }

    // ===========================================
    //    检测栈顶元素
    // ===========================================
    if ((data = stack_peek(&stack)) != NULL)
    {
        fprintf(stdout, "Peeking at the top element ... Value=%03d\n", *data);
    } else {
        fprintf(stdout, "Peeking at the top element ... Value=NULL\n");
    }

    // 打印出栈中的所有元素
    print_stack(&stack);

    /*****************************************************************************
    *                                                                            *
    *  Destroy the stack.                                                        *
    *                                                                            *
    *****************************************************************************/

    fprintf(stdout, "Destroying the stack\n");
    stack_destroy(&stack);

    return 0;
}
