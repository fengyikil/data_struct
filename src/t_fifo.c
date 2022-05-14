#include "fifo.h"
#include <stdio.h>
typedef struct
{
    int age;
    char name;
} strudent;

void test_fifo()
{
    strudent studt = {1, 'c'};
    struct fifo *ff = fifo_init(sizeof(studt) * 4);
    int ret;
    //插入5个，容量不够只能插入4个
    for (int i = 0; i < 5; i++)
    {
        studt.age = i;
        fifo_put(ff, (void *)&studt, sizeof(studt));
    }
    //取出4个
    for (int i = 0; i < 4; i++)
    {
        ret = fifo_get(ff, (void *)&studt, sizeof(studt));
        if (ret == sizeof(studt))
        {
            printf("studt.age is %d\n", studt.age);
        }
    }
    //再插入3个
    for (int i = 0; i < 3; i++)
    {
        studt.age = i + 10;
        fifo_put(ff, (void *)&studt, sizeof(studt));
    }
    //取出4个，不够4个，只能取出3个
    for (int i = 0; i < 4; i++)
    {
        ret = fifo_get(ff, (void *)&studt, sizeof(studt));
        if (ret == sizeof(studt))
        {
            printf("studt.age is %d\n", studt.age);
        }
    }
}