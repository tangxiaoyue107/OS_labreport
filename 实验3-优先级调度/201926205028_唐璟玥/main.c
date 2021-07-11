#include <stdio.h>
#include <stdlib.h>
#include "01.h"
//��������
queue *input(queue *cc);
queue *insert(queue *cc,node *x);
queue *dele(queue *cc);
void youxian(queue *cc);
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
    printf("�������������\t");
    scanf("%d",&num);//�����������
    printf("������%d�����̵ģ�\n",num);
    printf("ID�� ���� ���ȼ� ����ʱ�� ִ��ʱ�䣨���ӣ� ��\n");
    while(num!=0)
    {
        node *onejincheng = (node *)malloc(sizeof(node));
        scanf("%d %s %d %d:%d %d",&onejincheng->id,onejincheng->name,&onejincheng->good,&onejincheng->arrive.hour,&onejincheng->arrive.min,&onejincheng->zx);
        onejincheng->next=NULL;
        cc = insert(cc,onejincheng);
        num--;
    }
    return cc;

}
//�������
queue *insert(queue *cc,node *x)
{
    if(cc->front==NULL) cc->front=cc->rear=x;//���λ��һ�����룬����Ϊ��
    else//�����в�Ϊ��
    {
        node *p = cc->front;
        node *pre = NULL;
        int ptime = (p->arrive.hour)*60+(p->arrive.min);
        int xtime = (x->arrive.hour)*60+(x->arrive.min);
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
//ɾ������
queue *dele(queue *cc)
{
    if(cc->rear==NULL) printf("����Ϊ�գ�\n");
    else
    {
        node *x;
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
//��������
void youxian(queue *cc)
{
    node *p,*pre;//����cc���еı���ָ��
    node *reastart,*reaend;//�������е���β
    p=cc->front;
    pre=NULL;
    //��һ������Ľ��̲��ؿ������ȼ�
    if(!pre)
    {
        p->start.hour=p->arrive.hour;
        p->start.min=p->arrive.min;
        p->finish.hour=p->start.hour+(p->arrive.min+p->zx)/60;
        p->finish.min=(p->arrive.min+p->zx)%60;
        p->zz=p->finish.hour*60+p->finish.min-p->arrive.hour*60-p->arrive.min;
        p->zzxs=(p->zz)*1.0/(p->zx);//�����*1.0���õ�zzxs��С����Ϊ.00
        pre=p;
        p=p->next;
    }
    while(p)//��pָ��Ĳ��ǵ�һ������Ҫ���Ǿ��������е����ȼ�����
    {

            int title = 1;//����ѭ���ı�־Ϊ1
            reastart=p;//�������е���ָ��Ϊp
            reaend=p; // �������е����һ������
            while(reaend->next && (reaend->arrive.hour*60+reaend->arrive.min)<=(pre->finish.hour*60+pre->finish.min))//�ҵ��������е�βָ��
            {//���realend->next�����ҿ�ʼʱ��С����һ������ʱ������ھ��������У�//�ҵ��������е�βָ��

                reaend = reaend->next;
            }
            while(title == 1)  // �ھ���������ð�����򣬽��������ȼ�������ǰ�棬��С�����ȼ����������
            {
                title=0;//��ʼΪ0
                reastart=p;
                while(reastart!=reaend)//���reastartָ�벻����reaend���������л�����һ�����Ͻ��
                {
                    if(reastart->good<reastart->next->good)//�Ƚ϶��ߵ�good����������good����ǰ���Good
                    {
                        // �����ڵ��ڲ���Ϣ��id
                        int data;
                        data=reastart->id;
                        reastart->id=reastart->next->id;
                        reastart->next->id=data;
                        // �����ڵ��ڲ���Ϣ������
                        for(int i=0; i<20; i++)
                        {
                            char namec;
                            namec=reastart->name[i];
                            reastart->name[i]=reastart->next->name[i];
                            reastart->next->name[i]=namec;
                        }
                        // �����ڵ��ڲ���Ϣ��good
                        data=reastart->good;
                        reastart->good=reastart->next->good;
                        reastart->next->good=data;
                        // �����ڵ��ڲ���Ϣ��arrive
                        data=reastart->arrive.hour;
                        reastart->arrive.hour=reastart->next->arrive.hour;
                        reastart->next->arrive.hour=data;

                        data=reastart->arrive.min;
                        reastart->arrive.min=reastart->next->arrive.min;
                        reastart->next->arrive.min=data;
                        // �����ڵ��ڲ���Ϣ��zx
                        data=reastart->zx;
                        reastart->zx=reastart->next->zx;
                        reastart->next->zx=data;
                        //����н���˵����Ҫ������һ��ѭ��������һ��ѭ�����ж��Ƿ���Ҫð��������
                        title = 1;
                    }
                    reastart=reastart->next;//reastart����һλ��һ���ڽ���good�ıȽϡ�
                }
            }

            if((p->arrive.hour*60+p->arrive.min)>=pre->finish.hour*60+pre->finish.min)
            //���p�ĵ���ʱ�����ǰһ�����̵Ľ���ʱ��
            {
                p->start = p->arrive;//p�Ŀ�ʼʱ�����p�ĵ���ʱ��
            }
            else
            {
                p->start = pre->finish;//p�Ŀ�ʼʱ������һ�����̵Ľ���ʱ��
            }

            p->finish.hour = (p->start.hour*60+p->start.min+ p->zx)/60;
            p->finish.min = (p->start.hour*60+p->start.min+p->zx)%60;
            p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;
            p->zzxs = (p->zz)*1.0/(p->zx);
            pre=p;
            p=p->next;
        }
    }

//�������
void output(queue *cc)
{
    node *p;
    p=cc->front;
    float sum_zz = 0;
    float sum_zzxs=0;
    int total = 0;
    printf("\nģ�����FCFS���ȹ�����������\n");
    printf("ID��\t����\t���ȼ� ����ʱ�� ִ��ʱ��(����)  ��ʼʱ�� ���ʱ�� ��תʱ�䣨���ӣ���Ȩ��תʱ�䣨ϵ������\n");
    while(p)
    {
        printf("%d\t",p->id);
        printf("%s\t",p->name);
        printf("%d\t",p->good);
        printf("%2d:%2d",p->arrive.hour,p->arrive.min);
        printf("\t");
        printf("%d�����ӣ�\t",p->zx);
        printf("%2d:%2d\t",p->start.hour,p->start.min);
        printf("%2d:%2d\t",p->finish.hour,p->finish.min);
        printf("%d�����ӣ�\t",p->zz);
        printf("%.2f",p->zzxs);
        printf("\n");
        sum_zz = sum_zz +p->zz;
        sum_zzxs = sum_zzxs + p->zzxs;
        total++;
        p=p->next;
    }
    printf("ϵͳ��ƽ����תʱ��Ϊ��\t\t\t\t\t\t%.2f�����ӣ�\n",sum_zz/total);
    printf("ϵͳ�Ĵ�Ȩƽ����תʱ��Ϊ��\t\t\t\t\t\t\t%.2f",sum_zzxs/total);

}
int main()
{
    queue *me;
    me=init();
    printf("��ʼ���ɹ���\n");
    me=input(me);
    youxian(me);
    output(me);
    getch();
    return 0;
}


/*
�������ݣ�
5001 p1 1 9:40  20
5004 p4 4 10:10 10
5005 p5 3 10:05 30
5002 p2 3 9:55  15
5003 p3 2 9:45  25
*/
