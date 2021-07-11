#include <stdio.h>
#include <stdlib.h>
#include "01.h"
//函数声明
queue *input(queue *cc);
queue *insert(queue *cc,node *x);
queue *dele(queue *cc);
void youxian(queue *cc);
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
    printf("ID号 名字 优先级 到达时间 执行时间（分钟） ：\n");
    while(num!=0)
    {
        node *onejincheng = (node *)malloc(sizeof(node));
        scanf("%d %s %d %d:%d %d",&onejincheng->id,onejincheng->name,&onejincheng->good,&onejincheng->arrive.hour,&onejincheng->arrive.min,&onejincheng->zx);
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
        int ptime = (p->arrive.hour)*60+(p->arrive.min);
        int xtime = (x->arrive.hour)*60+(x->arrive.min);
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
void youxian(queue *cc)
{
    node *p,*pre;//整个cc序列的遍历指针
    node *reastart,*reaend;//就绪队列的首尾
    p=cc->front;
    pre=NULL;
    //第一个到达的进程不必考虑优先级
    if(!pre)
    {
        p->start.hour=p->arrive.hour;
        p->start.min=p->arrive.min;
        p->finish.hour=p->start.hour+(p->arrive.min+p->zx)/60;
        p->finish.min=(p->arrive.min+p->zx)%60;
        p->zz=p->finish.hour*60+p->finish.min-p->arrive.hour*60-p->arrive.min;
        p->zzxs=(p->zz)*1.0/(p->zx);//如果不*1.0则会得到zzxs的小数都为.00
        pre=p;
        p=p->next;
    }
    while(p)//当p指向的不是第一个，就要考虑就绪队列中的优先级问题
    {

            int title = 1;//设置循环的标志为1
            reastart=p;//就绪队列的首指针为p
            reaend=p; // 就绪序列的最后一个进程
            while(reaend->next && (reaend->arrive.hour*60+reaend->arrive.min)<=(pre->finish.hour*60+pre->finish.min))//找到就绪序列的尾指针
            {//如果realend->next存在且开始时间小于上一个结束时间就算在就绪序列中，//找到就绪序列的尾指针

                reaend = reaend->next;
            }
            while(title == 1)  // 在就绪队列中冒泡排序，将最大的优先级排在最前面，最小的优先级排在最后面
            {
                title=0;//初始为0
                reastart=p;
                while(reastart!=reaend)//如果reastart指针不等于reaend即就绪序列还存在一个以上结点
                {
                    if(reastart->good<reastart->next->good)//比较二者的good，如果后面的good大于前面的Good
                    {
                        // 交换节点内部信息的id
                        int data;
                        data=reastart->id;
                        reastart->id=reastart->next->id;
                        reastart->next->id=data;
                        // 交换节点内部信息的名字
                        for(int i=0; i<20; i++)
                        {
                            char namec;
                            namec=reastart->name[i];
                            reastart->name[i]=reastart->next->name[i];
                            reastart->next->name[i]=namec;
                        }
                        // 交换节点内部信息的good
                        data=reastart->good;
                        reastart->good=reastart->next->good;
                        reastart->next->good=data;
                        // 交换节点内部信息的arrive
                        data=reastart->arrive.hour;
                        reastart->arrive.hour=reastart->next->arrive.hour;
                        reastart->next->arrive.hour=data;

                        data=reastart->arrive.min;
                        reastart->arrive.min=reastart->next->arrive.min;
                        reastart->next->arrive.min=data;
                        // 交换节点内部信息的zx
                        data=reastart->zx;
                        reastart->zx=reastart->next->zx;
                        reastart->next->zx=data;
                        //如果有交换说明需要进行下一次循环，在下一次循环中判断是否不需要冒泡排序了
                        title = 1;
                    }
                    reastart=reastart->next;//reastart后移一位，一轮内进行good的比较。
                }
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
    printf("ID号\t名字\t优先级 到达时间 执行时间(分钟)  开始时间 完成时间 周转时间（分钟）带权周转时间（系数）：\n");
    while(p)
    {
        printf("%d\t",p->id);
        printf("%s\t",p->name);
        printf("%d\t",p->good);
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
    printf("系统的平均周转时间为：\t\t\t\t\t\t%.2f（分钟）\n",sum_zz/total);
    printf("系统的带权平均周转时间为：\t\t\t\t\t\t\t%.2f",sum_zzxs/total);

}
int main()
{
    queue *me;
    me=init();
    printf("初始化成功！\n");
    me=input(me);
    youxian(me);
    output(me);
    getch();
    return 0;
}


/*
测试数据：
5001 p1 1 9:40  20
5004 p4 4 10:10 10
5005 p5 3 10:05 30
5002 p2 3 9:55  15
5003 p3 2 9:45  25
*/
