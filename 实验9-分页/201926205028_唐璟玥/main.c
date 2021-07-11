#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
# define MAX 100
int page[MAX][MAX]= {0};
int Msize;//ϵͳ�ڴ�ռ�
int Wlength;//�ֳ���λ��
int WordNum;//�ֺ�
int Blength;//������С
int BlockNum;//��������
typedef struct link_node//ҳ����
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

//����
node* allocate(node *head)
{
    node *t,*p,*pre=NULL;
    int i,j,m,k=0,count=1;
    char jobname[20];
    p=head;
    //print();
    printf("��������ҵ�����֣�");
    scanf("%s",jobname);
    printf("��������ҵ��Ҫ����Ĵ�С��");
    scanf("%d",&m);

    if((page[BlockNum/Wlength][0])<m)
    {
        printf("\n�洢�ռ䲻�㣬����ʧ�ܣ�\n");
        return head;
    }
    else
    {
        page[BlockNum/Wlength][0]-=m;//�޸�ʣ��������С
        printf("����ɹ���\n");
        //����ҳ��
        t=(node*)malloc(sizeof(node));
        for(i=0; i<20; i++)
            t->name[i]=jobname[i];
        for(i=0; i<WordNum; i++)
        {
            for(j=0; j<Wlength; j++)
            {
                if(count>m)//����޸���������������ҵ��С��ֹͣ
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
            if(count>m)//����޸���������������ҵ��С��ֹͣ
                break;
        }

        t->size[m][0]=-1; //��ҳ�����һ������ֵ��Ϊ-1�������
        if(p==NULL)//����ǵ�һ����������ҳ��
        {
            head=p=t;
            t->next=NULL;
        }
        else//���ǵ�һ����Ҫ���뵽ĩβ
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
        printf("**********��ӡ%s��ҵ��ҳ��**********\n",t->name);
        for(i=0; i<m; i++)
        {
            printf("%d",t->size[i][0]);
            printf("\t%d\n",t->size[i][1]);
        }
        return head;
    }



}
//����
node* recycle(node *head)
{
    node *p,*pre=NULL;
    p=head;

    char recyclejobname[20];
    int i,j;
    printf("�������㵱ǰҪ���յ���ҵ����");
    scanf("%s",recyclejobname);
    while(p)
    {
        if(strcmp(recyclejobname,p->name)==0)//��ʱpΪ��Ӧ�Ļ�����ҵҳ��
        {
            break;
        }
        pre=p;
        p=p->next;
    }
    if(p==NULL)
    {
        printf("�޴���ҵ������ʧ�ܣ�\n");
        return head;
    }


    printf("����ҵ�޴洢��Ϣ�����ճɹ���\n");
    for(i=0; i<100; i++)
    {
        if(p->size[i][0]!=-1)//��Ϊֹͣ��
        {
            p->size[i][0]=0;
            j=p->size[i][1];//���
            page[j/Wlength][j%Wlength]=0;//�ҵ�λʾͼ��Ӧ�Ķ�ά������1��Ϊ0
        }
        else
            break;

    }
    page[BlockNum/Wlength][0]+=i; //�޸�ʣ�����
    //����ҳ��ҲҪ�ͷ�
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

//��ӡ��ǰλʾͼ
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
    printf("ʣ���������%d\n",page[--i][j]);

}

//��ʼ��
void initye()
{
    int i,j;
    int count=0;
    printf("������ϵͳ�ڴ�ռ�Ĵ�С��");
    scanf("%d",&Msize);
    printf("�������ֳ���16/32/64����");
    scanf("%d",&Wlength);
    printf("������������С��");
    scanf("%d",&Blength);

    BlockNum=Msize/Blength;//��������
    WordNum=BlockNum/Wlength+1;//�ֺ�

    srand(time(NULL));
    //��ʼ��λʾͼ
    for( i=0; i<WordNum; i++)
        for( j=0; j<Wlength; j++)
        {
            if(((i+1)*Wlength+j)>BlockNum)//���������������������ѭ��
                break;
            page[i][j]=rand()%2;//���ɸ���0/1
            if(page[i][j]==1)
                count++;//count���������Ϊ���ĸ���
        }
    page[i-1][j]=BlockNum-count;//λʾͼ�����һ�ֽڱ�ʾ����ʣ����п���
    print();

}

//ѡ��
void choose()
{
    node *head;
    head=NULL;
    while(1)
    {
        int c;
        printf("*********�ɱ��������**********\n");
        printf("   *     1.�ڴ����      *   \n"  );
        printf("   *     2.�ڴ�ȥ��      *   \n"  );
        printf("   *     0.�˳�          *   \n"  );
        printf("         ������ѡ��[ ]\b\b"       );
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
