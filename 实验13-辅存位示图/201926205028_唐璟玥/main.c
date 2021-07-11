#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "01.h"

int disksize;//硬盘大小
int wordsize;//字长
int blocksize;//物理块大小
int headnumber;//磁头数
int sectornumber;//扇区数
int cylinder;//每个柱面上的扇区数
int sum;//总扇区数
int availablesector;//空闲扇区数
int map[4096][4096];
int line;
linklist* work = NULL;

//打印
void print()
{
    printf("\t\t******************************辅存使用情况******************************\n");
    printf("%-3c",' ');
    //打印表头
    for(int i=0;i<wordsize;i++)
    {
        printf("%-3d",i);
    }
    putchar('\n');

    int cnt=0;//防止溢出
    for(int i=0;i<line;i++)
    {
        printf("%-3d",i);
        for(int j=0;j<wordsize && cnt<sum;j++)
        {
            printf("%-3d",map[i][j]);
            cnt++;
        }
        putchar('\n');
    }
    printf("辅存剩余空闲块数：%d\n",availablesector);
}
//分配
void allocate()
{
    printf("请输入申请空间的作业名字和需要分配辅存空间的大小（单位：K）：");
    linklist *tmp=(linklist*)malloc(sizeof(linklist));
    scanf("%s %d",&tmp->name,&tmp->size);
    if(tmp->size > availablesector*blocksize)//如果申请空间的大小 大于 现有的空闲空间
    {
        printf("辅存申请失败！\n");
        return ;
    }

    printf("辅存申请成功！\n");
    int cnt=0;
    int k=0;
    int ss=tmp->size/blocksize+(tmp->size%blocksize?1:0);//计算申请空间的需要的物理块数
    for(int i=0;i<line && k<ss;i++)
    {
        for(int j=0;j<wordsize && cnt < sum && k<ss;j++)
        {
            if(map[i][j]==0){
                map[i][j]=1;
                tmp->a[k]=i*wordsize+j;//a数组记录的是物理块序号
                tmp->zihao[k]=i;//字号
                tmp->weihao[k]=j;//位号
                tmp->zhu[k]=(i*wordsize+j)/cylinder;//柱面号
                tmp->citou[k]=(i*wordsize+j)%cylinder/sectornumber;//磁头
                tmp->shanqu[k]=(i*wordsize+j)%cylinder%sectornumber;//扇区
                k++;
                availablesector--;
            }
        }
    }
    print();
    printf("\t\t********************%s被分配的辅存********************\n",tmp->name);
    printf("  序号  块  字  位  柱面号  磁头号  扇区号\n");
    for(int i=0;i<ss;i++){
        printf("%4d  %4d  %4d  %4d  %4d   %4d   %4d\n",i+1,tmp->a[i],tmp->zihao[i],tmp->weihao[i],tmp->zhu[i],tmp->citou[i],tmp->shanqu[i]);
    }
    if(work == NULL){
        work = tmp;
        work->next=NULL;
    }else
    {
        linklist* q=work;
        while(q->next!=NULL) q=q->next;
        q->next=tmp;
        tmp->next=NULL;
    }
}
//回收
void recycle()
{
    linklist* q=work;
    printf("当前分配的作业：");
    while(q){
        printf("%s->",q->name);
        q=q->next;
    }
    putchar('\n');
    printf("要回收的作业名：");
    char name[10];
    scanf("%s",name);
    linklist* pre=work;
    linklist* p=work;
    while(p != NULL && strcmp(p->name,name)!=0){
        pre=p;
        p=p->next;
    }
    if(p==NULL){
        printf("回收失败！\n");
        return;
    }
    printf("回收成功！\n");
    if(pre == p)
        work=p->next;
    else
        pre->next = p->next;
    linklist* tmp=p;
    int ss=tmp->size/blocksize+(tmp->size%blocksize?1:0);
    for(int i=0;i<ss;i++){
        map[tmp->zihao[i]][tmp->weihao[i]]=0;
        availablesector++;
    }
    print();
}


int main()
{
    int flag=1;
    printf("------201926205028 唐璟玥 19级数据科学与大数据技术1班-----\n");
    printf("请输入辅存空间的大小（单位：K）和字长（32 or 64）和块长（单位：K）：");
    scanf("%d %d %d",&disksize,&wordsize,&blocksize);
    printf("请输入该辅存硬盘的磁道数（磁头数）和每个磁道的扇区数：");
    scanf("%d %d",&headnumber,&sectornumber);

    sum=availablesector=disksize/blocksize;
    line=sum/wordsize+(sum%wordsize?1:0);
    cylinder=headnumber*sectornumber;//一个柱面总共有多少扇区

    //初始化
    for(int i=0;i<sum;i+=3){
            map[i/wordsize][i%wordsize] = 1;
            availablesector--;
    }
    print();
    //菜单
    while(flag)
    {
        printf("***************辅存调度管理***************\n");
        printf("      *   1.空间分配               *\n");
        printf("      *   2.空间去配               *\n");
        printf("      *   0.退出                   *\n");
        printf("            请输入选项[ ]\b\b");
        int c;
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                allocate();
                break;
            case 2:
                recycle();
                break;
            case 0:
                flag=0;
                break;
            default:
                printf("error!\n");
                break;
        }
    }
    getch();
    return 0;
}

