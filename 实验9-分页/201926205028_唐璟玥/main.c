#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
# define MAX 100
int page[MAX][MAX]= {0};
int Msize;//系统内存空间
int Wlength;//字长，位长
int WordNum;//字号
int Blength;//物理块大小
int BlockNum;//物理块个数
typedef struct link_node//页表结点
{
    char name[10];
    int size[MAX][MAX];
    struct link_node *next;
} node;

node* allocate(node *head);
node* recycle(node *head);
void print();
void initye();
void choose();

//分配
node* allocate(node *head)
{
    node *t,*p,*pre=NULL;
    int i,j,m,k=0,count=1;
    char jobname[20];
    p=head;
    //print();
    printf("请输入作业的名字：");
    scanf("%s",jobname);
    printf("请输入作业需要分配的大小：");
    scanf("%d",&m);

    if((page[BlockNum/Wlength][0])<m)
    {
        printf("\n存储空间不足，分配失败！\n");
        return head;
    }
    else
    {
        page[BlockNum/Wlength][0]-=m;//修改剩余物理块大小
        printf("分配成功！\n");
        //链接页表
        t=(node*)malloc(sizeof(node));
        for(i=0; i<20; i++)
            t->name[i]=jobname[i];
        for(i=0; i<WordNum; i++)
        {
            for(j=0; j<Wlength; j++)
            {
                if(count>m)//如果修改物理块个数大于作业大小就停止
                    break;
                else if(page[i][j]==0)
                {
                    t->size[k][0]=k;
                    t->size[k][1]=i*Wlength+j;
                    page[i][j]=1;
                    k++;
                    count++;
                }
            }
            if(count>m)//如果修改物理块个数大于作业大小就停止
                break;
        }

        t->size[m][0]=-1; //将页表最后一个数组值设为-1代表结束
        if(p==NULL)//如果是第一个插入主存页表
        {
            head=p=t;
            t->next=NULL;
        }
        else//不是第一个则要插入到末尾
        {
            while(p)
            {
                pre=p;
                p=p->next;
            }
            t->next=p;
            pre->next=t;
        }
        print();
        printf("**********打印%s作业的页表**********\n",t->name);
        for(i=0; i<m; i++)
        {
            printf("%d",t->size[i][0]);
            printf("\t%d\n",t->size[i][1]);
        }
        return head;
    }



}
//回收
node* recycle(node *head)
{
    node *p,*pre=NULL;
    p=head;

    char recyclejobname[20];
    int i,j;
    printf("请输入你当前要回收的作业名：");
    scanf("%s",recyclejobname);
    while(p)
    {
        if(strcmp(recyclejobname,p->name)==0)//此时p为相应的回收作业页表
        {
            break;
        }
        pre=p;
        p=p->next;
    }
    if(p==NULL)
    {
        printf("无此作业！回收失败！\n");
        return head;
    }


    printf("该作业无存储信息，回收成功！\n");
    for(i=0; i<100; i++)
    {
        if(p->size[i][0]!=-1)//不为停止符
        {
            p->size[i][0]=0;
            j=p->size[i][1];//块号
            page[j/Wlength][j%Wlength]=0;//找到位示图对应的二维表处，将1改为0
        }
        else
            break;

    }
    page[BlockNum/Wlength][0]+=i; //修改剩余块数
    //主存页表也要释放
    if(pre==NULL)
    {
        head=head->next;
    }
    else
    {
        pre->next=p->next;
    }
    print();
    return head;
}

//打印当前位示图
void print()
{
    int i,j;
    for(i=0; i<WordNum; i++)
    {
        for(j=0; j<Wlength; j++)
        {
            if(((i+1)*Wlength+j)>Msize)
                break;
            else
                printf("%3d",page[i][j]);
        }
        printf("\n");
    }
    printf("剩余物理块数%d\n",page[--i][j]);

}

//初始化
void initye()
{
    int i,j;
    int count=0;
    printf("请输入系统内存空间的大小：");
    scanf("%d",&Msize);
    printf("请输入字长（16/32/64）：");
    scanf("%d",&Wlength);
    printf("请输入物理块大小：");
    scanf("%d",&Blength);

    BlockNum=Msize/Blength;//物理块个数
    WordNum=BlockNum/Wlength+1;//字号

    srand(time(NULL));
    //初始化位示图
    for( i=0; i<WordNum; i++)
        for( j=0; j<Wlength; j++)
        {
            if(((i+1)*Wlength+j)>BlockNum)//如果大于物理块个数则跳出循环
                break;
            page[i][j]=rand()%2;//自由赋予0/1
            if(page[i][j]==1)
                count++;//count代表物理块为满的个数
        }
    page[i-1][j]=BlockNum-count;//位示图的最后一字节表示的是剩余空闲块数
    print();

}

//选择
void choose()
{
    node *head;
    head=NULL;
    while(1)
    {
        int c;
        printf("*********可变分区管理**********\n");
        printf("   *     1.内存分配      *   \n"  );
        printf("   *     2.内存去配      *   \n"  );
        printf("   *     0.退出          *   \n"  );
        printf("         请输入选项[ ]\b\b"       );
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                head=allocate(head);
                break;
            case 2:
                head=recycle(head);
                break;
            case 0:
                return ;
        }
    }
}


int main()
{
    initye();
    choose();
    getch();
    return 0;
}
