#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct person
{
    int age;
    char name[20];
    struct list_head list;
};

int my_list_less(struct list_head *node1, struct list_head *node2)
{
    struct person *p1 = list_entry(node1, struct person, list);
    struct person *p2 = list_entry(node2, struct person, list);
    if (p1->age < p2->age)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void test_list_sort()
{
    struct person *pperson;
    struct person person_head = {56, "xxx", NULL};
    struct list_head *pos, *next, *rnd;
    int i;

    // 初始化双链表的表头
    INIT_LIST_HEAD(&person_head.list);

    // 添加节点
    for (i = 10; i > 0; i--)
    {
        pperson = (struct person *)malloc(sizeof(struct person));
        pperson->age = (i + 1) * 10;
        sprintf(pperson->name, "%d", i + 1);
        // 将节点链接到链表的末尾
        // 如果想把节点链接到链表的表头后面，则使用 list_add
        list_add_tail(&(pperson->list), &(person_head.list));
    }

    // 遍历链表
    printf("==== 1st iterator d-link ====\n");
    list_for_each(pos, &person_head.list)
    {
        pperson = list_entry(pos, struct person, list);
        printf("name:%-2s, age:%d\n", pperson->name, pperson->age);
    }

    rnd = sort_list(&person_head.list, my_list_less);
    printf("sortList end!\n");
    // 再次遍历链表
    list_for_each(pos, rnd)
    {
        pperson = list_entry(pos, struct person, list);
        printf("name:%-2s, age:%d\n", pperson->name, pperson->age);
    }
    // 释放资源
    list_for_each_safe(pos, next, &person_head.list)
    {
        pperson = list_entry(pos, struct person, list);
        list_del_init(pos);
        free(pperson);
    }
}
