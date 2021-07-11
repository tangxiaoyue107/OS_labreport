#include <stdio.h>
#include <stdlib.h>
#include "01.h"
//队列初始化
queue *init();
//插入分区
queue *insertfenqu(queue *cc,node *x);
//删除分区
queue *delefenqu(queue *cc);
//输入分区参数
queue *fenquinput(queue *cc);
//打印分区状态
void fenquoutput(queue *cc);
//插入作业
queue *insertzuoye(queue *aa,job *x);
//输入作业
queue *zuoyeinput(queue *aa);
//打印作业
void zuoyeoutput(queue *aa);
//分配
void fenpei(queue *aa,queue *cc);
//回收
void huishou(queue *cc);


//队列初始化
queue *init()
{
    queue *cc;
    cc=(queue*)malloc(sizeof(queue));
    cc->front=NULL;
    cc->rear=NULL;
    return cc;
}
//插入分区
queue *insertfenqu(queue *cc,node *x)
{
    if(cc->front==NULL)
    {
        cc->front=cc->rear=x;
        return cc;
    }
    else
    {
        node *p=cc->front;
        node *pre=NULL;
        while(p->next)
        {
            pre=p;
            p=p->next;
        }
        //插在队列后面
        p->next=x;
        x->next=NULL;
    }
    return cc;
}
//删除分区
queue *delefenqu(queue *cc)
{
    cc->front=cc->front->next;
    return cc;
}
//输入分区参数
queue *fenquinput(queue *cc)
{
    int num;
    node *onefenqu;
    printf("请输入系统的分区块数：");
    scanf("%d",&num);
    printf("请依次输入：\n分区号 大小 起始\n");
    while(num)
    {
        onefenqu=(node*)malloc(sizeof(node));
        scanf("\t%d\t",&onefenqu->id);
        scanf("%d\t",&onefenqu->size);
        scanf("%d",&onefenqu->address);
        onefenqu->station[0]=0;
        onefenqu->next=NULL;
        cc=insertfenqu(cc,onefenqu);
        num--;
    }
    return cc;
}
//打印分区状态
void fenquoutput(queue *cc)
{
    node *p=cc->front;
    printf("************打印区块信息************\n");
    printf("分区号\t大小<KB> 起始<KB>     状态\n");
    while(p)
    {
        printf("%3d\t",p->id);
        printf("%4d\t",p->size);
        printf("%4d\t\t",p->address);
        if(p->station[0]==0) printf("%d\n",p->station[0]);
        else printf("JOB%d\n",p->station[0]);
        p=p->next;
    }
}
//插入作业
queue *insertzuoye(queue *aa,job *x)
{
    if(aa->front==NULL)
    {
        aa->front=aa->rear=x;
        return aa;
    }
    else
    {
        job *p=aa->front;
        job *pre=NULL;
        while(p->next)
        {
            pre=p;
            p=p->next;
        }
        //插在队列后面
        p->next=x;
        x->next=NULL;
    }
    return aa;
}
//输入作业
queue *zuoyeinput(queue *aa)
{
    int num,x,size;
    job *onefenqu;
    x=1;
    printf("请输入作业个数：");
    scanf("%d",&num);
    printf("请输入这%d个作业的信息：\n",num);
    while(num)
    {
        printf("请输入作业%d的大小：",x);
        onefenqu = (job *)malloc(sizeof(job));
        onefenqu->id = x;
        onefenqu->name = x;
        onefenqu->next=NULL;
        scanf("%d",&size);
        onefenqu->size =size;
        aa = insertzuoye(aa,onefenqu);
        num--;
        x++;
    }
    return aa;
}

//打印作业
void zuoyeoutput(queue *aa)
{
    job *p=aa->front;
    printf("打印各作业的信息：\n");
    printf("作业名\t作业大小\n");
    while(p)
    {
        printf("JOB%d\t",p->name);
        printf("%d\n",p->size);
        p=p->next;
    }
}
//分配
void fenpei(queue *aa,queue *cc)
{
    job *onezuoye = aa->front;
    node *onefenqu = cc->front;
    node *choose=NULL;
    while(onezuoye)
    {
        //printf("先分配JOB%d的内存,它需要内存%d(KB)\n",onezuoye->id,onezuoye->size);
        while(onefenqu)
        {
            //printf("我们先来看分区%d，它有%d(KB)内存\n",onefenqu->id,onefenqu->size);
            if(onefenqu->size>=onezuoye->size && onefenqu->station[0]==0)
            {
                //printf("分区%d够！",onefenqu->id);
                if(choose!=NULL)
                {
                    if(choose->size<onefenqu->size) ;
                    else choose = onefenqu;
                }
                else choose = onefenqu;
                //printf("这一轮choose为分区%d",choose->id);
            }
            onefenqu=onefenqu->next;
        }
        if(choose!=NULL)
        {
            choose->station[0] = onezuoye->id;
        }
        else printf("\nJOB%d无足够空间放入！",onezuoye->id);
        choose=NULL;
        onefenqu = cc->front;
        onezuoye = onezuoye->next;
    }
}
//回收
void huishou(queue *cc)
{
    char flag;
    int id;
    node *onefenqu = cc->front;
    printf("是否需要回收？（y/n）:");
    scanf(" %c",&flag);
    printf("%c",flag);
    while(flag == 'y' || flag == 'Y')
    {
        printf("请输入你要回收的作业名：JOB");
        scanf("%d",&id);

        while(onefenqu)
        {
            if(onefenqu->station[0] == id)
            {
                onefenqu->station[0]=0;
                break;
            }
            onefenqu=onefenqu->next;
        }
        if(onefenqu==NULL)
        {
            printf("没有找到您输入的作业。");
        }
        fenquoutput(cc);
        printf("是否还需要回收？（y/n）:");
        scanf(" %c",&flag);
        onefenqu = cc->front;
    }
}
int main()
{
    queue *cc;
    queue *aa;
    cc=init();
    aa=init();
    cc=fenquinput(cc);
    fenquoutput(cc);
    aa=zuoyeinput(aa);
    zuoyeoutput(aa);
    fenpei(aa,cc);
    fenquoutput(cc);
    huishou(cc);
    getch();
    return 0;

}
/*
    1   12  20
    2   32  32
    3   64  64
    4   128 128
    5   100 256
*/
