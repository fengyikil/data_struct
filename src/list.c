#include "list.h"
#define NULL 0
// 双链表长度
int list_len(const struct list_head *head)
{
    int len = 0;
    struct list_head *pos;
    for (pos = (head)->next; pos != (head); pos = pos->next)
    {
        len++;
    }
    return len;
}
//向后移动
struct list_head *list_move_next(const struct list_head *pos, int step, struct list_head *end)
{
    struct list_head *rnd = pos;
    for (int i = 0; i < step; i++)
    {
        if (rnd == end)
            break;
        rnd = pos->next;
    }
    return rnd;
}

// merge two sorted list to one
struct list_head *merge(struct list_head *head1, struct list_head *head2, less_callback isless)
{
    struct list_head *res, *p, *h1, *h2, *end1, *end2;
    h1 = head1;
    h2 = head2;
    end1 = head1->prev;
    end2 = head2->prev;

    if ((*isless)(h1, h2))
    {
        res = h1;
        h1 = h1->next;
    }
    else
    {
        res = h2;
        h2 = h2->next;
    }
    p = res;
    while (1)
    {
        if ((*isless)(h1, h2))
        {
            if (h1 != end1)
            {
                p->next = h1;
                h1->prev = p;
                h1 = h1->next;
                p = p->next;
            }
            else
            {
                p->next = h1;
                h1->prev = p;
                p = p->next;

                p->next = h2;
                h2->prev = p;
                res->prev = end2;
                end2->next = res;
                break;
            }
        }
        else
        {
            if (h2 != end2)
            {
                p->next = h2;
                h2->prev = p;
                h2 = h2->next;
                p = p->next;
            }
            else
            {
                p->next = h2;
                h2->prev = p;
                p = p->next;

                p->next = h1;
                h1->prev = p;
                res->prev = end1;
                end1->next = res = res;
                break;
            }
        }
    }
    return res;
}

struct list_head *sort(struct list_head *head, less_callback less)
{
    //链表归并排序
    if (head->next == head)
        return head;
    else
    {
        //快慢指针找到中间节点
        struct list_head *fast = head, *slow = head, *front, *black, *rnd;
        while (fast->next != head && fast->next->next != head)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        slow = slow->next;

        if (head->next == slow && slow->next != head)
        {
            slow->prev = head->prev;
            slow->prev->next = slow;
            head->next = head;
            head->prev = head;
        }
        else if (head->next != slow && slow->next == head)
        {
            head->prev = slow->prev;
            slow->prev->next = head;
            slow->next = slow;
            slow->prev = slow;
        }
        else if (head->next != slow && slow->next != head)
        {
            rnd = head->prev;
            head->prev = slow->prev;
            slow->prev->next = head;

            rnd->next = slow;
            slow->prev = rnd;
        }
        else if (head->next == slow && slow->next == head)
        {
            slow->next = slow;
            slow->prev = slow;

            head->next = head;
            head->prev = head;
        }

        front = sort(head, less); //前半段排序
        black = sort(slow, less); //后半段排序
        return merge(front, black, less);
    }
}
struct list_head *sort_list(struct list_head *head, less_callback less)
{
    struct list_head *rnd;
    if (head != NULL || head->next == head)
    {
        return head;
    }
    head->next->prev = head->prev;
    head->prev->next = head->next;
    rnd = sort(head->next, less);
    head->next = rnd;
    head->prev = rnd->prev;
    rnd->prev = head;
    return head;
}
