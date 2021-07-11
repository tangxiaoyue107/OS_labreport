#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int physicalBlockNumber; // ��������

void FIFO()
{
    char name[100]; // ��ҵ������
    int workLength; // ҳ��ĳ���

    printf("��������ҵ����");
    scanf("%s",&name);
    printf("��������ҵҳ��ĳ��ȣ�");
    scanf("%d",&workLength);
    printf("��������ҵҳ��˳��:");
    int a[workLength];
    for(int i=0; i<workLength; i++)
        scanf("%d",&a[i]);
    printf("**************��ӡ��ҵFIFO���Ƚ�������ҳ�Ĺ���**************\n");
    printf("��ҵ����%s\n",name);
    printf("��ҵ���ȹ��̣�\n");
    printf("    ");
    for(int j=0; j<workLength; j++)
        printf("%4d",j);
    printf("\n");
    printf("    ");
    for(int k=0; k<workLength; k++)
        printf("%4d",a[k]);
    printf("\n");
    //�����ά����
    char pages[physicalBlockNumber+2][workLength+1];
    //��ʼ��pages��ά����
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
            if(a[j-1]+'0'==pages[i][j-1])//���ҳ�����ڴ���
            {
                flag=1;//�����κζ�ά����䶯����
                break;
            }
        if(flag)
        {
            for(int i=0; i<physicalBlockNumber; i++)
                pages[i][j]=pages[i][j-1];//����һ�е�ҳ���ǰһ��һ��
        }
        else//�����¼һ���жϣ�ҳ���û�
        {
            counter++;
            pages[0][j]=a[j-1]+'0';//FIFO�û��������ڴ���������õ�ҳ�棬Ҳ����������ġ��������ƣ����磺107->210
            for(int i=0; i<physicalBlockNumber-1; i++)
            {
                pages[i+1][j]=pages[i][j-1];
            }
            pages[physicalBlockNumber][j]='+';//��ʾ�ж�
            pages[physicalBlockNumber+1][j]=pages[physicalBlockNumber-1][j-1];
        }
    }
    for(int i=0; i<physicalBlockNumber+2; i++)
    {
        for(int j=0; j<workLength+1; j++)
        {
            printf("%4c",pages[i][j]);//�Ѷ�ά�����ӡ
        }
        printf("\n");
    }
    printf("ȱҳ�ж���Ϊ��%.2f\n",counter*1.0/workLength*100);
}


void LRU()
{
    char name[100]; // ��ҵ������
    int workLength; // ҳ��ĳ���

    printf("��������ҵ����");
    scanf("%s",&name);
    printf("��������ҵҳ��ĳ��ȣ�");
    scanf("%d",&workLength);
    printf("��������ҵҳ��˳��:");
    int a[workLength];
    for(int i=0; i<workLength; i++)
        scanf("%d",&a[i]);
    printf("**************��ӡ��ҵLRU(LFU)���Ƚ�������ҳ�Ĺ���**************\n");
    printf("��ҵ����%s\n",name);
    printf("��ҵ���ȹ��̣�\n");
    printf("    ");
    for(int j=0; j<workLength; j++)
        printf("%4d",j);
    printf("\n");
    printf("    ");
    for(int k=0; k<workLength; k++)
        printf("%4d",a[k]);
    printf("\n");
    //�����ά����
    char cla[physicalBlockNumber+2][workLength+1];
    //��ʼ����ά����
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
            if(a[j-1]+'0'==cla[i][j-1]) //���ҳ�������ڴ���
            {
                s=i; //��¼��������
                flag=1;
                break;
            }
        if(flag)
        {
            cla[0][j]=a[j-1]+'0';
            for(int i=0; i<s; i++)//���ҳ�����ڴ��Ҳ��Ҫ�ı���һ�������˳�򣬽��·��ʵķ������ϡ�
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
    printf("ȱҳ�ж���Ϊ��%.2f\n",counter*1.0/workLength*100);
}

int operation()
{
    printf("**************�����ҳʽ�洢����**************\n");
    printf("           *   1.FIFO����         *\n");
    printf("           *   2.LRU(LFU)����     *\n");
    printf("           *   0.�˳�             *\n");
    printf("               ������ѡ��[ ]\b\b");
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
        printf("0.�˳�\n");
        return 1;
    default:
        printf("\n����������ѡ�\n\n");

    }
    return 0;
}

int main()
{
    printf("�����������Ŀ�����");
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
