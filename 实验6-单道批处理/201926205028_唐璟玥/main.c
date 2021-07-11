#include <stdio.h>
#include <stdlib.h>
#include "01.h"
/*
由于单道 系统中只能存放一个作业，
因此装入系统内存的作业即时完成作业进程的创建并独占系统资源，
从而即刻发生进程调度进入CPU执行。
*/

//函数声明
queue *input(queue *cc);
queue *insert(queue *cc,linklist *x);
queue *dele(queue *cc);
void fcfs(queue *cc);
void output(queue *cc);

//队列初始化
queue *init()
{
    queue *cc;
    cc = (queue *)malloc(sizeof(queue));
    cc->front=NULL;
    cc->rear = NULL;
    return cc;
}
//输入队列
queue *input(queue *cc)
{

    int num;
    printf("请输入你要创建的作业数：\t");
    scanf("%d",&num);//读入进程数量
    printf("请依次输入%d个作业的：\n",num);
    printf("名字 入井时间 运行时间：\n");
    while(num!=0)
    {
        linklist *onejincheng = (linklist *)malloc(sizeof(linklist));
        scanf("%s %d:%d %d",onejincheng->name,&onejincheng->arrive.hour,&onejincheng->arrive.min,&onejincheng->zx);
        onejincheng->next=NULL;
        cc = insert(cc,onejincheng);
        num--;
    }
    return cc;

}
//插入
queue *insert(queue *cc,linklist *x)
{
    if(cc->front==NULL) cc->front=cc->rear=x;//如果位第一个插入，队列为空
    else//当队列不为空
    {
        linklist *p = cc->front;
        linklist *pre = NULL;
        while(p && ((p->arrive.hour)*60+(p->arrive.min))<=((x->arrive.hour)*60+(x->arrive.min)))//将当前结点的时间和x的时间比较大小，如果x时间大则循环比较下一个结点，直到找到比x还大的队列结点
        {
            pre=p;
            p=p->next;
        }
        if(pre==NULL)//如果时间最早是第一个则插入链式队列队首
        {
            x->next = cc->front;
            cc->front = x;
        }
        else//插入到顺序相应时间后
        {
            x->next = p;
            pre->next = x;
        }
    }
    return cc;
}
//删除作业
queue *dele(queue *cc)
{
    if(cc->rear==NULL) printf("队列为空！\n");
    else
    {
        linklist *x;
        x=cc->front;
        cc->front = cc->front->next;
        free(x);
        if(cc->front==NULL)
        {
            cc->rear=NULL;
        }
    }
    return cc;

}
//FCFS运行
void fcfs(queue *cc)
{
    linklist *p=cc->front;
    linklist *pre=NULL;
    while(p)
    {
        if(!pre)//假设p为第一个进程
        {
            p->jobTime.hour = p->arrive.hour;//p的作业到达时间就是p的开始时间
            p->jobTime.min = p->arrive.min;

            p->processTime.hour = p->arrive.hour;//p的进程到达时间就是p的开始时间
            p->processTime.min = p->arrive.min;

            p->finish.hour = (p->jobTime.hour*60+p->jobTime.min + p->zx)/60;//p的结束时间就是开始时间+执行时间
            p->finish.min = (p->jobTime.hour*60+p->jobTime.min + p->zx)%60;

            p->jobWait=0;//第一个进程/作业等待为0
            p->processWait=0;

            p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;//p的周转时间
            p->zzxs = 1.0000*p->zz / p->zx;//p的周转系数

            pre=p; //p和pre移动进入下一次循环
            p=p->next;
        }
        else//不是第一个进程
        {
            if((p->arrive.hour*60+p->arrive.min)>=pre->finish.hour*60+pre->finish.min)
            //如果p的到达时间大于前一个进程的结束时间
            {
                p->jobTime = p->arrive;//p的开始时间就是p的到达时间
                p->processTime = p->jobTime;//单道批处理
            }
            else
            {
                p->jobTime = pre->finish;//p的开始时间是上一个进程的结束时间
                p->processTime = p->jobTime;//单道批处理
            }
            p->finish.hour = (p->jobTime.hour*60+p->jobTime.min+ p->zx)/60;
            p->finish.min = (p->jobTime.hour*60+p->jobTime.min+p->zx)%60;

            p->jobWait = p->jobTime.hour*60+p->jobTime.min-p->arrive.hour*60-p->arrive.min;//作业等待时间
            p->processWait = 0;//单道批处理 一个作业一个进程，无需等待

            p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;
            p->zzxs = 1.0000*p->zz/p->zx;
            pre=p;
            p=p->next;
        }
    }
}
//输出进程
void output(queue *cc)
{
    linklist *p;
    p=cc->front;
    float sum_zz = 0;
    float sum_zzxs=0;
    int total = 0;
    printf("\n模拟作业FCFS调度过程输出结果：\n");
    printf("名字 入井时间 运行时间(分钟)  作业调度时间  作业调度等待时间  进程调度时间  进程调度等待时间   完成时间   周转时间（分钟）  带权周转时间（系数）：\n");
    while(p)
    {
        printf("%s\t",p->name);
        printf("%2d:%2d\t",p->arrive.hour,p->arrive.min);
        printf("%d（分钟）\t",p->zx);
        printf("%2d:%2d\t\t",p->jobTime.hour,p->jobTime.min);
        printf("%d（分钟）\t",p->jobWait);
        printf("%2d:%2d\t\t",p->processTime.hour,p->processTime.min);
        printf("%d（分钟）\t",p->processWait);
        printf("%2d:%2d\t\t",p->finish.hour,p->finish.min);
        printf("%d（分钟）\t",p->zz);
        printf("%.4f（系数）",p->zzxs);
        printf("\n");
        sum_zz = sum_zz +p->zz;
        sum_zzxs = 1.0000*sum_zzxs + p->zzxs;
        total++;
        p=p->next;
    }
    printf("系统的平均周转时间为：%.2f（分钟）\n",sum_zz/total);
    printf("系统的带权平均周转时间为：%.4f",1.0*sum_zzxs/total);

}
int main()
{
    queue *me;
    me=init();
    printf("初始化成功！\n");
    me=input(me);
    fcfs(me);
    output(me);
    getch();
    return 0;
}


/*
测试数据：
JOB1 8:00 120
JOB2 8:50 50
JOB3 9:00 10
JOB4 9:50 20
*/

