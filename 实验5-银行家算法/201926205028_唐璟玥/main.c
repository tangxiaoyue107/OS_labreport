#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100//���κ��������ڵ���MAX�Ĵ�С
int N,M;//N����Դ����M��ʾ������
int need[MAX][MAX];//P[i]����j����Դ������
int available[MAX];//ĳ����Դ�Ŀ�����
int max[MAX][MAX];//P[i]����Դj������������
int allocate[MAX][MAX]= {0}; //p[i]��j����Դ�ѷ������Դ��
int finish[MAX]= {0}; //P[i]�����Ƿ�ִ�н���
int request[MAX][MAX];//���̶�ĳ����Դ��������
int Flag[MAX]= {0};//P[i]�����Ƿ��Ѿ�����ȫ��������Դ
int s[MAX];//��¼��ȫ��������


//��ʼ����Ϣ
void Init()
{
    // ��ʼ����Դ�������������
    printf("��������Դ��������");
    scanf("%d",&N);
    printf("�������������");
    scanf("%d",&M);
    int i, j;
    printf("������%d����Դ�ĳ�ʼ����Դ����",N);    // ��ʼ��������Դ�Ŀ�����
    for(i = 0; i < N; i++)
    {
        scanf("%d",&available[i]);
    }
    printf("������%d�����̵������Ϣ��\n",M);// ��ʼ������������
    printf("������\t\t���������\n\t\t");
    for(i=0; i<N; i++)
    {
        printf("%c ",'A'+i);//��ӡ��Դ��ABC����
    }
    printf("\n");
    for(i=0; i<M; i++)//����ÿһ������
    {
        printf("����P[%d]\t",i);//��������
        while(1)
        {
            int count = 0;//err[MAX]�����еĳ���������������
            int bigthaninit = 0;//��¼�˽�����������������Ƿ���ڳ�ʼ��Դ����� ���������ı�Ϊ1
            int err[MAX];//�����Ͻ��������������ϵͳ�ṩ�����Դ�����������飬�������ϵ���Դ����¼������
            for(int j=0; j<N; j++)
            {
                scanf("%d",&max[i][j]);
                if(max[i][j]>available[j])//���������������������������ɷ�����Դ��
                {
                    err[count++]=j;//��¼��err��������������д������Դ���
                    bigthaninit=1;//��־��Ϊ1���޷�����ѭ��
                }
            }
            if(bigthaninit==0)//�����־û��Ϊ0����ʾ����û���⣬������whileѭ����������һ�����̡�
            {
                break;
            }
            if(count!=0)//���count��Ϊ��ʼֵ0����˵�����̷�����Դ�������⡣��ӡ���������Դ���࣬���������������Դ�������������
            {
                printf("�������������ϵͳ������Դ\n");
                for(int k=0; k<count; k++) printf("ϵͳ%c����Դ��������Ϊ%d\n",'A'+err[k],available[err[k]]);
                printf("����������\n");
                printf("����P[%d]\t",i);
            }
        }
    }

    //��ʼ����ǰ�ѷ�����Դ���������������allocate��need����
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
//��Ϣ��ʾ����
void ShowInfo()
{
    printf("\n");
    printf("������\t\t���������\t\t��������\t\t�ѷ�����\t\t����״̬\n\t\t");
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
        printf("����P[%d]\t",i);
        for(int j = 0; j < N; j++)
        {
            printf("%d ",max[i][j]);//��ӡmax����
        }
        printf("\t\t\t");
        for(int j = 0; j < N; j++)
        {
            printf("%d ",need[i][j]);//��ӡneed����
        }
        printf("\t\t\t");
        for(int j = 0; j < N; j++)
        {
            printf("%d ",allocate[i][j]);//��ӡallocate����
        }
        printf("\t\t\t");
        if(Flag[i]==1)
        {
            printf("finished");//��ӡ�Ƿ�������
        }
        else
        {
            printf("working");
        }
        printf("\n");
    }
    printf("\n");
    printf("��Դʣ������\t");
    for(int i = 0; i < N; i++)
    {
        printf("%d ",available[i]);//��ӡʣ��available����
    }
    printf("\n");
}
//��ȫ���㷨
int isSafe()
{
    int have_finished = 0;//�Ѿ���������Ľ��̸���
    int sindex = 0;//������ɽ��̵ĸ���
    int work[N];//������������ʾϵͳ���ṩ�����̼����������������Դ��Ŀ
    //��ʼʱ������work = available
    for(int i = 0; i < N; i++)
    {
        work[i]=available[i];
    }
    //��ʼʱ��������Flag[i]=finish[i]
    for(int i = 0; i < M; i++)
    {
        finish[i]=Flag[i];
        if(finish[i]==1)
        {
            have_finished++;//�����finishe[i]Ϊ1��˵���˽�������ɣ�have_finished++
        }
    }
    while(have_finished != M)//����Ѿ�������Դ�����ĸ������������н��̸�����һֱѭ����ֱ�����еĽ�����work�ļ����¶���ȫ
    {
        int insist_circulate = 0;//����ѭ����־
        for(int i=0; i < M ; i++)
        {
            int num = 0;//num��ʾ�������������need<work�������Ŀ
            for(int j = 0; j < N; j++)
            {
                if(need[i][j] <= work[j] && finish[i] == 0)//���need��Ҫ����Դ����С��availableҲ����word�Է������Դ��
                {
                    num ++;//num������1
                }
            }
            if(num == N)//����������num�ĸ�������Դ������һ����˵���������Է���������̿���
            {
                for(int k = 0; k < N; k++)
                {
                    work[k]+=allocate[i][k];//�������ɹ���work�����available�����ı䣬����ɹ��������һ�����̵ķ���
                }
                have_finished++;//��ɵĽ��̼�1
                s[sindex] = i;//s�����ʾ��˳�������ɵĽ��̵�Ŀǰ�����Ľ�������
                sindex++;//��˳����ɸ�����1
                finish[i]=1;//������̵�finished�����Ϊ1
                insist_circulate = 1;//ѭ������
            }
        }

        if(insist_circulate){

        }else{//���ѭ��Ϊ0��˵�����ɹ��Է��䲻�ɹ������������ѭ������ʱ����ɵ�have_finished������Ϊ���̸�������Ϊ��;�ж���
            break;
        }
    }

    if(have_finished == M)//���have_finished�����ͽ��̸���һ����ȫ
    {
        int count = have_finished;
        printf("ϵͳ��ȫ����ȫ����Ϊ��");
        for(int i=0;i<M;i++){
                if(Flag[i]){
                        count--;//�������Flag���̽�����ɵĽ��̸���
                }
        }

        for(int i = 0; i < count; i++)//ѭ��count�Σ���ʾ���ְ�ȫ���ѭ�������Ľ��̸���
        {
            printf("p[%d] ",s[i]);//���s�������е�˳�򣬱�ʾ��ȫ����
        }
        printf("\n");
        return 1;
    }
    else//���򲻰�ȫreturn 0
    {
        printf("ϵͳ����ȫ���ް�ȫ����\n");
        return 0;
    }
}
//�����⺯��
int ResourceRequest(int now,int cc[][MAX])//now��ʾ�ڼ������̣�cc��ʾ��һ���ֶ�����ĸ�����Դ��
{
    int j;
    //�ж������Ҫ����Դ�Ƿ�ȱ�����������Ҫ����Դ��С��
    for( j=0; j<N; j++)
    {
        if(cc[now][j]<=need[now][j])//��������С�����������Ҫ�ĸ�����Դ��������������������Դ������������
        {

        }
        else
        {
            printf("Error��������Դ������������");//return 0 ��ʹ��FirstApply������������˴����������Դ��
            return 0;
        }
    }
    //�ж������Ҫ����Դϵͳʣ����Դ���Ƿ��㹻�������
    if(j == N)//�����������и�����Դ����С�����������Ҫ�ĸ�����Դ��
    {
        for(int k = 0; k< N; k++)//�жϵ�ǰ������Դʣ����ø�����Դ���Ƿ��㹻�����������ʹ��
        {
            if(cc[now][k] <= available[k])//����㹻�����ѭ���ж���һ������
            {
                continue;
            }
            else
            {
                printf("Error��ϵͳ��Դ���㣬�ȴ��У�\n");//�����㹻��˵��ϵͳ��Դ���㣬��Ҫ�ȴ���
                return 0;//return 0 ��ʹ��FirstApply������������˴����������Դ��
            }
        }
    }
    //�������������������㣬��˵����������������������������������㣬���Խ�����һ����̽�Է��价��
    return 1;
}
//��̽�Է���
int Probe(int now)
{
    for(int j = 0; j < N; j++)//��������⺯���ɹ���������ȼ���������̼�������request��Դ֮��ĵ�available,allocate,need�Ľ��
    {
        available[j] -= request[now][j];
        allocate[now][j] += request[now][j];
        need[now][j] -= request[now][j];
    }
    if(isSafe())//��ȫ�Լ��ͨ�����жϷ�����ɺ�����Ƿ����
    {
        if(IsFinished(now) == 1)//�������
        {
            for(int j = 0; j < N; j++ )
            {
                available[j] = available[j] + allocate[now][j];//ϵͳÿһ�����Դ�������ͷź�available����ԭ�������ϼ���allocate����Դ��
            }

            Flag[now]=1;//Flag�����now����Ϊ1��ʾΪ����״̬��

        }
        printf("��Դ����ɹ���\n");
        return 1;
    }
    else//��ȫ�Լ�ⲻͨ��
    {
        for(int j = 0; j < N; j++)//�����е�available allocate need�������ݻ�ԭ
        {
            available[j] += request[now][j];
            allocate[now][j] -= request[now][j];
            need[now][j] += request[now][j];
        }
        printf("��Դ����ʧ�ܣ�������\n");
        return 0;//return 0֮����FirstApply��������������˽��̵ķ�����Դ��
    }
}
//���̽�����⺯��
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
            FinishedFlag = 0; //���FinishedFlagΪ0��˵������������Դ��������δ����
            break;
        }
    }
    return FinishedFlag;//Ϊ1��˵�����̽�����Ϊ0˵�����̻�������need��Ϊ0
}

//��һ����Դ���뺯��
void FirstApply()
{
    printf("������%d�����̵ĵ�һ����Դ��������\n",M);
    printf("������\t\t��һ�ε�������");
    printf("\n\t\t");
    for(int i=0; i<N; i++)
    {
        printf("%c ",'A'+i);
    }
    printf("\n");
    for(int i=0; i<M; i++)
    {
        printf("����P[%d]��\t",i);
        while(1)
        {
            for(int j=0; j<N; j++)
            {
                scanf("%d",&request[i][j]);
            }
            if(ResourceRequest(i,request)==0)//�����⺯����������ͨ��Ϊ1��δͨ����Ϊ0��������
            {
                printf("\n");
                printf("����������������̵���Դ������\n");
                printf("����P[%d]��\t",i);
                continue;
            }
            if(Probe(i)==1)//��̽�Է��亯�����������1��˵����̽�ɹ���break�������һ�����̣����������������������Դ���������½���˽��̵�ѭ��
            {
                break;

            }
            printf("\n");
            printf("����������������̵���Դ������\n");
            printf("����P[%d]��\t",i);
        }
    }
    ShowInfo();//��ʾ��������ɹ�����Ϣ������ʾ���

}
//��Դ����
void Apply()
{
    while(1)
    {
        int now;// ��ʾ��ǰ������Դ�Ľ��̱��
        int ok = 1;
        printf("��Դʣ������\t");//��ʾ�����Դʣ�����Ŀ
        for(int i = 0; i < N; i++)
        {
            printf("%d ",available[i]);
        }
        printf("\n");
        printf("�Ƿ���Ҫ��������Դ��Y/N����");
        while(1)
        {
            char c;
            scanf("%c",&c);//����ָ��YES OR NO
            if(c == 'Y' || c == 'y')
            {
                printf("��������̱�ţ�0��%d��P��",M-1);
                scanf("%d",&now);//������̱�ţ���1��ʼ����Ӧ��0123����
                printf("���������P[%d]��Ҫ�������Դ����",now);
                while(1)
                {
                    for(int j=0; j<N; j++)
                    {
                        scanf("%d",&request[now][j]);//����˴�����������Դ����
                    }
                    if(ResourceRequest(now,request)==1)//�����⺯����������ͨ��Ϊ1��δͨ����Ϊ0��������
                    {
                        break;
                    }
                    else
                    {
                        printf("\n");
                        printf("����������������̵���Դ������\n");
                        printf("���������P[%d]��Ҫ�������Դ����",now);
                    }
                }
                int cc=Probe(now);//������������������������㣬�������̽�Է���������̵Ľ����
                ShowInfo();//������̽�ɹ���ʧ�ܶ�showinfo()���ɹ���showinfo��Ϊ����ɹ��ģ����ɹ�����ԭΪԭʼ״̬
                break;//�������ѭ���ٴ��ж��Ƿ���Ҫ������Դ��
            }
            else if(c == 'N' || c == 'n')//�������������Դ�����
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

