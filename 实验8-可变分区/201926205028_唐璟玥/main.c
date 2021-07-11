#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "01.h"
//回收
void recycle_froms(node *head);
//打印已分配和未分配的分区
void print_fenqu(node *head);
//最先适配
void first_allo(node *head);
//最优适配
void good_allo(node *head);
//最坏分配
void bad_allo(node *head);
//分配菜单
void allocate_caidan(node *head);



//回收
void recycle_froms(node *head)
{
    char name[10];
    int flag=0;
    print_fenqu(head);
    printf("请输入回收的作业名:");
    scanf("%s",name);
    node *p=s->next;//从已分配的链表中找到作业名
    node *pre=s;
    while(p)
    {
        if(strcmp(p->flag,name)==0)
        {
            //资源返回
            flag=1;//找到了作业
            printf("找到啦！\n");
            node *t=(node*)malloc(sizeof(node));
            t->address=p->address;

            t->size=p->size;
            t->next=NULL;

            node *q=head->next;
            node *pre_q=head;//未分配
            pre_q->address=0;
            pre_q->size=0;
            if(!head->next)
            {
                strcpy(t->flag,"空闲");
                head->next=t;
                pre->next=p->next;//已分配的表中要释放掉已回收到未分配区的结点
                free(p);
                printf("回收成功!\n");
                break;
            }

            while(q)
            {
                printf("11");
                if(pre_q->address+pre_q->size < t->address && t->address+t->size < q->address)//上下都没有回收区
                {
                    printf("上下都没有回收区\n");
                    pre_q->next=t;
                    t->next=q;
                    strcpy(t->flag,"空闲");
                    break;
                }
                else if(pre_q->address+pre_q->size == t->address && t->address+t->size < q->address)//上有空闲区，下没有
                {
                    printf("上有空闲区，下没有\n");
                    pre_q->size=pre_q->size+t->size;
                    free(t);
                    break;
                }
                else if(pre_q->address+pre_q->size < t->address && t->address+t->size == q->address)//下有空闲区，上没有
                {
                    printf("下有空闲区，上没\n");
                    q->size=q->size+t->size;
                    q->address = q->address-t->size;
                    free(t);
                    break;
                }
                else if(pre_q->address+pre_q->size == t->address && t->address+t->size == q->address)//上下都有空闲区
                {
                    printf("上下都有回收区\n");
                    pre_q->size=pre_q->size+t->size+q->size;
                    if(q->next)//如果q的next不是NULL，p不是最后一个
                        pre_q->next=q->next;
                    else//如果p是最后一个
                        pre_q->next=NULL;
                }
                pre_q=q;
                q=q->next;
            }
            if(q==NULL)
            {
                strcpy(t->flag,"空闲");
                pre_q->next=t;
            }
            pre->next=p->next;//已分配的表中要释放掉已回收到未分配区的结点
            free(p);
            printf("回收成功!\n");
            break;
        }
        pre=p;
        p=p->next;
    }
    if(flag==0)
    {
        printf("不存在%s作业",name);
    }
    print_fenqu(head);
}

//打印已分配和未分配的分区
void print_fenqu(node *head)
{
    int i=1;
    printf("\n*********************主存分配情况*********************\n");
    printf("——————已分配:——————\n");
    printf("分区号\t大小（KB）\t起始（KB）\t状态\n");
    node *q=s->next;
    while(q)
    {
        printf("%d\t %d\t\t%d\t\t%s\n",i,q->size,q->address,q->flag);
        i++;
        q=q->next;
    }

    printf("——————未分配:——————\n");
    printf("分区号\t大小（KB）\t起始（KB）\t状态\n");
    node *p=head->next;
    while(p)
    {
        printf("%d\t %d\t\t%d\t\t%s\n",i,p->size,p->address,p->flag);
        i++;
        p=p->next;
    }
}
//最先适配
void first_allo(node *head)
{
    char name[10];
    int size;
    print_fenqu(head);
    printf("请输入作业名:");
    scanf("%s",name);
    printf("请输入%s需要分配的主存大小（单位:KB）:");
    scanf("%d",&size);

    node *p=head->next;//未分配
    node *pre =head;
    node *q= s->next;//已分配
    node *pre_q =s;
    int flag=1;
    while(p)//如果未分配的内存还存在内存，循环查找符合内存大小的分区表（最先适配）
    {
        if(p->size==size)//如果输入进程内存==未分配内存的大小
        {
            node *t=(node *)malloc(sizeof(node));//创建一个Node 输入内存信息
            //最先分配
            t->address=p->address;//地址
            t->size=p->size;//大小
            strcpy(t->flag,name);//作业名
            while(q&&q->address < t->address)//找到地址从小大的内存地点排序，插入
            {
                pre_q=q;
                q=q->next;
            }
            if(q!=NULL)//如果q存在，说明pre_q不是最后一个
            {
                pre_q->next=t;//插入t，已分配新结点
                t->next=q;
            }
            else//pre_q是最后一个
            {
                pre_q->next=t;
                t->next=NULL;
            }
            pre->next=p->next;//释放掉未分配内存中的已分配结点p
            free(p);
            printf("分配成功!\n");
            flag=0;
            break;
        }
        else if(p->size > size)//如果输入进程内存<未分配内存中其中之一
        {
            node *t=(node *)malloc(sizeof(node));
            t->address=p->address;//起始地址
            t->size=size;//大小
            strcpy(t->flag,name);//作业名
            while(q&&q->address < t->address)
            {
                pre_q=q;//找到已分配分区表的内存起始地址从小到大排序位置
                q=q->next;
            }
            if(q)
            {
                pre_q->next=t;
                t->next=q;
            }
            else
            {
                pre_q->next=t;
                t->next=NULL;
            }
            p->size=p->size-size;//p的大小变小
            p->address=p->address+size;//p的地址改变
            printf("分配成功!\n");
            flag=0;
            break;
        }
        pre=p;
        p=p->next;
    }
    if(flag==1)
    {
        printf("分配失败!\n");
    }
    print_fenqu(head);
}
//最优适配
void good_allo(node *head)
{
    char name[10];
    int size;
    print_fenqu(head);
    printf("请输入作业名:");
    scanf("%s",name);
    printf("请输入%s需要分配的主存大小（单位:KB）:");
    scanf("%d",&size);

    node *p=head->next;
    node *pre =head;
    node *q= s->next;
    node *pre_q =s;
    //寻找最适合最小的内存空间
    node *min_p=(node *)malloc(sizeof(node));
    node *min_pre=head;
    min_p->size=99999;
    int flag=1;
    while(p)
    {
        if(p->size>=size&&p->size<min_p->size)//如果在循环的过程中，找到比输入进程大小大且长度更适合（小）的就修改Min_pre min_p
        {
            min_pre=pre;
            min_p=p;
        }
        pre=p;
        p=p->next;
    }
    if(min_p->size==size)
    {
        node *t=(node *)malloc(sizeof(node));
        t->address=min_p->address;
        t->size=min_p->size;
        strcpy(t->flag,name);
        while(q&&q->address < t->address)
        {
            pre_q=q;
            q=q->next;
        }
        if(q)
        {
            pre_q->next=t;
            t->next=q;
        }
        else
        {
            pre_q->next=t;
            t->next=NULL;
        }
        min_pre->next=min_p->next;
        free(min_p);
        printf("分配成功!\n");
        flag=0;
    }
    else if(min_p->size > size)
    {
        node *t=(node *)malloc(sizeof(node));
        t->address=min_p->address;
        t->size=size;
        strcpy(t->flag,name);
        while(q&&q->address < t->address)
        {
            pre_q=q;
            q=q->next;
        }
        if(q)
        {
            pre_q->next=t;
            t->next=q;
        }
        else
        {
            pre_q->next=t;
            t->next=NULL;
        }
        min_p->size=min_p->size-size;
        min_p->address=min_p->address+size;
        printf("分配成功!\n");
        flag=0;
    }
    if(flag==1)
        printf("分配失败!\n");
    print_fenqu(head);
}
//最坏分配
void bad_allo(node *head)
{
    char name[10];
    int size;
    print_fenqu(head);
    printf("请输入作业名:");
    scanf("%s",name);
    printf("请输入%s需要分配的主存大小（单位:KB）:");
    scanf("%d",&size);

    node *p=head->next;
    node *pre =head;
    node *q= s->next;
    node *pre_q =s;

    node *max_p=(node *)malloc(sizeof(node));//如果在循环的过程中，找到比输入进程大小大且长度更适合（大）的就修改max_pre max_p
    node *max_pre=head;
    max_p->size=0;
    int flag=1;
    while(p)
    {
        if(p->size>=size&&p->size>max_p->size)
        {
            max_pre=pre;
            max_p=p;
        }
        pre=p;
        p=p->next;
    }
    if(max_p->size==size)
    {
        node *t=(node *)malloc(sizeof(node));
        t->address=max_p->address;
        t->size=max_p->size;
        strcpy(t->flag,name);
        while(q&&q->address < t->address)
        {
            pre_q=q;
            q=q->next;
        }
        if(q)
        {
            pre_q->next=t;
            t->next=q;
        }
        else
        {
            pre_q->next=t;
            t->next=NULL;
        }
        max_pre->next=max_p->next;
        free(max_p);
        printf("分配成功!\n");
        flag=0;
    }
    else if(max_p->size > size)
    {
        node *t=(node *)malloc(sizeof(node));
        t->address=max_p->address;
        t->size=size;
        strcpy(t->flag,name);
        while(q&&q->address < t->address)
        {
            pre_q=q;
            q=q->next;
        }
        if(q)
        {
            pre_q->next=t;
            t->next=q;
        }
        else
        {
            pre_q->next=t;
            t->next=NULL;
        }
        max_p->size=max_p->size-size;
        max_p->address=max_p->address+size;
        printf("分配成功!\n");
        flag=0;
    }
    if(flag==1)
        printf("分配失败!\n");
    print_fenqu(head);
}
//分配菜单
void allocate_caidan(node *head)
{
    int choose;
    printf("*********分配算法**********\n");
    printf("   *     1.最先分配算法      *   \n");
    printf("   *     2.最优分配算法      *   \n");
    printf("   *     3.最坏分配算法      *   \n");
    printf("         请输入选项[ ]\b\b");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:
            printf("1.最先分配法\n");
            first_allo(head);
            break;
        case 2:
            printf("2.最优分配法\n");
            good_allo(head);
            break;
        case 3:
            printf("3.最坏分配法\n");
            bad_allo(head);
            break;
        }
}

int main()
{
    int choose;
    node *newnode = (node*)malloc(sizeof(node));
    head = (node *)malloc(sizeof(node));
    head->next = NULL;
    s=(node *)malloc(sizeof(node));//s指向已分配分区表
    s->next=NULL;

    printf("请输入内存地址总量:");
    scanf("%d",&newnode->size);
    printf("请输入起始地址大小为:");
    scanf("%d",&newnode->address);
    strcpy(newnode->flag,"空闲");
    newnode->next = NULL;
    head->next=newnode;

    while(1)
    {
        printf("*********可变分区管理**********\n");
        printf("   *     1.内存分配      *   \n");
        printf("   *     2.内存去配      *   \n");
        printf("   *     0.退出          *   \n");
        printf("         请输入选项[ ]\b\b");
        scanf("%d",&choose);
        switch(choose)
        {
            case 1:
                printf("1.内存分配\n");
                allocate_caidan(head);
                break;
            case 2:
                printf("2.内存去配\n");
                recycle_froms(head);
                break;
            case 0:
                printf("0.退出\n");
                return 0;
            }
    }
    return 0;
}
