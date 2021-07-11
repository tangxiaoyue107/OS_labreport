#include <stdio.h>
#include <stdlib.h>
//不带头节点的单链表
typedef int datatype;
typedef struct link_node
{
    datatype info;
    struct link_node *next;
}node;
typedef node *linklist;
//链表初始化
node *init()
{
    return NULL;
}
//查找值为x的结点的索引
node *find(node *head,int i)
{
    int j=1;
    node *p=head;
    if(i<1) return NULL;
    while(p&&i!=j)
    {
        p=p->next;
        j++;
    }
    return p;
}
//打印各个单链表的值
void display(node *head)
{
    node *p;
    p=head;
    if(!p) printf("\n单链表是空的！");
    else
    {
        printf("\n单链表各个结点的值是：\n");
        while(p)
        {
            printf("%5d",p->info);
            p=p->next;
        }
    }
}

//查找值为x的某个节点
int selectLink(linklist p,int x)
{
    linklist t=p;
    int i=1;
    while(t->next){
        t=t->next;
        if(t->info==x){
            return i;
        }
        i++;
    }
    return -1;
}
//插入值为x在链表的第i的位置
node *insert(node *head,datatype x,int i)
{
    node *p,*q;
    q=find(head,i);
    //printf("i=%d",i);
    if(!q&&i!=0)
    {

        printf("\n找不到第%d个结点，不能插入%d!",i,x);
    }
    else
    {
        p=(node*)malloc(sizeof(node));
        p->info=x;
        if(i==0)
        {
            p->next=head;
            head=p;
        }
        else
        {
            p->next=q->next;
            q->next=p;
        }
    }
    return head;
}
//删除值为x的结点
node *dele(node *head,datatype x)
{
    node *pre=NULL,*p;
    if(!head)
    {
        printf("单链表是空的！");
        return head;
    }
    p=head;
    while(p&&p->info!=x)
    {
        pre=p;
        p=p->next;
    }
    if(p)
    {
        if(!pre) head=head->next;
        else pre->next=p->next;
        free(p);
    }
    return head;
}
//头插
linklist creatbystack()
{
    linklist head,s;
    datatype x;
    head=NULL;
    printf("请输入若干整数序列：\n");
    scanf("%d",&x);
    while(x!=0)
    {
        s=(linklist)malloc(sizeof(node));
        s->info=x;
        s->next=head;
        head=s;
    }
    return head;
}
//尾插
linklist creatbyqueue()
{
    linklist head,r,s;
    datatype x;
    head=r=NULL;
    printf("请输入若干整数数列：\n");
    scanf("%d",&x);
    while(x!=0)
    {
        s=(linklist)malloc(sizeof(node));
        s->info=x;
        if(head==NULL) head=s;
        else r->next=s;
        r=s;
        scanf("%d",&x);
    }
    if(r) r->next=NULL;
    return head;
}

//链式队列的删除
void delList(linklist head)
{
    linklist p=head;
    while(p)
    {
        head=p->next;
        free(p);
        p=head;
    }
}
//排序
linklist Listsort(linklist head)
{
    linklist p,q;
    int t;
    p=head;
    while(p)
    {
        q=p->next;
        while(q)
        {
            if(p->info > q->info){
                t=p->info;
                p->info=q->info;
                q->info=t;
            }
            q=q->next;
        }
        p=p->next;
    }
    return head;
}



int main()
{
    node *head;
    int x,num,index,m,adress;
    head = init();
    head = creatbyqueue();
    display(head);
    printf("\n请输入想要查找的元素：");
    scanf("%d",&m);
    adress=selectLink(head,m);
    if(adress==-1)
        printf("没有该元素。\n");
    else
        printf("元素%d的位置为：%d\n",m,adress);
    printf("\n请输入你要删除的结点的值：");
    scanf("%d",&x);
    head = dele(head,x);
    display(head);
    printf("\n请输入你要插入结点的值和位置：");
    scanf("%d %d",&num,&index);
    head = insert(head,num,index);
    display(head);
    printf("\n对此链表进行排序：");
    head = Listsort(head);
    display(head);
    getch();
    return 0;
}
