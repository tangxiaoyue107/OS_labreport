#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int physicalBlockNumber; // 物理块个数

void FIFO()
{
    char name[100]; // 作业名数组
    int workLength; // 页面的长度

    printf("请输入作业名：");
    scanf("%s",&name);
    printf("请输入作业页面的长度：");
    scanf("%d",&workLength);
    printf("请输入作业页面顺序:");
    int a[workLength];
    for(int i=0; i<workLength; i++)
        scanf("%d",&a[i]);
    printf("**************打印作业FIFO调度进入主存页的过程**************\n");
    printf("作业名：%s\n",name);
    printf("作业调度过程：\n");
    printf("    ");
    for(int j=0; j<workLength; j++)
        printf("%4d",j);
    printf("\n");
    printf("    ");
    for(int k=0; k<workLength; k++)
        printf("%4d",a[k]);
    printf("\n");
    //定义二维数组
    char pages[physicalBlockNumber+2][workLength+1];
    //初始化pages二维数组
    for(int i=0; i<physicalBlockNumber+2; i++)
        for(int j=0; j<workLength+1; j++)
            pages[i][j]=' ';
    for(int i=0; i<physicalBlockNumber; i++)
        pages[i][0]=i+'0';
    pages[0][1]=a[0]+'0';
    pages[physicalBlockNumber][1]='+';

    int counter=1;
    for(int j=2; j<workLength+1; j++)
    {
        int flag=0;
        for(int i=0; i<physicalBlockNumber; i++)
            if(a[j-1]+'0'==pages[i][j-1])//如果页面在内存里
            {
                flag=1;//则不做任何二维数组变动处理
                break;
            }
        if(flag)
        {
            for(int i=0; i<physicalBlockNumber; i++)
                pages[i][j]=pages[i][j-1];//这这一列的页面和前一列一样
        }
        else//否则记录一次中断，页面置换
        {
            counter++;
            pages[0][j]=a[j-1]+'0';//FIFO置换的是在内存中滞留最久的页面，也就是最下面的。整体下移，例如：107->210
            for(int i=0; i<physicalBlockNumber-1; i++)
            {
                pages[i+1][j]=pages[i][j-1];
            }
            pages[physicalBlockNumber][j]='+';//表示中断
            pages[physicalBlockNumber+1][j]=pages[physicalBlockNumber-1][j-1];
        }
    }
    for(int i=0; i<physicalBlockNumber+2; i++)
    {
        for(int j=0; j<workLength+1; j++)
        {
            printf("%4c",pages[i][j]);//把二维数组打印
        }
        printf("\n");
    }
    printf("缺页中断率为：%.2f\n",counter*1.0/workLength*100);
}


void LRU()
{
    char name[100]; // 作业名数组
    int workLength; // 页面的长度

    printf("请输入作业名：");
    scanf("%s",&name);
    printf("请输入作业页面的长度：");
    scanf("%d",&workLength);
    printf("请输入作业页面顺序:");
    int a[workLength];
    for(int i=0; i<workLength; i++)
        scanf("%d",&a[i]);
    printf("**************打印作业LRU(LFU)调度进入主存页的过程**************\n");
    printf("作业名：%s\n",name);
    printf("作业调度过程：\n");
    printf("    ");
    for(int j=0; j<workLength; j++)
        printf("%4d",j);
    printf("\n");
    printf("    ");
    for(int k=0; k<workLength; k++)
        printf("%4d",a[k]);
    printf("\n");
    //定义二维数组
    char cla[physicalBlockNumber+2][workLength+1];
    //初始化二维数组
    for(int i=0; i<physicalBlockNumber+2; i++)
        for(int j=0; j<workLength+1; j++)
            cla[i][j]=' ';
    for(int i=0; i<physicalBlockNumber; i++)
        cla[i][0]=i+'0';
    cla[0][1]=a[0]+'0';
    cla[physicalBlockNumber][1]='+';
    int counter=1;

    for(int j=2; j<workLength+1; j++)
    {
        int flag=0;
        int s;
        for(int i=0; i<physicalBlockNumber; i++)
            if(a[j-1]+'0'==cla[i][j-1]) //如果页面已在内存里
            {
                s=i; //记录下列索引
                flag=1;
                break;
            }
        if(flag)
        {
            cla[0][j]=a[j-1]+'0';
            for(int i=0; i<s; i++)//如果页面在内存里，也需要改变那一列数组的顺序，将新访问的放在最上。
            {
                cla[i+1][j]=cla[i][j-1];
            }
            while(s<physicalBlockNumber-1)
            {
                cla[s+1][j]=cla[s+1][j-1];
                s++;
            }
        }
        else
        {
            counter++;
            cla[0][j]=a[j-1]+'0';
            for(int i=0; i<physicalBlockNumber-1; i++)
            {
                cla[i+1][j]=cla[i][j-1];
            }
            cla[physicalBlockNumber][j]='+';
            cla[physicalBlockNumber+1][j]=cla[physicalBlockNumber-1][j-1];
        }
    }
    for(int i=0; i<physicalBlockNumber+2; i++)
    {
        for(int j=0; j<workLength+1; j++)
        {
            printf("%4c",cla[i][j]);
        }
        printf("\n");
    }
    printf("缺页中断率为：%.2f\n",counter*1.0/workLength*100);
}

int operation()
{
    printf("**************请求分页式存储管理**************\n");
    printf("           *   1.FIFO分配         *\n");
    printf("           *   2.LRU(LFU)分配     *\n");
    printf("           *   0.退出             *\n");
    printf("               请输入选项[ ]\b\b");
    int y;
    scanf("%d",&y);
    switch(y)
    {
    case 1:
        FIFO();
        break;
    case 2:
        LRU();
        break;
    case 0:
        printf("0.退出\n");
        return 1;
    default:
        printf("\n请重新输入选项！\n\n");

    }
    return 0;
}

int main()
{
    printf("请输入物理块的块数：");
    scanf("%d",&physicalBlockNumber);

    while(1)
    {
        int c;
        c=operation();
        if(c==1)
        {
            break;
        }
    }
    getch();
    return 0;
}
/*

3
1
job1
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

job2
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

*/
