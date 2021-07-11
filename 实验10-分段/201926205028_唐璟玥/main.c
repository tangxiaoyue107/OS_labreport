#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "01.h"
node* initMemory();// 初始化内存空间
void allocate(node *head);//分配菜单
void goodAllocation(node* head,int size,char c[10]);
void badAllocation(node* head,int size,char c[10]);
void firstAllocation(node* head,int size,char c[10]);
void print(node* head);//打印主存 已分配未分配的分区表情况
void reorder(node* head);//修改id
void recyle(node* head);//回收

// 初始化内存空间
node* initMemory()
{
    //带头节点，head指向的是空闲分区表
    node* head=(node*)malloc(sizeof(node));
    head->next = NULL;
    node* q=(node*)malloc(sizeof(node));
    printf("请输入内存大小：");
    scanf("%d",&memory.size);
    printf("请输入起始地址：");
    scanf("%d",&memory.address);
    q->id=1;
    q->size=memory.size;
    q->address=memory.address;
    strcpy(q->flag,"空闲");
    q->next=NULL;
    head->next=q;
    return head;
}
//分配菜单
void allocate(node *head)
{
    char name[5];
    int size;
    int c;
    printf("*********分配算法**********\n");
    printf("   *     1.最先分配算法      *   \n");
    printf("   *     2.最优分配算法      *   \n");
    printf("   *     3.最坏分配算法      *   \n");
    printf("         请输入选项[ ]\b\b");
    scanf("%d",&c);
    print(head);
    printf("请输入作业名:");
    scanf("%s",&name);
    printf("请输入%s需要分配的主存大小:",name);
    scanf("%d",&size);
    switch(c)
    {
        case 1:
            firstAllocation(head,size,name);
            break;
        case 2:
            goodAllocation(head,size,name);
            break;
        case 3:
            badAllocation(head,size,name);
            break;
    }
}
//最适分
void goodAllocation(node* head,int size,char c[10])
{
    node* mark=NULL;
    int m,n,count=1,i=0;
    segmentNode *t;
    t=(segmentNode*)malloc(sizeof(segmentNode));
    node* new;
    char a[5]="0";
    node* p;
    p=head->next;
    int rest;
    printf("请输入要分成几段：");
    scanf("%d",&m);
    while(m!=0)
    {
        m--;
        printf("剩余%dKB的内存，请输入第%d段的大小：",size,count);
        scanf("%d",&n);
        size=size-n;
        while(p)
        {
            if((n<=p->size)&&(p->flag[0]!='j')&&(p->flag!='J'))      //找到合适大小未分配位置
            {
                if(mark==NULL)
                    mark=p;
                else if(p->size<mark->size)
                    mark=p;
            }
            p=p->next;
        }

        if((n<=mark->size)&&(mark->flag[0]!='j')&&(mark->flag[0]!='J'))
        {
            rest=mark->size-n;
            if(rest==0)
            {
                strcpy(mark->flag,c);
                mark->flag[4]='0'+count-1;
                mark->flag[5]='\0';
            }

            else
            {
                mark->size=n;
                strcpy(mark->flag,c);
                mark->flag[4]='0'+count-1;
                mark->flag[5]='\0';           //已分配部分处理
                new=(node*)malloc(sizeof(node));
                new->address=mark->address+n;
                new->size=rest;
                strcpy(new->flag,a);


                new->next=mark->next;
                mark->next=new;
                reorder(head);
            }
        }
        t->a[i][0]=i;
        t->a[i][1]=n;
        t->a[i][2]=mark->address;
        i++;
        count++;
        print(head);
    }
    t->a[i][0]=-1;
    t->next=h;
    h=t;
    printf("\n分配成功！\n");
    printf("************打印%s段表************\n",c);
    printf("段号\t段长\t基址\n");
    for(i=0; i<10; i++)
    {
        if(t->a[i][0]!=-1)
            printf("%d\t%d\t%d\n",t->a[i][0],t->a[i][1],t->a[i][2]);
        else
            break;
    }
}
//最坏分配
void badAllocation(node* head,int size,char c[10])
{
    node* mark=NULL;
    node* new;
    segmentNode *t;
    t=(segmentNode*)malloc(sizeof(segmentNode));
    char a[5]="0";
    node* p;
    p=head->next;
    int rest;
    int m,n,i=0,count=1;
    printf("请输入要分成几段：");
    scanf("%d",&m);
    while(m!=0)
    {
        m--;
        printf("剩余%dKB的内存，请输入第%d段的大小：",size,count);
        scanf("%d",&n);
        size=size-n;
        while(p)
        {
            if((n<=p->size)&&(p->flag[0]!='j')&&(p->flag!='J'))      //找到合适大小未分配位置
            {
                if(mark==NULL)
                    mark=p;
                else if(p->size>mark->size)
                    mark=p;
            }
            p=p->next;
        }
        if((n<=mark->size)&&(mark->flag[0]!='j')&&(mark->flag[0]!='J'))
        {
            rest=mark->size-size;
            if(rest==0)
            {
                strcpy(mark->flag,c);
                mark->flag[4]='0'+count-1;
                mark->flag[5]='\0';
            }
            else
            {
                mark->size=n;
                strcpy(mark->flag,c);
                mark->flag[4]='0'+count-1;
                mark->flag[5]='\0';           //已分配部分处理
                new=(node*)malloc(sizeof(node));
                new->address=mark->address+n;
                new->size=rest;
                strcpy(new->flag,a);
                new->next=mark->next;
                mark->next=new;
                reorder(head);
            }
        }
        t->a[i][0]=i;
        t->a[i][1]=n;
        t->a[i][2]=mark->address;
        i++;
        count++;
        print(head);
    }
    t->a[i][0]=-1;
    t->next=h;
    h=t;
    printf("\n分配成功！\n");
    printf("************打印%s段表************\n",c);
    printf("段号\t段长\t基址\n");
    for(i=0; i<10; i++)
    {
        if(t->a[i][0]!=-1)
            printf("%d\t%d\t%d\n",t->a[i][0],t->a[i][1],t->a[i][2]);
        else
            break;
    }
}
//最先分配
void firstAllocation(node* head,int size,char c[10])
{
    node* new;
    segmentNode *t=NULL;
    int k;
    t=(segmentNode*)malloc(sizeof(segmentNode));
    int m,n,count=1;
    int i=0;
    char a[5]="0";
    node* p;
    p=head->next;
    int rest;
    printf("请输入要分成几段：");
    scanf("%d",&m);
    while(m!=0)
    {
        m--;
        printf("剩余%dKB的内存，请输入第%d段的大小：",size,count);
        scanf("%d",&n);
        size=size-n;
        while((p->next)&&((n>p->size)||(p->flag[0]=='j')||(p->flag[0]=='J')))      //找到合适大小未分配位置
            p=p->next;
        if(p->next=NULL)
        {
            printf("越界中断！\n");
            return ;
        }
        if((n<=p->size)&&(p->flag[0]!='j')&&(p->flag[0]!='J'))
        {
            rest=p->size-n;
            if(rest==0)
            {
                strcpy(p->flag,c);
                p->flag[4]='0'+count-1;
                p->flag[5]='\0';
            }
            else
            {
                p->size=n;
                strcpy(p->flag,c);                    //已分配部分处理
                k=count-1;
                p->flag[4]='0'+count-1;
                p->flag[5]='\0';
                new=(node*)malloc(sizeof(node));
                new->address=p->address+n;
                new->size=rest;
                strcpy(new->flag,a);
                new->next=p->next;
                p->next=new;
                reorder(head);
            }
            t->a[i][0]=i;
            t->a[i][1]=n;
            t->a[i][2]=p->address;
            i++;
            count++;
        }
        print(head);
    }
    t->a[i][0]=-1;
    t->next=h;
    h=t;
    printf("\n分配成功！\n");
    printf("************打印%s段表************\n",c);
    printf("段号\t段长\t基址\n");
    for(i=0; i<10; i++)
    {
        if(t->a[i][0]!=-1)
            printf("%d\t%d\t%d\n",t->a[i][0],t->a[i][1],t->a[i][2]);
        else
            break;
    }
}

//打印主存 已分配未分配的分区表情况
void print(node* head)
{
    node* p=head;
    printf("******************主存分配情况*********************\n");

    printf("已分配：\n");
    printf("分配号\t大小（KB）\t起始（KB）\t状态\n");
    {
        p=head->next;
        while(p)
        {
            if(  (p->flag[0]=='j')||(p->flag[0]=='J')   )
                printf("%d\t%d\t\t%d\t\t%s\n",p->id,p->size,p->address,p->flag);
            p=p->next;
        }
    }

    printf("\n\n未分配：\n");
    printf("分配号\t大小（KB）\t起始（KB）\t状态\n");
    {
        p=head->next;
        while(p)
        {
            if(  (p->flag[0]!='j')&&(p->flag[0]!='J')   )
                printf("%d\t%d\t\t%d\t\t空闲\n",p->id,p->size,p->address);
            p=p->next;
        }
    }
}

//修改id
void reorder(node* head)
{
    int count=1;
    node*p=head;
    while(p->next)
    {
        p=p->next;
        if((p->flag[0]=='j')||(p->flag[0]=='J'))
        {
            p->id=count;
            count++;
        }
    }
    p=head;
    while(p->next)
    {
        p=p->next;
        if((p->flag[0]!='j')&&(p->flag[0]!='J'))
        {
            p->id=count;
            count++;
        }
    }
}

//回收
void recyle(node* head)
{
    print(head);
    printf("请输入您想回收的作业名：");
    char c[10];
    scanf("%s",c);
    char a[5]="0";
    int i=0;
    int count=0;

    node* p;
    p=head;
    while(p->next)
    {
        if(p->next->flag[3]==c[3])
        {
            count=1;
            if((p!=head)&&(p->flag[0]!='j')&&(p->flag[0]!='J'))
            {
                if((p->next->next)&&((p->next->next->flag[0]!='j')&&(p->next->next->flag[0]!='J')))      //有上邻有下邻
                {
                    p->size+=p->next->size;
                    p->size+=p->next->next->size;
                    p->next=p->next->next->next;
                }
                else                                                                                                //有上邻无下邻
                {
                    p->size+=p->next->size;
                    p->next=p->next->next;
                }
            }
            else                                                                                                     //无上邻大类
            {
                if((p->next->next)&&((p->next->next->flag[0]!='j')&&(p->next->next->flag[0]!='J')))            //无上邻有下邻小类
                {
                    strcpy(p->next->flag,a);
                    p->next->size+=p->next->next->size;
                    p->next->next=p->next->next->next;
                    p=p->next;
                }
                else                                                                                                 //无上邻无下邻小类
                {
                    strcpy(p->next->flag,a);
                    p=p->next;
                }
            }
            printf("回收%s的段%s%d成功！\n",c,c,i);
            reorder(head);
            i++;
        }
        else
            p=p->next;
    }


    if(count==0)
        printf("你想回收的作业不存在！\n");
    print(head);
}


int main()
{
    node* head;
    int c;
    int flag=1;
    head=initMemory();//初始化
    while(flag)
    {
        printf("*********可变分区管理**********\n");
        printf("   *     1.内存分配      *   \n"  );
        printf("   *     2.内存去配      *   \n"  );
        printf("   *     0.退出          *   \n"  );
        printf("         请输入选项[ ]\b\b"       );
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                printf("1.内存分配\n");
                allocate(head);
                break;
            case 2:
                printf("2.内存去配\n");
                recyle(head);
                break;
            case 0:
                printf("0.退出\n");
                flag=0;
                break;
        }
    }
    getch();
    return 0;

}
