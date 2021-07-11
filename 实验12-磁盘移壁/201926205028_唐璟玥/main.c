#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MX 199
int ans[MX];//��˳���������
int vis[MX];//�����������
int length;
int begin;//Ŀǰ�����ʵ�����
//�ŵ������Ϊ0

//��ӡ
void print()
{
    printf("�ű��ƶ�˳��Ϊ��\n");
    int sum=0;
    for(int i=0; i<=length; ++i)
    {
        printf("%d ",ans[i]);
        if(i)
        {
            sum=sum+abs(ans[i]-ans[i-1]);
        }
    }
    printf("\nɨ��������Ϊ��%d\n\n",sum);
}
//�����ȷ���
void FCFS()
{
    printf("\n********************FCFS�㷨********************\n");
    printf("����������еĳ��ȣ�");
    scanf("%d",&length);
    printf("����������У�");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("���ڷ��ʵ�����ţ�");
    scanf("%d",&begin);
    ans[0]=begin;

    for(int i=0; i<length; ++i)
    {
        ans[i+1]=vis[i];
    }
    print();
}
//���Ѱ��ʱ������
void SSTF()
{
    printf("\n********************SSTF�㷨********************\n");
    printf("����������еĳ��ȣ�");
    scanf("%d",&length);
    printf("����������У�");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("���ڷ��ʵ�����ţ�");
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
        vis[t]= -1;//�Ѿ�Ѱ�����ĸ�Ϊ-1
    }
    print();
}
//����ɨ���������
void onewayScanning()
{
    printf("\n********************����ɨ���㷨********************\n");
    printf("����������еĳ��ȣ�");
    scanf("%d",&length);
    printf("����������У�");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("���ڷ��ʵ�����ţ�");
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
            if(vis[j]!=-1 && vis[j]>=now && vis[j]<=x)//��������
            {
                mi=j;
                x=vis[mi];//�ҵ���߾��������
            }
        }
        if(mi!=-1)//�����߻���
        {
            i--;
            ans[cnt++]=vis[mi];
            now=vis[mi];
            vis[mi]=-1;
            mi=-1;
            x=MX;
        }
        else//mi==-1 ��0���⿪ʼ
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
//˫��ɨ�裨���⵽�
void bilateralScanningUp()
{
    printf("\n********************˫��ɨ�裨���⵽��㷨********************\n");
    printf("����������еĳ��ȣ�");
    scanf("%d",&length);
    printf("����������У�");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("���ڷ��ʵ�����ţ�");
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
            if(vis[j] != -1 && vis[j]>=now && vis[j]<=x)//��������С���������
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
            if(vis[j] != -1 && vis[j] <=now && vis[j] >= x)//��������󣬾������
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
//˫��ɨ�裨���ﵽ�⣩
void bilateralScanningDown()
{
    printf("\n********************˫��ɨ�裨���ﵽ�⣩�㷨********************\n");
    printf("����������еĳ��ȣ�");
    scanf("%d",&length);
    printf("����������У�");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("���ڷ��ʵ�����ţ�");
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

//���ݵ��ȣ����⵽�
void elavatorUp()
{
    printf("\n********************%���ݵ��ȣ����⵽��㷨********************\n");
    printf("����������еĳ��ȣ�");
    scanf("%d",&length);
    printf("����������У�");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("���ڷ��ʵ�����ţ�");
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
                mi=j;//��¼now��ʼ���⵽�����С����
                x=vis[j];
            }
        }
        if(mi != -1)//�����໹����С��
        {
            ans[cnt++]=vis[mi];
            now=vis[mi];//�ı�now
            vis[mi]=-1;//��Ϊ-1��ʾ�Ѿ�����
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
            if(vis[j] != -1 && vis[j]<=now && vis[j]>=x)//now�������Ҫ���ʵĴŵ������Կ�ʼ����������jΪ-1��
            {
                mx=j;
                x=vis[j];//�ҵ�����ģ���vis[j]���ʹ������
            }
        }
        if(mx!=-1)//����ұ߻�������ķ��ʴŵ�
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
//���ݵ��ȣ����ﵽ�⣩
void elevatorDown()
{
    printf("\n********************���ݵ��ȣ����ﵽ�⣩�㷨********************\n");
    printf("����������еĳ��ȣ�");
    scanf("%d",&length);
    printf("����������У�");
    for(int i=0; i<length; ++i)
    {
        scanf("%d",&vis[i]);
    }
    printf("���ڷ��ʵ�����ţ�");
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
        printf("***************������������***************\n");
        printf("      *   1.FCFS                   *\n");
        printf("      *   2.SSTF                   *\n");
        printf("      *   3.���ݵ��ȣ����⵽�   *\n");
        printf("      *   4.���ݵ��ȣ����ﵽ�⣩   *\n");
        printf("      *   5.����ɨ�裨�������   *\n");
        printf("      *   6.˫��ɨ�裨���⵽�   *\n");
        printf("      *   7.˫��ɨ�裨���ﵽ�⣩   *\n");
        printf("      *   8.�˳�                   *\n");
        printf("            ������ѡ��[ ]\b\b");
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
