#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MX 199
int ans[MX];//按顺序访问序列
int vis[MX];//柱面访问序列
int length;
int begin;//目前正访问的序列
//磁道最外的为0

//打印
void print()
{
    printf("磁臂移动顺序为：\n");
    int sum=0;
    for(int i=0; i<=length; ++i)
    {
        printf("%d ",ans[i]);
        if(i)
        {
            sum=sum+abs(ans[i]-ans[i-1]);
        }
    }
    printf("\n扫过柱面数为：%d\n\n",sum);
}
//先来先服务
void FCFS()
{
    printf("\n********************FCFS算法********************\n");
    printf("柱面访问序列的长度：");
    scanf("%d",&length);
    printf("柱面访问序列：");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("正在访问的柱面号：");
    scanf("%d",&begin);
    ans[0]=begin;

    for(int i=0; i<length; ++i)
    {
        ans[i+1]=vis[i];
    }
    print();
}
//最短寻道时间优先
void SSTF()
{
    printf("\n********************SSTF算法********************\n");
    printf("柱面访问序列的长度：");
    scanf("%d",&length);
    printf("柱面访问序列：");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("正在访问的柱面号：");
    scanf("%d",&begin);
    ans[0]=begin;

    int now=begin;
    int k=1;
    for(int i=0; i<length; ++i)
    {
        int t;
        int mx=MX;
        for(int j=0; j<length; ++j)
        {
            if(vis[j] != -1 && abs(vis[j]-now)<mx)
            {
                t=j;
                mx=abs(vis[j]-now);
            }
        }
        ans[k++]=vis[t];
        vis[t]= -1;//已经寻道过的改为-1
    }
    print();
}
//单向扫描从外向里
void onewayScanning()
{
    printf("\n********************单向扫描算法********************\n");
    printf("柱面访问序列的长度：");
    scanf("%d",&length);
    printf("柱面访问序列：");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("正在访问的柱面号：");
    scanf("%d",&begin);
    ans[0]=begin;

    int now=begin;
    int mi=-1;
    int x=MX;
    int cnt=1;
    int i=length;
    while(i)
    {
        for(int j=0; j<length; ++j)
        {
            if(vis[j]!=-1 && vis[j]>=now && vis[j]<=x)//从外向里
            {
                mi=j;
                x=vis[mi];//找到里边距离最近的
            }
        }
        if(mi!=-1)//如果左边还有
        {
            i--;
            ans[cnt++]=vis[mi];
            now=vis[mi];
            vis[mi]=-1;
            mi=-1;
            x=MX;
        }
        else//mi==-1 从0最外开始
        {
            ans[cnt++]=199,now=199;
            ans[cnt++]=0,now=0;
            mi=-1;
            x=MX;
        }
    }
    length=cnt-1;
    print();
}
//双向扫描（由外到里）
void bilateralScanningUp()
{
    printf("\n********************双向扫描（由外到里）算法********************\n");
    printf("柱面访问序列的长度：");
    scanf("%d",&length);
    printf("柱面访问序列：");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("正在访问的柱面号：");
    scanf("%d",&begin);
    ans[0]=begin;

    int cnt =1;
    int mx=-1,mi=-1;
    int now = begin;
    int x=MX;
    for(int i=0; i<length; ++i)
    {
        for(int j=0; j<length; ++j)
        {
            if(vis[j] != -1 && vis[j]>=now && vis[j]<=x)//向左找最小，距离最近
            {
                mi=j;
                x=vis[j];
            }
        }
        if(mi!=-1)
        {
            ans[cnt++]=vis[mi];
            now=vis[mi];
            vis[mi]=-1;
            mi=-1;
            x=MX;
        }
        else
            break;
    }
    if(now != 199 && cnt <= length+1)
        ans[cnt++]=199,now=199;
    x=-1;
    for(int i=0; i<length; ++i)
    {
        for(int j=0; j<length; ++j)
        {
            if(vis[j] != -1 && vis[j] <=now && vis[j] >= x)//向右找最大，距离最近
            {
                mx=j;
                x=vis[j];
            }
        }
        if(mx != -1)
        {
            ans[cnt++] = vis[mx];
            now = vis[mx];
            vis[mx]=-1;
            mx=-1;
            x=-1;
        }
        else
            break;
    }
    length = cnt-1;
    print();
}
//双向扫描（由里到外）
void bilateralScanningDown()
{
    printf("\n********************双向扫描（由里到外）算法********************\n");
    printf("柱面访问序列的长度：");
    scanf("%d",&length);
    printf("柱面访问序列：");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("正在访问的柱面号：");
    scanf("%d",&begin);
    ans[0]=begin;

    int cnt=1;
    int mx=-1,mi=-1;
    int now=begin;
    int x=-1;
    for(int i=0; i<length; i++)
    {
        for(int j=0; j<length; j++)
        {
            if(vis[j] != -1 && vis[j] <= now && vis[j]>=x)
            {
                mx=j;
                x=vis[j];
            }
        }
        if(mx!=-1)
        {
            ans[cnt++]=vis[mx];
            now=vis[mx];
            vis[mx]=-1;
            mx=-1;
            x=-1;
        }
        else
            break;
    }
    if(now != 0)
        ans[cnt++]=0,now=0;
    x=MX;
    for(int i=0; i<length; i++)
    {
        for(int j=0; j<length; j++)
        {
            if(vis[j] != -1 && vis[j] >= now && vis[j] <=x)
            {
                mi=j;
                x=vis[j];
            }
        }
        if(mi != -1)
        {
            ans[cnt++]=vis[mi];
            now=vis[mi];
            vis[mi]=-1;
            mi=-1;
            x=MX;
        }
        else
            break;
    }
    length=cnt-1;
    print();
}

//电梯调度（由外到里）
void elavatorUp()
{
    printf("\n********************%电梯调度（由外到里）算法********************\n");
    printf("柱面访问序列的长度：");
    scanf("%d",&length);
    printf("柱面访问序列：");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("正在访问的柱面号：");
    scanf("%d",&begin);
    ans[0]=begin;

    int cnt=1;
    int mx=-1,mi=-1;
    int now=begin;
    int x=MX;
    for(int i=0; i<length; ++i)
    {
        for(int j=0; j<length; ++j)
        {
            if(vis[j]!=-1 && vis[j]>=now && vis[j] <= x)
            {
                mi=j;//记录now开始从外到里的最小索引
                x=vis[j];
            }
        }
        if(mi != -1)//如果左侧还有最小的
        {
            ans[cnt++]=vis[mi];
            now=vis[mi];//改变now
            vis[mi]=-1;//置为-1表示已经访问
            mi=-1;
            x=MX;
        }
        else
            break;
    }
    x=-1;
    for(int i=0; i<length; ++i)
    {
        for(int j=0; j<length; ++j)
        {
            if(vis[j] != -1 && vis[j]<=now && vis[j]>=x)//now左侧已无要访问的磁道，所以开始从里向外找j为-1的
            {
                mx=j;
                x=vis[j];//找到最近的（即vis[j]最大就代表最近
            }
        }
        if(mx!=-1)//如果右边还有最近的访问磁道
        {
            ans[cnt++]=vis[mx];
            now=vis[mx];
            vis[mx]=-1;
            mx=-1;
            x=-1;
        }
        else
            break;
    }
    print();
}
//电梯调度（由里到外）
void elevatorDown()
{
    printf("\n********************电梯调度（由里到外）算法********************\n");
    printf("柱面访问序列的长度：");
    scanf("%d",&length);
    printf("柱面访问序列：");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("正在访问的柱面号：");
    scanf("%d",&begin);
    ans[0]=begin;

    int cnt=1;
    int mx=-1,mi=-1;
    int now=begin;
    int x=-1;
    for(int i=0; i<length; ++i)
    {
        for(int j=0; j<length; ++j)
        {
            if(vis[j]!=-1 && vis[j]<=now && vis[j]>=x)
            {
                mx=j;
                x=vis[j];
            }
        }
        if(mx!=-1)
        {
            ans[cnt++]=vis[mx];
            now=vis[mx];
            vis[mx]=-1;
            mx=-1;
            x=-1;
        }
        else
            break;
    }
    x=MX;
    for(int i=0; i<length; ++i)
    {
        for(int j=0; j<length; ++j)
        {
            if(vis[j]!=-1 && vis[j]>=now && vis[j]<=x)
            {
                mi=j;
                x=vis[j];
            }
        }
        if(mi!=-1)
        {
            ans[cnt++]=vis[mi];
            now=vis[mi];
            vis[mi]=-1;
            mi=-1;
            x=MX;
        }
        else
            break;
    }
    print();
}


int main()
{
    int flag=1;
    while(flag)
    {
        printf("***************磁盘驱动调度***************\n");
        printf("      *   1.FCFS                   *\n");
        printf("      *   2.SSTF                   *\n");
        printf("      *   3.电梯调度（由外到里）   *\n");
        printf("      *   4.电梯调度（由里到外）   *\n");
        printf("      *   5.单向扫描（从外向里）   *\n");
        printf("      *   6.双向扫描（由外到里）   *\n");
        printf("      *   7.双向扫描（由里到外）   *\n");
        printf("      *   8.退出                   *\n");
        printf("            请输入选项[ ]\b\b");
        int c;
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                FCFS();
                break;
            case 2:
                SSTF();
                break;
            case 3:
                elavatorUp();
                break;
            case 4:
                elevatorDown();
                break;
            case 5:
                onewayScanning();
                break;
            case 6:
                bilateralScanningUp();
                break;
            case 7:
                bilateralScanningDown();
                break;
            case 8:
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
