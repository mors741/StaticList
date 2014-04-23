// Laba 2
// Semestr 2
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
const int MAX =20;
struct elem
{
    int num;
    int pow;
    int next;
};
struct List
{
    struct elem buffer[MAX];
    int head;
    int free_elem;
};
void init_list(struct List *list) 
{
    list->head=-1;
    list->free_elem=0;
    for (int i =0; i< MAX-1;i++)
        list->buffer[i].next=i+1;
    list->buffer[MAX-1].next=-1;
}
int get_elem(struct List *list, int num, int pow)
{
    if (list->free_elem==-1)
        return -1;
    else
    {
        list->buffer[list->free_elem].num=num;
        list->buffer[list->free_elem].pow=pow;
        int pointer = list->free_elem;
        list->free_elem=list->buffer[list->free_elem].next;
        return pointer;
    }
}
void add_elem(struct List *list, int num, int pow)
{
    int pointer = get_elem(list, num, pow);
    if (list->head==-1)
    {
        list->head=pointer;
        list->buffer[list->head].next=-1;
    }
    else
    {
        int Hpoint = list->head;
        while (list->buffer[Hpoint].next != -1)
            Hpoint = list->buffer[Hpoint].next;
        list->buffer[Hpoint].next =pointer;
        list->buffer[pointer].next=-1;
    }

}
void print_list(List *list)
{
    int pointer = list->head;
    while (pointer != -1)
    {
        printf("  %i\n%ix\n    + \n",list->buffer[pointer].pow,list->buffer[pointer].num);
        pointer=list->buffer[pointer].next;
    }
    printf("\n---------------------------------------\n");
}
int get_size (struct List *list)
{
    int counter = 0;
    int elem = list->head; 
    while (elem!=-1)
    {
        counter++;
        elem=list->buffer[elem].next;
    }
    return counter;
}
void mark_free (struct List *list, int point) 
{
    int p2=list->free_elem;
    if (list->free_elem==-1)
    {
        list->free_elem = point;
        list->buffer[point].next=-1;
    }
    else 
        while (list->buffer[p2].next!=-1)
            p2=list->buffer[p2].next;
    list->buffer[p2].next=point;
    list->buffer[point].next=-1;
}
void delete_head(List *list)
{
    if (list->head!=-1)
    {
        if (list->buffer[list->head].next ==-1)
        {
            mark_free(list,list->head);
            list->head=-1; 
        }
        else
        {
            int point=list->head;
            list->head=list->buffer[list->head].next;
            mark_free(list,point);
        }
    }
}
int find_pow(List *list, int pow)
{
    if (list->head==-1) 
            return -1;
    int p=list->head;
    while (p!=-1)
    {
        if (list->buffer[p].pow == pow)
            return p;
        p=list->buffer[p].next;
    }
    return -1;
}
int find_prev(struct List *list, int point)
{
    if (list->head==point)
        return -1;
    else
    {
        int p2=list->head;
        while (list->buffer[p2].next != point)
            p2=list->buffer[p2].next;
        return p2;
    }
}
void delete_elem(struct List *list, int point) 
{
    int pred = find_prev(list,point);
    if (pred==-1)
        delete_head(list);
    else
    {
        list->buffer[pred].next=list->buffer[point].next;
        mark_free (list,point);
    }
}
void format(struct List *list)
{
    int elem1 = list->head;
    int elem2 = list->buffer[elem1].next;
    while (elem1!=-1)
    {
        elem2 = list->buffer[elem1].next;
        while (elem2!=-1)
        {
            if (list->buffer[elem1].pow > list->buffer[elem2].pow)
            {
                int vrn = list->buffer[elem1].num;
                int vrp = list->buffer[elem1].pow;
                list->buffer[elem1].num = list->buffer[elem2].num;
                list->buffer[elem1].pow = list->buffer[elem2].pow;
                list->buffer[elem2].num = vrn;
                list->buffer[elem2].pow = vrp;
            }
            elem2 = list->buffer[elem2].next;
        }
        elem1 = list->buffer[elem1].next;
    }
    elem1 = list->head;
    while (elem1!=-1)
    {
        if (list->buffer[elem1].pow == list->buffer[list->buffer[elem1].next].pow)
        {
            list->buffer[elem1].num = list->buffer[elem1].num + list->buffer[list->buffer[elem1].next].num;
            delete_elem(list, list->buffer[elem1].next);
        }
        else
            elem1 = list->buffer[elem1].next;
    }
}
void read_elems(struct List *list)
{
    int n;
    int p;
    printf("Num: ");
    scanf("%i",&n);
    printf("Power: ");
    scanf("%i",&p);
    while (n!=0 )
    {
        add_elem(list,n,p);
        printf("\nNum: ");
        scanf("%i",&n);
        printf("Power: ");
        scanf("%i",&p);
    }
    format(list);
    printf("\n---------------------------------------\n");
}
int equal(struct List *list1, struct List *list2)
{
    int elem1 = list1->head;
    int elem2 = list2->head;
    if (get_size(list1) != get_size(list2))
        return 0;
    else
    {
        while (elem1 != -1)
        {
            if (list1->buffer[elem1].num == list2->buffer[elem2].num &&
                list1->buffer[elem1].pow == list2->buffer[elem2].pow)
            {
                elem1=list1->buffer[elem1].next;
                elem2=list2->buffer[elem2].next;
            }
            else
                return 0;
        }
        return 1;
    }
}
int main()
{
    struct List list1;
    struct List list2;
    init_list(&list1);
    init_list(&list2);
    read_elems(&list1);
    read_elems(&list2);
    print_list(&list1);
    print_list(&list2);
    if (equal(&list1, &list2))
        printf("Polinoms are equal\n");
    else
        printf("Polinoms are not equal\n");
    return 0;
}