#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100//本次宏设置用于调整MAX的大小
int N,M;//N是资源数，M表示进程数
int need[MAX][MAX];//P[i]尚需j类资源的数量
int available[MAX];//某类资源的可用量
int max[MAX][MAX];//P[i]对资源j类的最大需求量
int allocate[MAX][MAX]= {0}; //p[i]在j类资源已分配的资源量
int finish[MAX]= {0}; //P[i]进程是否执行结束
int request[MAX][MAX];//进程对某类资源的申请量
int Flag[MAX]= {0};//P[i]进程是否已经满足全部所需资源
int s[MAX];//记录安全序列数组


//初始化信息
void Init()
{
    // 初始化资源类别数，进程数
    printf("请输入资源种类数：");
    scanf("%d",&N);
    printf("请输入进程数：");
    scanf("%d",&M);
    int i, j;
    printf("请输入%d类资源的初始化资源数：",N);    // 初始化各类资源的可用数
    for(i = 0; i < N; i++)
    {
        scanf("%d",&available[i]);
    }
    printf("请输入%d个进程的相关信息：\n",M);// 初始化最大需求矩阵
    printf("进程名\t\t最大需求量\n\t\t");
    for(i=0; i<N; i++)
    {
        printf("%c ",'A'+i);//打印资源类ABC……
    }
    printf("\n");
    for(i=0; i<M; i++)//读入每一个进程
    {
        printf("进程P[%d]\t",i);//进程名字
        while(1)
        {
            int count = 0;//err[MAX]数组中的超出需求量类别个数
            int bigthaninit = 0;//记录此进程申请最大需求量是否大于初始资源最大数 如果大于则改变为1
            int err[MAX];//不符合进程最大需求量＜系统提供最多资源数条件的数组，将不符合的资源类别记录下来。
            for(int j=0; j<N; j++)
            {
                scanf("%d",&max[i][j]);
                if(max[i][j]>available[j])//如果种类的最大需求量超出此种类可分配资源数
                {
                    err[count++]=j;//记录到err数组中这个进程有错误的资源类别
                    bigthaninit=1;//标志变为1，无法跳出循环
                }
            }
            if(bigthaninit==0)//如果标志没变为0，表示分配没问题，则跳出while循环，进入下一个进程。
            {
                break;
            }
            if(count!=0)//如果count不为初始值0，则说明进程分配资源出现问题。打印有问题的资源种类，并重新输入进程资源的最大需求量。
            {
                printf("最大需求量超出系统可用资源\n");
                for(int k=0; k<count; k++) printf("系统%c类资源可用数量为%d\n",'A'+err[k],available[err[k]]);
                printf("请重新输入\n");
                printf("进程P[%d]\t",i);
            }
        }
    }

    //初始化当前已分配资源矩阵，需求矩阵，设置allocate和need数组
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            allocate[i][j] = 0;
            need[i][j] = max[i][j];
        }
    }
    return ;
}
//信息显示函数
void ShowInfo()
{
    printf("\n");
    printf("进程名\t\t最大需求量\t\t尚需求量\t\t已分配量\t\t工作状态\n\t\t");
    for(int i=0; i<M-2; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%c ",'A'+j);
        }
        printf("\t\t\t");
    }
    printf("\n");
    for(int i = 0; i < M; i++)
    {
        printf("进程P[%d]\t",i);
        for(int j = 0; j < N; j++)
        {
            printf("%d ",max[i][j]);//打印max数组
        }
        printf("\t\t\t");
        for(int j = 0; j < N; j++)
        {
            printf("%d ",need[i][j]);//打印need数组
        }
        printf("\t\t\t");
        for(int j = 0; j < N; j++)
        {
            printf("%d ",allocate[i][j]);//打印allocate数组
        }
        printf("\t\t\t");
        if(Flag[i]==1)
        {
            printf("finished");//打印是否进程完成
        }
        else
        {
            printf("working");
        }
        printf("\n");
    }
    printf("\n");
    printf("资源剩余数：\t");
    for(int i = 0; i < N; i++)
    {
        printf("%d ",available[i]);//打印剩余available数组
    }
    printf("\n");
}
//安全性算法
int isSafe()
{
    int have_finished = 0;//已经分配结束的进程个数
    int sindex = 0;//结束完成进程的个数
    int work[N];//工作向量，表示系统可提供给进程继续运行所需各类资源数目
    //开始时，所有work = available
    for(int i = 0; i < N; i++)
    {
        work[i]=available[i];
    }
    //开始时，令所有Flag[i]=finish[i]
    for(int i = 0; i < M; i++)
    {
        finish[i]=Flag[i];
        if(finish[i]==1)
        {
            have_finished++;//如果有finishe[i]为1的说明此进程已完成，have_finished++
        }
    }
    while(have_finished != M)//如果已经分配资源结束的个数不等于所有进程个数则一直循环，直到所有的进程在work的假设下都安全
    {
        int insist_circulate = 0;//设置循环标志
        for(int i=0; i < M ; i++)
        {
            int num = 0;//num表示这个进程中满足need<work的类别数目
            for(int j = 0; j < N; j++)
            {
                if(need[i][j] <= work[j] && finish[i] == 0)//如果need需要的资源个数小于available也就是word试分配的资源数
                {
                    num ++;//num个数加1
                }
            }
            if(num == N)//如果这个进程num的个数和资源分类数一样，说明可以先试分配这个进程看看
            {
                for(int k = 0; k < N; k++)
                {
                    work[k]+=allocate[i][k];//假设分配成功，work替代的available数量改变，假设成功后进行下一个进程的分配
                }
                have_finished++;//完成的进程加1
                s[sindex] = i;//s数组表示按顺序结束完成的进程的目前个数的进程序列
                sindex++;//按顺序完成个数加1
                finish[i]=1;//这个进程的finished数组变为1
                insist_circulate = 1;//循环继续
            }
        }

        if(insist_circulate){

        }else{//如果循环为0则说明不成功试分配不成功。跳出最外层循环，这时已完成的have_finished不可能为进程个数，因为中途中断了
            break;
        }
    }

    if(have_finished == M)//如果have_finished个数和进程个数一样则安全
    {
        int count = have_finished;
        printf("系统安全！安全序列为：");
        for(int i=0;i<M;i++){
                if(Flag[i]){
                        count--;//计算此轮Flag进程结束完成的进程个数
                }
        }

        for(int i = 0; i < count; i++)//循环count次，表示此轮安全检测循环结束的进程个数
        {
            printf("p[%d] ",s[i]);//输出s数组序列的顺序，表示安全序列
        }
        printf("\n");
        return 1;
    }
    else//否则不安全return 0
    {
        printf("系统不安全！无安全序列\n");
        return 0;
    }
}
//申请检测函数
int ResourceRequest(int now,int cc[][MAX])//now表示第几个进程，cc表示这一次手动申请的各类资源数
{
    int j;
    //判断这次需要的资源是否比本身进程最大还需要的资源数小。
    for( j=0; j<N; j++)
    {
        if(cc[now][j]<=need[now][j])//如果申请的小于这个进程需要的各类资源数则不做处理，否则请求资源超出尚需量。
        {

        }
        else
        {
            printf("Error：请求资源超出尚需量！");//return 0 后使得FirstApply函数重新输入此次所需各类资源数
            return 0;
        }
    }
    //判断这次需要的资源系统剩余资源中是否足够给与分配
    if(j == N)//如果申请的所有各类资源数都小于这个进程需要的各类资源数
    {
        for(int k = 0; k< N; k++)//判断当前各类资源剩余可用各类资源数是否足够给予这个进程使用
        {
            if(cc[now][k] <= available[k])//如果足够则继续循环判断下一个进程
            {
                continue;
            }
            else
            {
                printf("Error：系统资源不足，等待中！\n");//否则不足够则说明系统资源不足，需要等待。
                return 0;//return 0 后使得FirstApply函数重新输入此次所需各类资源数
            }
        }
    }
    //若以上两个条件都满足，则说明检测这个进程申请检测的两个基本条件满足，可以进行下一个试探性分配环节
    return 1;
}
//试探性分配
int Probe(int now)
{
    for(int j = 0; j < N; j++)//如果申请检测函数成功，则可以先计算这个进程假若分配request资源之后的的available,allocate,need的结果
    {
        available[j] -= request[now][j];
        allocate[now][j] += request[now][j];
        need[now][j] -= request[now][j];
    }
    if(isSafe())//安全性检测通过后判断分配完成后进程是否结束
    {
        if(IsFinished(now) == 1)//如果结束
        {
            for(int j = 0; j < N; j++ )
            {
                available[j] = available[j] + allocate[now][j];//系统每一类的资源都用完释放后，available将在原来基础上加上allocate的资源数
            }

            Flag[now]=1;//Flag数组的now进程为1表示为结束状态。

        }
        printf("资源申请成功！\n");
        return 1;
    }
    else//安全性检测不通过
    {
        for(int j = 0; j < N; j++)//讲所有的available allocate need数组内容还原
        {
            available[j] += request[now][j];
            allocate[now][j] -= request[now][j];
            need[now][j] += request[now][j];
        }
        printf("资源申请失败！请重试\n");
        return 0;//return 0之后在FirstApply函数中重新输入此进程的分配资源数
    }
}
//进程结束检测函数
int IsFinished(int now)
{
    int FinishedFlag = 1;
    for(int j=0; j<N; j++)
    {
        if(need[now][j] == 0)
        {

        }
        else
        {
            FinishedFlag = 0; //如果FinishedFlag为0则说明还有类别的资源的需求尚未满足
            break;
        }
    }
    return FinishedFlag;//为1则说明进程结束，为0说明进程还有类别的need不为0
}

//第一次资源申请函数
void FirstApply()
{
    printf("请输入%d个进程的第一次资源申请量：\n",M);
    printf("进程名\t\t第一次的申请量");
    printf("\n\t\t");
    for(int i=0; i<N; i++)
    {
        printf("%c ",'A'+i);
    }
    printf("\n");
    for(int i=0; i<M; i++)
    {
        printf("进程P[%d]：\t",i);
        while(1)
        {
            for(int j=0; j<N; j++)
            {
                scanf("%d",&request[i][j]);
            }
            if(ResourceRequest(i,request)==0)//申请检测函数，如果检测通过为1，未通过则为0重新输入
            {
                printf("\n");
                printf("请重新输入这个进程的资源申请量\n");
                printf("进程P[%d]：\t",i);
                continue;
            }
            if(Probe(i)==1)//试探性分配函数，如果返回1则说明试探成功，break后进入下一个进程，否则重新输入这个进程资源申请量重新进入此进程的循环
            {
                break;

            }
            printf("\n");
            printf("请重新输入这个进程的资源申请量\n");
            printf("进程P[%d]：\t",i);
        }
    }
    ShowInfo();//显示此轮如果成功的信息分类显示情况

}
//资源申请
void Apply()
{
    while(1)
    {
        int now;// 表示当前申请资源的进程编号
        int ok = 1;
        printf("资源剩余数：\t");//显示如今资源剩余的数目
        for(int i = 0; i < N; i++)
        {
            printf("%d ",available[i]);
        }
        printf("\n");
        printf("是否需要再申请资源（Y/N）：");
        while(1)
        {
            char c;
            scanf("%c",&c);//读入指令YES OR NO
            if(c == 'Y' || c == 'y')
            {
                printf("请输入进程编号（0—%d）P：",M-1);
                scanf("%d",&now);//读入进程编号（从1开始）对应的0123……
                printf("请输入进程P[%d]需要申请的资源数：",now);
                while(1)
                {
                    for(int j=0; j<N; j++)
                    {
                        scanf("%d",&request[now][j]);//读入此次申请各类的资源数量
                    }
                    if(ResourceRequest(now,request)==1)//申请检测函数，如果检测通过为1，未通过则为0重新输入
                    {
                        break;
                    }
                    else
                    {
                        printf("\n");
                        printf("请重新输入这个进程的资源申请量\n");
                        printf("请输入进程P[%d]需要申请的资源数：",now);
                    }
                }
                int cc=Probe(now);//如果申请检测两个基本条件满足，则进行试探性分配这个进程的结果。
                ShowInfo();//不论试探成功或失败都showinfo()，成功的showinfo则为分配成功的，不成功的则还原为原始状态
                break;//跳出这个循环再次判断是否需要申请资源。
            }
            else if(c == 'N' || c == 'n')//如果不再申请资源则结束
            {
                return;
            }
            else
            {

            }
        }
    }
}

int main()
{

    Init();
    ShowInfo();
    FirstApply();
    Apply();
    getch();
    return 0;

}
/*

3
5
10 5 7
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
0 1 1
2 0 0
3 0 2
2 1 1
0 0 2
Y
0
4 3 1
1 2 1
Y
0
1 2 0
Y
3
0 1 1
Y
1
1 2 2
Y
2
6 0 0
Y
4
1 1 1
Y
0
6 2 2
Y
4
4 3 1

*/

