#include <stdio.h>
#include <stdlib.h>
#include "01.h"
//函数声明
queue *input(queue *cc);
queue *insert(queue *cc,node *x);
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
    printf("请输入进程数：\t");
    scanf("%d",&num);//读入进程数量
    printf("请输入%d个进程的：\n",num);
    printf("ID号 名字 到达时间 执行时间（分钟） ：\n");
    while(num!=0)
    {
        node *onejincheng = (node *)malloc(sizeof(node));
        scanf("%d %s %d:%d %d",&onejincheng->id,onejincheng->name,&onejincheng->arrive.hour,&onejincheng->arrive.min,&onejincheng->zx);
        onejincheng->next=NULL;
        cc = insert(cc,onejincheng);
        num--;
    }
    return cc;

}
//插入队列
queue *insert(queue *cc,node *x)
{
    if(cc->front==NULL) cc->front=cc->rear=x;//如果位第一个插入，队列为空
    else//当队列不为空
    {
        node *p = cc->front;
        node *pre = NULL;
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
//删除进程
queue *dele(queue *cc)
{
    if(cc->rear==NULL) printf("队列为空！\n");
    else
    {
        node *x;
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
//进程运行
void fcfs(queue *cc)
{
    node *p=cc->front;
    node *pre=NULL;
    while(p)
    {
        if(!pre)//假设p为第一个进程
        {
            p->start.hour = p->arrive.hour;//p的到达时间就是p的开始时间
            p->start.min = p->arrive.min;
            p->finish.hour = (p->start.hour*60+p->start.min + p->zx)/60;//p的结束时间就是开始时间+执行时间
            p->finish.min = (p->start.hour*60+p->start.min + p->zx)%60;
            p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;//p的周转时间
            p->zzxs = p->zz / p->zx;//p的周转系数
            pre=p; //p和pre移动进入下一次循环
            p=p->next;
        }
        else//不是第一个进程
        {
            if((p->arrive.hour*60+p->arrive.min)>=pre->finish.hour*60+pre->finish.min)
            //如果p的到达时间大于前一个进程的结束时间
            {
                p->start = p->arrive;//p的开始时间就是p的到达时间
            }
            else
            {
                p->start = pre->finish;//p的开始时间是上一个进程的结束时间
            }
            p->finish.hour = (p->start.hour*60+p->start.min+ p->zx)/60;
            p->finish.min = (p->start.hour*60+p->start.min+p->zx)%60;
            p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;
            p->zzxs = p->zz/p->zx;
            pre=p;
            p=p->next;
        }
    }
}
//输出进程
void output(queue *cc)
{
    node *p;
    p=cc->front;
    float sum_zz = 0;
    float sum_zzxs=0;
    int total = 0;
    printf("\n模拟进程FCFS调度过程输出结果：\n");
    printf("ID号\t名字 到达时间 执行时间(分钟)  开始时间 完成时间 周转时间（分钟）带权周转时间（系数）：\n");
    while(p)
    {
        printf("%d\t",p->id);
        printf("%s\t",p->name);
        printf("%2d:%2d",p->arrive.hour,p->arrive.min);
        printf("\t");
        printf("%d（分钟）\t",p->zx);
        printf("%2d:%2d\t",p->start.hour,p->start.min);
        printf("%2d:%2d\t",p->finish.hour,p->finish.min);
        printf("%d（分钟）\t",p->zz);
        printf("%.2f",p->zzxs);
        printf("\n");
        sum_zz = sum_zz +p->zz;
        sum_zzxs = sum_zzxs + p->zzxs;
        total++;
        p=p->next;
    }
    printf("系统的平均周转时间为：\t\t\t\t\t%.2f（分钟）\n",sum_zz/total);
    printf("系统的带权平均周转时间为：\t\t\t\t\t\t%.2f",sum_zzxs/total);

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
5001 p1 9:40 20
5004 p4 10:10 10
5005 p5 10:05 30
5002 p2 9:55 15
5003 p3 9:45 25
*/

/*node *p,*pre;//整个cc序列的遍历指针
    node *reastart,*reaend;//就绪队列的首尾以及就绪队列中reastart的前一个地址的前一个地址
    p=cc->front;
    pre=NULL;
    if(!pre)//处理第一个进程，第一个进程无需竞争，所以到达时间最早的，也就是cc->front第一个开始运行
    {
        p->start.hour = p->arrive.hour;
        p->start.min = p->arrive.min;
        p->finish.hour = (p->arrive.hour*60+p->arrive.min)/60;
        p->finish.min = (p->arrive.hour*60+p->arrive.min)%60;
        p->zz = p->finish.hour*60+p->finish.min-p->arrive.hour*60-p->arrive.min;
        p->zzxs = p->zz*1.0/p->zx;
        pre=p;
        p=p->next;
    }
    while(p)//当p指向的不是第一个，就要考虑就绪队列中的优先级问题
    {
        reastart = p;//就绪队列的首指针为p
        reaend = p;
        while(reaend->next && (reaend->arrive.hour*60+reaend->arrive.min)<=(pre->finish.hour*60+pre->finish.min))//找到就绪序列的尾指针
        {//如果realend->next存在且开始时间小于上一个结束时间就算在就绪序列中

                   reaend = reaend->next;
        }






        //找到就绪序列最大的那个good地址为temp
        node *pxulie=reastart;//记录遍历就绪序列的指针pxulie
        node *prexulie=pre;//就绪序列的reastart前一个结点的地址为pre
        node *temppre;//记录最大的good的地址前一个结点地址
        node *temp;//记录最大的good的地址
        while(pxulie->next) //如果pxulie的下一个指针存在
        {
            if(pxulie->good<pxulie->next->good)//比较二者的good
            {
                temppre = pxulie;//记录最大的good的地址前一个结点地址
                temp=pxulie->next;//记录最大的good的地址
            }
            prexulie =pxulie;//移动
            pxulie=pxulie->next;//移动
        }
        //整个序列遍历了一遍，找到了最大good结点地址temp
        //将temp地址放到地址第一个
        temppre->next = temp->next;
        temp->next = reastart;
        pre->next = temp;
        p=temp;//将temp设为这一轮的p

云 21:14:28
    node *p,*pre;//整个cc序列的遍历指针
    node *reastart,*reaend;//就绪队列的首尾以及就绪队列中reastart的前一个地址的前一个地址
    p=cc->front;
    pre=NULL;
    if(!pre)//处理第一个进程，第一个进程无需竞争，所以到达时间最早的，也就是cc->front第一个开始运行
    {
        p->start.hour = p->arrive.hour;
        p->start.min = p->arrive.min;
        p->finish.hour = (p->arrive.hour*60+p->arrive.min)/60;
        p->finish.min = (p->arrive.hour*60+p->arrive.min)%60;
        p->zz = p->finish.hour*60+p->finish.min-p->arrive.hour*60-p->arrive.min;
        p->zzxs = p->zz*1.0/p->zx;
        pre=p;
        p=p->next;
    }
    while(p)//当p指向的不是第一个，就要考虑就绪队列中的优先级问题
    {
        reastart = p;//就绪队列的首指针为p
        reaend = p;
        while(reaend->next)//找到就绪序列的尾指针
        {
            if((reaend->arrive.hour*60+reaend->arrive.min)<=(pre->finish.hour*60+pre->finish.min))//如果开始时间小于上一个结束时间就算在就绪序列中
               {
                   reaend = reaend->next;
               }
        }
        //找到就绪序列最大的那个good地址为temp
        node *pxulie=reastart;//记录遍历就绪序列的指针pxulie
        node *prexulie=pre;//就绪序列的reastart前一个结点的地址为pre
        node *temppre;//记录最大的good的地址前一个结点地址
        node *temp;//记录最大的good的地址
        while(pxulie->next) //如果pxulie的下一个指针存在
        {
            if(pxulie->good<pxulie->next->good)//比较二者的good
            {
                temppre = pxulie;//记录最大的good的地址前一个结点地址
                temp=pxulie->next;//记录最大的good的地址
            }
            prexulie =pxulie;//移动
            pxulie=pxulie->next;//移动
        }
        //整个序列遍历了一遍，找到了最大good结点地址temp
        //将temp地址放到地址第一个
        temppre->next = temp->next;
        temp->next = reastart;
        pre->next = temp;

        p=temp;//将temp设为这一轮的p
        if((p->arrive.hour*60+p->arrive.min)>=pre->finish.hour*60+pre->finish.min)
            //如果p的到达时间大于前一个进程的结束时间
            {
                p->start = p->arrive;//p的开始时间就是p的到达时间
            }
            else
            {
                p->start = pre->finish;//p的开始时间是上一个进程的结束时间
            }
            p->finish.hour = (p->start.hour*60+p->start.min+ p->zx)/60;
            p->finish.min = (p->start.hour*60+p->start.min+p->zx)%60;
            p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;
            p->zzxs = p->zz/p->zx;
            pre=p;
            p=p->next;
        pre=p;
        p=p->next;
    }








        if((p->arrive.hour*60+p->arrive.min)>=pre->finish.hour*60+pre->finish.min)
        //如果p的到达时间大于前一个进程的结束时间
        {
            p->start = p->arrive;//p的开始时间就是p的到达时间
        }
        else
        {
            p->start = pre->finish;//p的开始时间是上一个进程的结束时间
        }

        p->finish.hour = (p->start.hour*60+p->start.min+ p->zx)/60;
        p->finish.min = (p->start.hour*60+p->start.min+p->zx)%60;
        p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;
        p->zzxs = (p->zz)*1.0/(p->zx);
        pre=p;
        p=p->next;
    }


    */

