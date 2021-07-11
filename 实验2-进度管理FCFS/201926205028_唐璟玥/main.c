#include <stdio.h>
#include <stdlib.h>
#include "01.h"
//��������
queue *input(queue *cc);
queue *insert(queue *cc,node *x);
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
    printf("�������������\t");
    scanf("%d",&num);//�����������
    printf("������%d�����̵ģ�\n",num);
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ� ��\n");
    while(num!=0)
    {
        node *onejincheng = (node *)malloc(sizeof(node));
        scanf("%d %s %d:%d %d",&onejincheng->id,onejincheng->name,&onejincheng->arrive.hour,&onejincheng->arrive.min,&onejincheng->zx);
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
void fcfs(queue *cc)
{
    node *p=cc->front;
    node *pre=NULL;
    while(p)
    {
        if(!pre)//����pΪ��һ������
        {
            p->start.hour = p->arrive.hour;//p�ĵ���ʱ�����p�Ŀ�ʼʱ��
            p->start.min = p->arrive.min;
            p->finish.hour = (p->start.hour*60+p->start.min + p->zx)/60;//p�Ľ���ʱ����ǿ�ʼʱ��+ִ��ʱ��
            p->finish.min = (p->start.hour*60+p->start.min + p->zx)%60;
            p->zz = p->finish.hour*60+p->finish.min - p->arrive.hour*60-p->arrive.min;//p����תʱ��
            p->zzxs = p->zz / p->zx;//p����תϵ��
            pre=p; //p��pre�ƶ�������һ��ѭ��
            p=p->next;
        }
        else//���ǵ�һ������
        {
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
            p->zzxs = p->zz/p->zx;
            pre=p;
            p=p->next;
        }
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
    printf("ID��\t���� ����ʱ�� ִ��ʱ��(����)  ��ʼʱ�� ���ʱ�� ��תʱ�䣨���ӣ���Ȩ��תʱ�䣨ϵ������\n");
    while(p)
    {
        printf("%d\t",p->id);
        printf("%s\t",p->name);
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
    printf("ϵͳ��ƽ����תʱ��Ϊ��\t\t\t\t\t%.2f�����ӣ�\n",sum_zz/total);
    printf("ϵͳ�Ĵ�Ȩƽ����תʱ��Ϊ��\t\t\t\t\t\t%.2f",sum_zzxs/total);

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
5001 p1 9:40 20
5004 p4 10:10 10
5005 p5 10:05 30
5002 p2 9:55 15
5003 p3 9:45 25
*/

/*node *p,*pre;//����cc���еı���ָ��
    node *reastart,*reaend;//�������е���β�Լ�����������reastart��ǰһ����ַ��ǰһ����ַ
    p=cc->front;
    pre=NULL;
    if(!pre)//�����һ�����̣���һ���������辺�������Ե���ʱ������ģ�Ҳ����cc->front��һ����ʼ����
    {
        p->start.hour = p->arrive.hour;
        p->start.min = p->arrive.min;
        p->finish.hour = (p->arrive.hour*60+p->arrive.min)/60;
        p->finish.min = (p->arrive.hour*60+p->arrive.min)%60;
        p->zz = p->finish.hour*60+p->finish.min-p->arrive.hour*60-p->arrive.min;
        p->zzxs = p->zz*1.0/p->zx;
        pre=p;
        p=p->next;
    }
    while(p)//��pָ��Ĳ��ǵ�һ������Ҫ���Ǿ��������е����ȼ�����
    {
        reastart = p;//�������е���ָ��Ϊp
        reaend = p;
        while(reaend->next && (reaend->arrive.hour*60+reaend->arrive.min)<=(pre->finish.hour*60+pre->finish.min))//�ҵ��������е�βָ��
        {//���realend->next�����ҿ�ʼʱ��С����һ������ʱ������ھ���������

                   reaend = reaend->next;
        }






        //�ҵ��������������Ǹ�good��ַΪtemp
        node *pxulie=reastart;//��¼�����������е�ָ��pxulie
        node *prexulie=pre;//�������е�reastartǰһ�����ĵ�ַΪpre
        node *temppre;//��¼����good�ĵ�ַǰһ������ַ
        node *temp;//��¼����good�ĵ�ַ
        while(pxulie->next) //���pxulie����һ��ָ�����
        {
            if(pxulie->good<pxulie->next->good)//�Ƚ϶��ߵ�good
            {
                temppre = pxulie;//��¼����good�ĵ�ַǰһ������ַ
                temp=pxulie->next;//��¼����good�ĵ�ַ
            }
            prexulie =pxulie;//�ƶ�
            pxulie=pxulie->next;//�ƶ�
        }
        //�������б�����һ�飬�ҵ������good����ַtemp
        //��temp��ַ�ŵ���ַ��һ��
        temppre->next = temp->next;
        temp->next = reastart;
        pre->next = temp;
        p=temp;//��temp��Ϊ��һ�ֵ�p

�� 21:14:28
    node *p,*pre;//����cc���еı���ָ��
    node *reastart,*reaend;//�������е���β�Լ�����������reastart��ǰһ����ַ��ǰһ����ַ
    p=cc->front;
    pre=NULL;
    if(!pre)//�����һ�����̣���һ���������辺�������Ե���ʱ������ģ�Ҳ����cc->front��һ����ʼ����
    {
        p->start.hour = p->arrive.hour;
        p->start.min = p->arrive.min;
        p->finish.hour = (p->arrive.hour*60+p->arrive.min)/60;
        p->finish.min = (p->arrive.hour*60+p->arrive.min)%60;
        p->zz = p->finish.hour*60+p->finish.min-p->arrive.hour*60-p->arrive.min;
        p->zzxs = p->zz*1.0/p->zx;
        pre=p;
        p=p->next;
    }
    while(p)//��pָ��Ĳ��ǵ�һ������Ҫ���Ǿ��������е����ȼ�����
    {
        reastart = p;//�������е���ָ��Ϊp
        reaend = p;
        while(reaend->next)//�ҵ��������е�βָ��
        {
            if((reaend->arrive.hour*60+reaend->arrive.min)<=(pre->finish.hour*60+pre->finish.min))//�����ʼʱ��С����һ������ʱ������ھ���������
               {
                   reaend = reaend->next;
               }
        }
        //�ҵ��������������Ǹ�good��ַΪtemp
        node *pxulie=reastart;//��¼�����������е�ָ��pxulie
        node *prexulie=pre;//�������е�reastartǰһ�����ĵ�ַΪpre
        node *temppre;//��¼����good�ĵ�ַǰһ������ַ
        node *temp;//��¼����good�ĵ�ַ
        while(pxulie->next) //���pxulie����һ��ָ�����
        {
            if(pxulie->good<pxulie->next->good)//�Ƚ϶��ߵ�good
            {
                temppre = pxulie;//��¼����good�ĵ�ַǰһ������ַ
                temp=pxulie->next;//��¼����good�ĵ�ַ
            }
            prexulie =pxulie;//�ƶ�
            pxulie=pxulie->next;//�ƶ�
        }
        //�������б�����һ�飬�ҵ������good����ַtemp
        //��temp��ַ�ŵ���ַ��һ��
        temppre->next = temp->next;
        temp->next = reastart;
        pre->next = temp;

        p=temp;//��temp��Ϊ��һ�ֵ�p
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
            p->zzxs = p->zz/p->zx;
            pre=p;
            p=p->next;
        pre=p;
        p=p->next;
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


    */

