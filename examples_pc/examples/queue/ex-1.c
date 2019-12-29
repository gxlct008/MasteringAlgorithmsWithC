/*****************************************************************************
*                                                                            *
*  ex-1.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates using a queue (see Chapter 6).                   *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../../source/queue.c"

/*****************************************************************************
*                                                                            *
*  ------------------------------ print_queue -----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_queue(const Queue *queue) {
    ListElmt        *element;
    int             *data,
                    size,
                    i;

    /*****************************************************************************
    *                                                                            *
    *  Display the queue.                                                        *
    *                                                                            *
    *****************************************************************************/

    fprintf(stdout, "Queue size is %d\n", size = queue_size(queue));

    i = 0;
    element = list_head(queue);

    while (i < size) {
        data = list_data(element);
        fprintf(stdout, "queue[%03d]=%03d\n", i, *data);
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
    Queue           queue;
    int             *data,
                    i;
    /*****************************************************************************
    *                                                                            *
    *  Initialize the queue.                                                     *
    *                                                                            *
    *****************************************************************************/

    queue_init(&queue, free);

    /*****************************************************************************
    *                                                                            *
    *  Perform some queue operations.                                            *
    *                                                                            *
    *****************************************************************************/

    // ===========================================
    //    往队列中插入10个元素
    // ===========================================
    fprintf(stdout, "Enqueuing 10 elements\n");

    for (i = 0; i < 10; i++)
    {
        if ((data = (int *)malloc(sizeof(int))) == NULL)
        {
            return 1;
        }

        *data = i + 1;

        if (queue_enqueue(&queue, data) != 0)
        {
            return 1;
        }
    }

    // 打印出队列中的元素
    print_queue(&queue);


    // ===========================================
    //    从队列中出队5个元素
    // ===========================================
    fprintf(stdout, "Dequeuing 5 elements\n");

    for (i = 0; i < 5; i++)
    {
        if (queue_dequeue(&queue, (void **)&data) == 0)
        {
            free(data);
        } else {
            return 1;
        }
    }

    // 打印出队列中剩余的元素
    print_queue(&queue);

    // ===========================================
    //    元素100 和 200入队
    // ===========================================
    fprintf(stdout, "Enqueuing 100 and 200\n");

    if ((data = (int *)malloc(sizeof(int))) == NULL)
    {
        return 1;
    }

    *data = 100;

    if (queue_enqueue(&queue, data) != 0)
    {
        return 1;
    }

    if ((data = (int *)malloc(sizeof(int))) == NULL)
    {
        return 1;
    }

    *data = 200;

    if (queue_enqueue(&queue, data) != 0)
    {
        return 1;
    }

    // 打印出插入新元素后队列中的所有元素
    print_queue(&queue);

    // ===========================================
    //    检测队列头部元素
    // ===========================================
    if ((data = queue_peek(&queue)) != NULL)
    {
        fprintf(stdout, "Peeking at the head element ... Value=%03d\n", *data);
    } else {
        fprintf(stdout, "Peeking at the head element ... Value=NULL\n");
    }

    // 打印出检测队列头部元素后队列中的所有元素
    print_queue(&queue);

    // ===========================================
    //    出队所有的元素
    // ===========================================
    fprintf(stdout, "Dequeuing all elements\n");

    while (queue_size(&queue) > 0) {
        if (queue_dequeue(&queue, (void *)&data) == 0)
        {
            free(data);
        }
    }

    // ===========================================
    //    检测空队列中的元素
    // ===========================================
    if ((data = queue_peek(&queue)) != NULL)
    {
        fprintf(stdout, "Peeking at an empty queue ... Value=%03d\n", *data);
    } else {
        fprintf(stdout, "Peeking at an empty queue ... Value=NULL\n");
    }

    // 打印出队列中的所有元素
    print_queue(&queue);

    /*****************************************************************************
    *                                                                            *
    *  Destroy the queue.                                                        *
    *                                                                            *
    *****************************************************************************/

    fprintf(stdout, "Destroying the queue\n");
    queue_destroy(&queue);

    return 0;
}
