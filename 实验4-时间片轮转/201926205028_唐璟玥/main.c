#include <stdio.h>
#include <stdlib.h>

//时间结构体
typedef struct data
{
    int hour;
    int min;
}time;
//进程结构体
typedef struct link_node
{
    int id;//编号
    char name[20];//进程名
    time arrive;//到达就绪队列时间
    int zx;//执行时间
    time start;//开始时间
    time first;//首次开始时间
    int have_finished;//已完成时间
    time arr;//每轮到达时间
    time finish;//最终完成时间
    int zz;//周转时间=完成时间-到达就绪队列时间
    float zzxs;//带权周转系数=周转时间/执行时间
    int flag;//是否结束
    struct link_node *next;
}node;
//队列
typedef struct
{
    node *front;
    node *rear;
}queue;
//队列初始化
queue *init()
{
    queue *cc;
    cc=(queue *)malloc(sizeof(queue));
    cc->front=NULL;
    cc->rear=NULL;
    return cc;
}
//插入进程
queue *insert(queue *cc,node *x)
{
    node *p;
    if(cc->front==NULL)
    {
        cc->front=cc->rear=x;
        return cc;
    }
    else if((x->arrive.hour<cc->front->arrive.hour)||((x->arrive.hour==cc->front->arrive.hour)&&(x->arrive.min<cc->front->arrive.min)))
    {
        x->next=cc->front;
        cc->front=x;
        return cc;
    }
    else
    {
        p=cc->front;
        if((p->next)&&((x->arrive.hour>p->next->arrive.hour)||((x->arrive.hour==p->next->arrive.hour)&&(x->arrive.min>p->next->arrive.min))))
            p=p->next;
        if(p->next==NULL)
        {
            p->next=x;
            cc->rear =x;
            return cc;
        }
        else
        {
            x->next=p->next;
            p->next=x;
            return cc;
        }
    }
}

queue *input(queue *cc)
{
    printf("请输入进程数：");
    int n;
    scanf(" %d",&n);
    printf("请输入%d个进程的：",n);
    printf("ID号	名字	到达时间  执行时间（分钟）\n");
    int x;
    node *a;
    char m[10];
    while(n--)
    {
        scanf("%d",&x);
        a=(node*)malloc(sizeof(node));
        a->id=x;
        scanf(" %s",&a->name);
        scanf(" %s",&m);
        scanf(" %d",&a->zx);
        a->flag=0;
        a->have_finished=0;
        if(m[1]!=':')
        {
            a->arrive.hour=((m[0]-'0')*10+m[1]-'0');
            a->arrive.min=((m[3]-'0')*10+m[4]-'0');
        }
        else
        {
            a->arrive.hour=(m[0]-'0');
            a->arrive.min=((m[2]-'0')*10+m[3]-'0');
        }
        a->first.hour=0;
        a->next=NULL;
        cc=insert(cc,a);
    }
    return cc;
}


queue *dele(queue *cc)
{
    cc->front=cc->front->next;
    return cc;
}

void shijianpian(queue *cc)
{
    printf("请输入时间片的时间：");
    int t;
    scanf(" %d",&t);
    node *p;
    node *pnext;
    node *ke,*neng;
    int a;
    int n=1;
    p=cc->front;
    p->start.hour =p->arrive.hour ;
    p->start.min =p->arrive.min ;
    pnext=p;
    p->first.hour=p->arrive.hour;
    p->first.min=p->arrive.min;
    p->arr.hour=p->arrive.hour;
    p->arr.min=p->arrive.min;
    while(pnext->next->flag==0)//如果pnext下一个进程还未结束
    {
        p=pnext;
        pnext=p->next;//pnext设置未p的下一个
        if((p->have_finished+t)<p->zx)//如果p的已完成时间加上t还未大于执行时间，那么这一轮的t留给队列的第一个p，之后轮转
        {
            p->have_finished=p->have_finished+t;//p的已完成时间增加t
            a=(p->start.min+t)/60;
            if(!p->first.hour)
            {
                p->first.hour=p->start.hour;
                p->first.min=p->start.min;
            }
            pnext->start.min=(p->start.min+t)%60;//p下一个pnext的每轮开始时间再加上轮转时间t
            pnext->start.hour=a+p->start.hour;
        }
        else//如果p已完成时间加上t大于等于执行时间，说明这一轮时间的t将会留给两个进程。p会在这一轮完成自己的进程，剩余时间再开始pnext的时间片;
        {
            a=p->zx-p->have_finished;//a为p执行完毕，时间片剩下的时间
            pnext->start.min=(p->start.min+a)%60;//pnext下一个的开始时间为p这一轮开始时间加上剩余完成时间
            pnext->start.hour=p->start.hour+(pnext->start.min+a)/60;
            p->finish.min=(p->start.min+a)%60;//p的完成时间为这一轮的开始时间加上剩余时间
            a=(p->start.min+a)/60;
            p->finish.hour=p->start.hour+a;
            p->have_finished=p->zx;//这时候p已经执行完毕，已完成时间变为执行时间
            p->zz=(p->finish.hour-p->arrive.hour)*60+p->finish.min-p->arrive.min;
            p->zzxs=(float)p->zz/p->zx;
            p->flag=1;//flag为1设置这个进程为已结束
        }

        ke=p->next;//表示当前时间片内每轮可打印的结点尾指针
        neng=p->next;//表示当前时间片内每轮可打印的结点首指针
        while(ke->next&&ke->next->flag==0&&(ke->next->arrive.hour<pnext->start.hour||(ke->next->arrive.hour==pnext->start.hour&&ke->next->arrive.min<=pnext->start.min)))
        {
            ke=ke->next;//如果ke指向的结点到达时间早于第二轮pnext的开始时间，则需要进入打印序列就绪
        }
        printf("第%d轮执行和就绪队列结果：\n",n++);
        printf("\n");
        printf("ID号	名字	到达时间  总执行时间（分钟）  当前开始时间  已完成时间（分钟）  剩余完成时间（分钟）\n");
        printf("%02d      %s       %02d:%02d       %02d（分钟）         %02d:%02d          %02d（分钟）          %02d（分钟）\n",p->id,p->name,p->arrive.hour,p->arrive.min,p->zx,p->start.hour,p->start.min,p->have_finished,p->zx-p->have_finished);
        while(neng!=ke)
        {
            printf("%02d      %s       %02d:%02d       %02d（分钟）         00:00          %02d（分钟）          %02d（分钟）\n",neng->id,neng->name,neng->arrive.hour,neng->arrive.min,neng->zx,neng->have_finished,neng->zx-neng->have_finished);
            neng=neng->next;
        }
        printf("%02d      %0s       %02d:%02d       %02d（分钟）         00:00          %02d（分钟）          %02d（分钟）\n",neng->id,neng->name,neng->arrive.hour,neng->arrive.min,neng->zx,neng->have_finished,neng->zx-neng->have_finished);
        printf("\n");

        cc->front=cc->front->next;//时间轮转之后将最顶端的指针往下移一个结点，进行轮转。
        p->next=NULL;//当前结点需要移至序列最后一个结点。等待下几轮时间轮转。
        if(ke->next)
        {
            ke=ke->next;//listend也后移一个，指向当前打印序列的第一个
            neng->next=p;//liststart将指向最后一个结点，也就是上一轮轮完被放到最后的那一个结点。
            p->next=ke;//将整个就绪序列的进行循环，使得时间轮转
        }
        else
        {
            ke->next=p;
        }
    }
    p=pnext;//如果整个就绪序列除最后一个其他都已经轮转完毕，只剩下最后一个p指向的结点flag还未完毕
    while(p->flag==0)//对最后一个进行处理
    {
        if((p->have_finished+t)<p->zx)
        {
            p->have_finished=p->have_finished+t;
        }
        else
        {
            a=p->zx-p->have_finished;
            p->finish.min=(p->start.min+a)%60;
            a=(p->start.min+a)/60;
            p->finish.hour=p->start.hour+a;
            p->have_finished=p->zx;
            p->zz=(p->finish.hour-p->arrive.hour)*60+p->finish.min-p->arrive.min;
            p->zzxs=(float)p->zz/p->zx;
            p->flag=1;
        }
        printf("第%d轮执行和就绪队列结果：\n",n++);
        printf("\n");
        printf("ID号	名字	到达时间  总执行时间（分钟）  当前开始时间  已完成时间（分钟）  剩余完成时间（分钟）\n");
        printf("%02d      %s       %02d:%02d       %02d（分钟）         %02d:%02d          %02d（分钟）          %02d（分钟）\n",p->id,p->name,p->arrive.hour,p->arrive.min,p->zx,p->start.hour,p->start.min,p->have_finished,p->zx-p->have_finished);
        printf("\n");
        if(p->flag==0)
        {
            p->start.min=(p->start.min+t)%60;
            p->start.hour=(p->start.min+t)/60+p->start.hour;
        }
    }
}

void output(queue *cc)
{
    node *p,*pre,*pr,*q;

    p=cc->front;
    q=p;
    pre=p;
    while(pre->next)
    {
        pr=pre;
        pre=pre->next;
    }
    pr->next=NULL;
    cc->front=pre;
    pre->next=p;
    q=cc->front;
    while(p->next)
    {
        pre=p;
        while(pre->next)
        {
            pr=pre;
            pre=pre->next;
        }
        pr->next=NULL;
        q->next=pre;
        pre->next=p;
        q=q->next;
    }

    p=cc->front;
    float x=0;
    float y=0;
    int count=0;
    printf("模拟进程FCFS进度过程输出结果：\n");
    printf("ID号	名字	到达时间  执行时间（分钟） 首次开始时间   完成时间      周转时间（分钟）    带权周转时间（系数）\n");
    while(p)
    {
        printf("%02d     %s       %02d:%02d       %02d               %02d:%02d       %02d:%02d        %02d（分钟）             \t%.2f \n",p->id,p->name,p->arrive.hour,p->arrive.min,p->zx,p->first.hour,p->first.min,p->finish.hour,p->finish.min,p->zz,p->zzxs);
        p=p->next;
    }
    p=cc->front;
    while(p)
    {
        x+=p->zz;
        y+=p->zzxs;
        count+=1;
        p=p->next;
    }
    x=(float)x/count;
    y=(float)y/count;
    printf("系统平均周转时间                                                  \t%.2f\n",x);
    printf("系统平均带权周转时间                                                            \t\t%.2f\n",y);
}

int main()
{
    queue *me;
    me=init();
    me=input(me);
    shijianpian(me);
    output(me);
    getch();
    return 0;
}
/*
5001 p1 9:40 20
5004 p4 10:00 10
5005 p5 10:05 30
5002 p2 9:55 15
5003 p3 9:45 25
*/
