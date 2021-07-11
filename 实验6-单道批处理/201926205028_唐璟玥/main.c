#include <stdio.h>
#include <stdlib.h>
#include "01.h"
/*
���ڵ��� ϵͳ��ֻ�ܴ��һ����ҵ��
���װ��ϵͳ�ڴ����ҵ��ʱ�����ҵ���̵Ĵ�������ռϵͳ��Դ��
�Ӷ����̷������̵��Ƚ���CPUִ�С�
*/

//��������
queue *input(queue *cc);
queue *insert(queue *cc,linklist *x);
queue *dele(queue *cc);
void fcfs(queue *cc);
void output(queue *cc);

//���г�ʼ��
queue *init()
{
    queue *cc;
    cc = (queue *)malloc(sizeof(queue));
    cc->front=NULL;
    cc->rear = NULL;
    return cc;
}
//�������
queue *input(queue *cc)
{

    int num;
    printf("��������Ҫ��������ҵ����\t");
    scanf("%d",&num);//�����������
    printf("����������%d����ҵ�ģ�\n",num);
    printf("���� �뾮ʱ�� ����ʱ�䣺\n");
    while(num!=0)
    {
        linklist *onejincheng = (linklist *)malloc(sizeof(linklist));
        scanf("%s %d:%d %d",onejincheng->name,&onejincheng->arrive.hour,&onejincheng->arrive.min,&onejincheng->zx);
        onejincheng->next=NULL;
        cc = insert(cc,onejincheng);
        num--;
    }
    return cc;

}
//����
queue *insert(queue *cc,linklist *x)
{
    if(cc->front==NULL) cc->front=cc->rear=x;//���λ��һ�����룬����Ϊ��
    else//�����в�Ϊ��
    {
        linklist *p = cc->front;
        linklist *pre = NULL;
        while(p && ((p->arrive.hour)*60+(p->arrive.min))<=((x->arrive.hour)*60+(x->arrive.min)))//����ǰ����ʱ���x��ʱ��Ƚϴ�С�����xʱ�����ѭ���Ƚ���һ����㣬ֱ���ҵ���x����Ķ��н��
        {
            pre=p;
            p=p->next;
        }
        if(pre==NULL)//���ʱ�������ǵ�һ���������ʽ���ж���
        {
            x->next = cc->front;
            cc->front = x;
        }
        else//���뵽˳����Ӧʱ���
        {
            x->next = p;
            pre->next = x;
        }
    }
    return cc;
}
//ɾ����ҵ
queue *dele(queue *cc)
{
    if(cc->rear==NULL) printf("����Ϊ�գ�\n");
    else
    {
        linklist *x;
        x=cc->front;
        cc->front = cc->front->next;
        free(x);
        if(cc->front==NULL)
        {
            cc->rear=NULL;
        }
    }
    return cc;

}
//FCFS����
void fcfs(queue *cc)
{
    linklist *p=cc->front;
    linklist *pre=NULL;
    while(p)
    {
        if(!pre)//����pΪ��һ������
        {
            p->jobTime.hour = p->arrive.hour;//p����ҵ����ʱ�����p�Ŀ�ʼʱ��
            p->jobTime.min = p->arrive.min;

            p->processTime.hour = p->arrive.hour;//p�Ľ��̵���ʱ�����p�Ŀ�ʼʱ��
            p->processTime.min = p->arrive.min;

            p->finish.hour = (p->jobTime.hour*60+p->jobTime.min + p->zx)/60;//p�Ľ���ʱ����ǿ�ʼʱ��+ִ��ʱ��
            p->finish.min = (p->jobTime.hour*60+p->jobTime.min + p->zx)%60;

            p->jobWait=0;//��һ������/��ҵ�ȴ�Ϊ0
            p->processWait=0;

            p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;//p����תʱ��
            p->zzxs = 1.0000*p->zz / p->zx;//p����תϵ��

            pre=p; //p��pre�ƶ�������һ��ѭ��
            p=p->next;
        }
        else//���ǵ�һ������
        {
            if((p->arrive.hour*60+p->arrive.min)>=pre->finish.hour*60+pre->finish.min)
            //���p�ĵ���ʱ�����ǰһ�����̵Ľ���ʱ��
            {
                p->jobTime = p->arrive;//p�Ŀ�ʼʱ�����p�ĵ���ʱ��
                p->processTime = p->jobTime;//����������
            }
            else
            {
                p->jobTime = pre->finish;//p�Ŀ�ʼʱ������һ�����̵Ľ���ʱ��
                p->processTime = p->jobTime;//����������
            }
            p->finish.hour = (p->jobTime.hour*60+p->jobTime.min+ p->zx)/60;
            p->finish.min = (p->jobTime.hour*60+p->jobTime.min+p->zx)%60;

            p->jobWait = p->jobTime.hour*60+p->jobTime.min-p->arrive.hour*60-p->arrive.min;//��ҵ�ȴ�ʱ��
            p->processWait = 0;//���������� һ����ҵһ�����̣�����ȴ�

            p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;
            p->zzxs = 1.0000*p->zz/p->zx;
            pre=p;
            p=p->next;
        }
    }
}
//�������
void output(queue *cc)
{
    linklist *p;
    p=cc->front;
    float sum_zz = 0;
    float sum_zzxs=0;
    int total = 0;
    printf("\nģ����ҵFCFS���ȹ�����������\n");
    printf("���� �뾮ʱ�� ����ʱ��(����)  ��ҵ����ʱ��  ��ҵ���ȵȴ�ʱ��  ���̵���ʱ��  ���̵��ȵȴ�ʱ��   ���ʱ��   ��תʱ�䣨���ӣ�  ��Ȩ��תʱ�䣨ϵ������\n");
    while(p)
    {
        printf("%s\t",p->name);
        printf("%2d:%2d\t",p->arrive.hour,p->arrive.min);
        printf("%d�����ӣ�\t",p->zx);
        printf("%2d:%2d\t\t",p->jobTime.hour,p->jobTime.min);
        printf("%d�����ӣ�\t",p->jobWait);
        printf("%2d:%2d\t\t",p->processTime.hour,p->processTime.min);
        printf("%d�����ӣ�\t",p->processWait);
        printf("%2d:%2d\t\t",p->finish.hour,p->finish.min);
        printf("%d�����ӣ�\t",p->zz);
        printf("%.4f��ϵ����",p->zzxs);
        printf("\n");
        sum_zz = sum_zz +p->zz;
        sum_zzxs = 1.0000*sum_zzxs + p->zzxs;
        total++;
        p=p->next;
    }
    printf("ϵͳ��ƽ����תʱ��Ϊ��%.2f�����ӣ�\n",sum_zz/total);
    printf("ϵͳ�Ĵ�Ȩƽ����תʱ��Ϊ��%.4f",1.0*sum_zzxs/total);

}
int main()
{
    queue *me;
    me=init();
    printf("��ʼ���ɹ���\n");
    me=input(me);
    fcfs(me);
    output(me);
    getch();
    return 0;
}


/*
�������ݣ�
JOB1 8:00 120
JOB2 8:50 50
JOB3 9:00 10
JOB4 9:50 20
*/

