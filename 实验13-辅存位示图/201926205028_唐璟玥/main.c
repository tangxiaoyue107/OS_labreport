#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "01.h"

int disksize;//Ӳ�̴�С
int wordsize;//�ֳ�
int blocksize;//������С
int headnumber;//��ͷ��
int sectornumber;//������
int cylinder;//ÿ�������ϵ�������
int sum;//��������
int availablesector;//����������
int map[4096][4096];
int line;
linklist* work = NULL;

//��ӡ
void print()
{
    printf("\t\t******************************����ʹ�����******************************\n");
    printf("%-3c",' ');
    //��ӡ��ͷ
    for(int i=0;i<wordsize;i++)
    {
        printf("%-3d",i);
    }
    putchar('\n');

    int cnt=0;//��ֹ���
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
    printf("����ʣ����п�����%d\n",availablesector);
}
//����
void allocate()
{
    printf("����������ռ����ҵ���ֺ���Ҫ���丨��ռ�Ĵ�С����λ��K����");
    linklist *tmp=(linklist*)malloc(sizeof(linklist));
    scanf("%s %d",&tmp->name,&tmp->size);
    if(tmp->size > availablesector*blocksize)//�������ռ�Ĵ�С ���� ���еĿ��пռ�
    {
        printf("��������ʧ�ܣ�\n");
        return ;
    }

    printf("��������ɹ���\n");
    int cnt=0;
    int k=0;
    int ss=tmp->size/blocksize+(tmp->size%blocksize?1:0);//��������ռ����Ҫ���������
    for(int i=0;i<line && k<ss;i++)
    {
        for(int j=0;j<wordsize && cnt < sum && k<ss;j++)
        {
            if(map[i][j]==0){
                map[i][j]=1;
                tmp->a[k]=i*wordsize+j;//a�����¼������������
                tmp->zihao[k]=i;//�ֺ�
                tmp->weihao[k]=j;//λ��
                tmp->zhu[k]=(i*wordsize+j)/cylinder;//�����
                tmp->citou[k]=(i*wordsize+j)%cylinder/sectornumber;//��ͷ
                tmp->shanqu[k]=(i*wordsize+j)%cylinder%sectornumber;//����
                k++;
                availablesector--;
            }
        }
    }
    print();
    printf("\t\t********************%s������ĸ���********************\n",tmp->name);
    printf("  ���  ��  ��  λ  �����  ��ͷ��  ������\n");
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
//����
void recycle()
{
    linklist* q=work;
    printf("��ǰ�������ҵ��");
    while(q){
        printf("%s->",q->name);
        q=q->next;
    }
    putchar('\n');
    printf("Ҫ���յ���ҵ����");
    char name[10];
    scanf("%s",name);
    linklist* pre=work;
    linklist* p=work;
    while(p != NULL && strcmp(p->name,name)!=0){
        pre=p;
        p=p->next;
    }
    if(p==NULL){
        printf("����ʧ�ܣ�\n");
        return;
    }
    printf("���ճɹ���\n");
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
    printf("------201926205028 �ƭZ�h 19�����ݿ�ѧ������ݼ���1��-----\n");
    printf("�����븨��ռ�Ĵ�С����λ��K�����ֳ���32 or 64���Ϳ鳤����λ��K����");
    scanf("%d %d %d",&disksize,&wordsize,&blocksize);
    printf("������ø���Ӳ�̵Ĵŵ�������ͷ������ÿ���ŵ�����������");
    scanf("%d %d",&headnumber,&sectornumber);

    sum=availablesector=disksize/blocksize;
    line=sum/wordsize+(sum%wordsize?1:0);
    cylinder=headnumber*sectornumber;//һ�������ܹ��ж�������

    //��ʼ��
    for(int i=0;i<sum;i+=3){
            map[i/wordsize][i%wordsize] = 1;
            availablesector--;
    }
    print();
    //�˵�
    while(flag)
    {
        printf("***************������ȹ���***************\n");
        printf("      *   1.�ռ����               *\n");
        printf("      *   2.�ռ�ȥ��               *\n");
        printf("      *   0.�˳�                   *\n");
        printf("            ������ѡ��[ ]\b\b");
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

