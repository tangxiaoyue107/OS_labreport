#include <stdio.h>
#include <stdlib.h>
#include "01.h"
//���г�ʼ��
queue *init();
//�������
queue *insertfenqu(queue *cc,node *x);
//ɾ������
queue *delefenqu(queue *cc);
//�����������
queue *fenquinput(queue *cc);
//��ӡ����״̬
void fenquoutput(queue *cc);
//������ҵ
queue *insertzuoye(queue *aa,job *x);
//������ҵ
queue *zuoyeinput(queue *aa);
//��ӡ��ҵ
void zuoyeoutput(queue *aa);
//����
void fenpei(queue *aa,queue *cc);
//����
void huishou(queue *cc);


//���г�ʼ��
queue *init()
{
    queue *cc;
    cc=(queue*)malloc(sizeof(queue));
    cc->front=NULL;
    cc->rear=NULL;
    return cc;
}
//�������
queue *insertfenqu(queue *cc,node *x)
{
    if(cc->front==NULL)
    {
        cc->front=cc->rear=x;
        return cc;
    }
    else
    {
        node *p=cc->front;
        node *pre=NULL;
        while(p->next)
        {
            pre=p;
            p=p->next;
        }
        //���ڶ��к���
        p->next=x;
        x->next=NULL;
    }
    return cc;
}
//ɾ������
queue *delefenqu(queue *cc)
{
    cc->front=cc->front->next;
    return cc;
}
//�����������
queue *fenquinput(queue *cc)
{
    int num;
    node *onefenqu;
    printf("������ϵͳ�ķ���������");
    scanf("%d",&num);
    printf("���������룺\n������ ��С ��ʼ\n");
    while(num)
    {
        onefenqu=(node*)malloc(sizeof(node));
        scanf("\t%d\t",&onefenqu->id);
        scanf("%d\t",&onefenqu->size);
        scanf("%d",&onefenqu->address);
        onefenqu->station[0]=0;
        onefenqu->next=NULL;
        cc=insertfenqu(cc,onefenqu);
        num--;
    }
    return cc;
}
//��ӡ����״̬
void fenquoutput(queue *cc)
{
    node *p=cc->front;
    printf("************��ӡ������Ϣ************\n");
    printf("������\t��С<KB> ��ʼ<KB>     ״̬\n");
    while(p)
    {
        printf("%3d\t",p->id);
        printf("%4d\t",p->size);
        printf("%4d\t\t",p->address);
        if(p->station[0]==0) printf("%d\n",p->station[0]);
        else printf("JOB%d\n",p->station[0]);
        p=p->next;
    }
}
//������ҵ
queue *insertzuoye(queue *aa,job *x)
{
    if(aa->front==NULL)
    {
        aa->front=aa->rear=x;
        return aa;
    }
    else
    {
        job *p=aa->front;
        job *pre=NULL;
        while(p->next)
        {
            pre=p;
            p=p->next;
        }
        //���ڶ��к���
        p->next=x;
        x->next=NULL;
    }
    return aa;
}
//������ҵ
queue *zuoyeinput(queue *aa)
{
    int num,x,size;
    job *onefenqu;
    x=1;
    printf("��������ҵ������");
    scanf("%d",&num);
    printf("��������%d����ҵ����Ϣ��\n",num);
    while(num)
    {
        printf("��������ҵ%d�Ĵ�С��",x);
        onefenqu = (job *)malloc(sizeof(job));
        onefenqu->id = x;
        onefenqu->name = x;
        onefenqu->next=NULL;
        scanf("%d",&size);
        onefenqu->size =size;
        aa = insertzuoye(aa,onefenqu);
        num--;
        x++;
    }
    return aa;
}

//��ӡ��ҵ
void zuoyeoutput(queue *aa)
{
    job *p=aa->front;
    printf("��ӡ����ҵ����Ϣ��\n");
    printf("��ҵ��\t��ҵ��С\n");
    while(p)
    {
        printf("JOB%d\t",p->name);
        printf("%d\n",p->size);
        p=p->next;
    }
}
//����
void fenpei(queue *aa,queue *cc)
{
    job *onezuoye = aa->front;
    node *onefenqu = cc->front;
    node *choose=NULL;
    while(onezuoye)
    {
        //printf("�ȷ���JOB%d���ڴ�,����Ҫ�ڴ�%d(KB)\n",onezuoye->id,onezuoye->size);
        while(onefenqu)
        {
            //printf("��������������%d������%d(KB)�ڴ�\n",onefenqu->id,onefenqu->size);
            if(onefenqu->size>=onezuoye->size && onefenqu->station[0]==0)
            {
                //printf("����%d����",onefenqu->id);
                if(choose!=NULL)
                {
                    if(choose->size<onefenqu->size) ;
                    else choose = onefenqu;
                }
                else choose = onefenqu;
                //printf("��һ��chooseΪ����%d",choose->id);
            }
            onefenqu=onefenqu->next;
        }
        if(choose!=NULL)
        {
            choose->station[0] = onezuoye->id;
        }
        else printf("\nJOB%d���㹻�ռ���룡",onezuoye->id);
        choose=NULL;
        onefenqu = cc->front;
        onezuoye = onezuoye->next;
    }
}
//����
void huishou(queue *cc)
{
    char flag;
    int id;
    node *onefenqu = cc->front;
    printf("�Ƿ���Ҫ���գ���y/n��:");
    scanf(" %c",&flag);
    printf("%c",flag);
    while(flag == 'y' || flag == 'Y')
    {
        printf("��������Ҫ���յ���ҵ����JOB");
        scanf("%d",&id);

        while(onefenqu)
        {
            if(onefenqu->station[0] == id)
            {
                onefenqu->station[0]=0;
                break;
            }
            onefenqu=onefenqu->next;
        }
        if(onefenqu==NULL)
        {
            printf("û���ҵ����������ҵ��");
        }
        fenquoutput(cc);
        printf("�Ƿ���Ҫ���գ���y/n��:");
        scanf(" %c",&flag);
        onefenqu = cc->front;
    }
}
int main()
{
    queue *cc;
    queue *aa;
    cc=init();
    aa=init();
    cc=fenquinput(cc);
    fenquoutput(cc);
    aa=zuoyeinput(aa);
    zuoyeoutput(aa);
    fenpei(aa,cc);
    fenquoutput(cc);
    huishou(cc);
    getch();
    return 0;

}
/*
    1   12  20
    2   32  32
    3   64  64
    4   128 128
    5   100 256
*/
