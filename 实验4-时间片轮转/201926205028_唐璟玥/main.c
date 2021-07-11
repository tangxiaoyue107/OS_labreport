#include <stdio.h>
#include <stdlib.h>

//ʱ��ṹ��
typedef struct data
{
    int hour;
    int min;
}time;
//���̽ṹ��
typedef struct link_node
{
    int id;//���
    char name[20];//������
    time arrive;//�����������ʱ��
    int zx;//ִ��ʱ��
    time start;//��ʼʱ��
    time first;//�״ο�ʼʱ��
    int have_finished;//�����ʱ��
    time arr;//ÿ�ֵ���ʱ��
    time finish;//�������ʱ��
    int zz;//��תʱ��=���ʱ��-�����������ʱ��
    float zzxs;//��Ȩ��תϵ��=��תʱ��/ִ��ʱ��
    int flag;//�Ƿ����
    struct link_node *next;
}node;
//����
typedef struct
{
    node *front;
    node *rear;
}queue;
//���г�ʼ��
queue *init()
{
    queue *cc;
    cc=(queue *)malloc(sizeof(queue));
    cc->front=NULL;
    cc->rear=NULL;
    return cc;
}
//�������
queue *insert(queue *cc,node *x)
{
    node *p;
    if(cc->front==NULL)
    {
        cc->front=cc->rear=x;
        return cc;
    }
    else if((x->arrive.hour<cc->front->arrive.hour)||((x->arrive.hour==cc->front->arrive.hour)&&(x->arrive.min<cc->front->arrive.min)))
    {
        x->next=cc->front;
        cc->front=x;
        return cc;
    }
    else
    {
        p=cc->front;
        if((p->next)&&((x->arrive.hour>p->next->arrive.hour)||((x->arrive.hour==p->next->arrive.hour)&&(x->arrive.min>p->next->arrive.min))))
            p=p->next;
        if(p->next==NULL)
        {
            p->next=x;
            cc->rear =x;
            return cc;
        }
        else
        {
            x->next=p->next;
            p->next=x;
            return cc;
        }
    }
}

queue *input(queue *cc)
{
    printf("�������������");
    int n;
    scanf(" %d",&n);
    printf("������%d�����̵ģ�",n);
    printf("ID��	����	����ʱ��  ִ��ʱ�䣨���ӣ�\n");
    int x;
    node *a;
    char m[10];
    while(n--)
    {
        scanf("%d",&x);
        a=(node*)malloc(sizeof(node));
        a->id=x;
        scanf(" %s",&a->name);
        scanf(" %s",&m);
        scanf(" %d",&a->zx);
        a->flag=0;
        a->have_finished=0;
        if(m[1]!=':')
        {
            a->arrive.hour=((m[0]-'0')*10+m[1]-'0');
            a->arrive.min=((m[3]-'0')*10+m[4]-'0');
        }
        else
        {
            a->arrive.hour=(m[0]-'0');
            a->arrive.min=((m[2]-'0')*10+m[3]-'0');
        }
        a->first.hour=0;
        a->next=NULL;
        cc=insert(cc,a);
    }
    return cc;
}


queue *dele(queue *cc)
{
    cc->front=cc->front->next;
    return cc;
}

void shijianpian(queue *cc)
{
    printf("������ʱ��Ƭ��ʱ�䣺");
    int t;
    scanf(" %d",&t);
    node *p;
    node *pnext;
    node *ke,*neng;
    int a;
    int n=1;
    p=cc->front;
    p->start.hour =p->arrive.hour ;
    p->start.min =p->arrive.min ;
    pnext=p;
    p->first.hour=p->arrive.hour;
    p->first.min=p->arrive.min;
    p->arr.hour=p->arrive.hour;
    p->arr.min=p->arrive.min;
    while(pnext->next->flag==0)//���pnext��һ�����̻�δ����
    {
        p=pnext;
        pnext=p->next;//pnext����δp����һ��
        if((p->have_finished+t)<p->zx)//���p�������ʱ�����t��δ����ִ��ʱ�䣬��ô��һ�ֵ�t�������еĵ�һ��p��֮����ת
        {
            p->have_finished=p->have_finished+t;//p�������ʱ������t
            a=(p->start.min+t)/60;
            if(!p->first.hour)
            {
                p->first.hour=p->start.hour;
                p->first.min=p->start.min;
            }
            pnext->start.min=(p->start.min+t)%60;//p��һ��pnext��ÿ�ֿ�ʼʱ���ټ�����תʱ��t
            pnext->start.hour=a+p->start.hour;
        }
        else//���p�����ʱ�����t���ڵ���ִ��ʱ�䣬˵����һ��ʱ���t���������������̡�p������һ������Լ��Ľ��̣�ʣ��ʱ���ٿ�ʼpnext��ʱ��Ƭ;
        {
            a=p->zx-p->have_finished;//aΪpִ����ϣ�ʱ��Ƭʣ�µ�ʱ��
            pnext->start.min=(p->start.min+a)%60;//pnext��һ���Ŀ�ʼʱ��Ϊp��һ�ֿ�ʼʱ�����ʣ�����ʱ��
            pnext->start.hour=p->start.hour+(pnext->start.min+a)/60;
            p->finish.min=(p->start.min+a)%60;//p�����ʱ��Ϊ��һ�ֵĿ�ʼʱ�����ʣ��ʱ��
            a=(p->start.min+a)/60;
            p->finish.hour=p->start.hour+a;
            p->have_finished=p->zx;//��ʱ��p�Ѿ�ִ����ϣ������ʱ���Ϊִ��ʱ��
            p->zz=(p->finish.hour-p->arrive.hour)*60+p->finish.min-p->arrive.min;
            p->zzxs=(float)p->zz/p->zx;
            p->flag=1;//flagΪ1�����������Ϊ�ѽ���
        }

        ke=p->next;//��ʾ��ǰʱ��Ƭ��ÿ�ֿɴ�ӡ�Ľ��βָ��
        neng=p->next;//��ʾ��ǰʱ��Ƭ��ÿ�ֿɴ�ӡ�Ľ����ָ��
        while(ke->next&&ke->next->flag==0&&(ke->next->arrive.hour<pnext->start.hour||(ke->next->arrive.hour==pnext->start.hour&&ke->next->arrive.min<=pnext->start.min)))
        {
            ke=ke->next;//���keָ��Ľ�㵽��ʱ�����ڵڶ���pnext�Ŀ�ʼʱ�䣬����Ҫ�����ӡ���о���
        }
        printf("��%d��ִ�к;������н����\n",n++);
        printf("\n");
        printf("ID��	����	����ʱ��  ��ִ��ʱ�䣨���ӣ�  ��ǰ��ʼʱ��  �����ʱ�䣨���ӣ�  ʣ�����ʱ�䣨���ӣ�\n");
        printf("%02d      %s       %02d:%02d       %02d�����ӣ�         %02d:%02d          %02d�����ӣ�          %02d�����ӣ�\n",p->id,p->name,p->arrive.hour,p->arrive.min,p->zx,p->start.hour,p->start.min,p->have_finished,p->zx-p->have_finished);
        while(neng!=ke)
        {
            printf("%02d      %s       %02d:%02d       %02d�����ӣ�         00:00          %02d�����ӣ�          %02d�����ӣ�\n",neng->id,neng->name,neng->arrive.hour,neng->arrive.min,neng->zx,neng->have_finished,neng->zx-neng->have_finished);
            neng=neng->next;
        }
        printf("%02d      %0s       %02d:%02d       %02d�����ӣ�         00:00          %02d�����ӣ�          %02d�����ӣ�\n",neng->id,neng->name,neng->arrive.hour,neng->arrive.min,neng->zx,neng->have_finished,neng->zx-neng->have_finished);
        printf("\n");

        cc->front=cc->front->next;//ʱ����ת֮����˵�ָ��������һ����㣬������ת��
        p->next=NULL;//��ǰ�����Ҫ�����������һ����㡣�ȴ��¼���ʱ����ת��
        if(ke->next)
        {
            ke=ke->next;//listendҲ����һ����ָ��ǰ��ӡ���еĵ�һ��
            neng->next=p;//liststart��ָ�����һ����㣬Ҳ������һ�����걻�ŵ�������һ����㡣
            p->next=ke;//�������������еĽ���ѭ����ʹ��ʱ����ת
        }
        else
        {
            ke->next=p;
        }
    }
    p=pnext;//��������������г����һ���������Ѿ���ת��ϣ�ֻʣ�����һ��pָ��Ľ��flag��δ���
    while(p->flag==0)//�����һ�����д���
    {
        if((p->have_finished+t)<p->zx)
        {
            p->have_finished=p->have_finished+t;
        }
        else
        {
            a=p->zx-p->have_finished;
            p->finish.min=(p->start.min+a)%60;
            a=(p->start.min+a)/60;
            p->finish.hour=p->start.hour+a;
            p->have_finished=p->zx;
            p->zz=(p->finish.hour-p->arrive.hour)*60+p->finish.min-p->arrive.min;
            p->zzxs=(float)p->zz/p->zx;
            p->flag=1;
        }
        printf("��%d��ִ�к;������н����\n",n++);
        printf("\n");
        printf("ID��	����	����ʱ��  ��ִ��ʱ�䣨���ӣ�  ��ǰ��ʼʱ��  �����ʱ�䣨���ӣ�  ʣ�����ʱ�䣨���ӣ�\n");
        printf("%02d      %s       %02d:%02d       %02d�����ӣ�         %02d:%02d          %02d�����ӣ�          %02d�����ӣ�\n",p->id,p->name,p->arrive.hour,p->arrive.min,p->zx,p->start.hour,p->start.min,p->have_finished,p->zx-p->have_finished);
        printf("\n");
        if(p->flag==0)
        {
            p->start.min=(p->start.min+t)%60;
            p->start.hour=(p->start.min+t)/60+p->start.hour;
        }
    }
}

void output(queue *cc)
{
    node *p,*pre,*pr,*q;

    p=cc->front;
    q=p;
    pre=p;
    while(pre->next)
    {
        pr=pre;
        pre=pre->next;
    }
    pr->next=NULL;
    cc->front=pre;
    pre->next=p;
    q=cc->front;
    while(p->next)
    {
        pre=p;
        while(pre->next)
        {
            pr=pre;
            pre=pre->next;
        }
        pr->next=NULL;
        q->next=pre;
        pre->next=p;
        q=q->next;
    }

    p=cc->front;
    float x=0;
    float y=0;
    int count=0;
    printf("ģ�����FCFS���ȹ�����������\n");
    printf("ID��	����	����ʱ��  ִ��ʱ�䣨���ӣ� �״ο�ʼʱ��   ���ʱ��      ��תʱ�䣨���ӣ�    ��Ȩ��תʱ�䣨ϵ����\n");
    while(p)
    {
        printf("%02d     %s       %02d:%02d       %02d               %02d:%02d       %02d:%02d        %02d�����ӣ�             \t%.2f \n",p->id,p->name,p->arrive.hour,p->arrive.min,p->zx,p->first.hour,p->first.min,p->finish.hour,p->finish.min,p->zz,p->zzxs);
        p=p->next;
    }
    p=cc->front;
    while(p)
    {
        x+=p->zz;
        y+=p->zzxs;
        count+=1;
        p=p->next;
    }
    x=(float)x/count;
    y=(float)y/count;
    printf("ϵͳƽ����תʱ��                                                  \t%.2f\n",x);
    printf("ϵͳƽ����Ȩ��תʱ��                                                            \t\t%.2f\n",y);
}

int main()
{
    queue *me;
    me=init();
    me=input(me);
    shijianpian(me);
    output(me);
    getch();
    return 0;
}
/*
5001 p1 9:40 20
5004 p4 10:00 10
5005 p5 10:05 30
5002 p2 9:55 15
5003 p3 9:45 25
*/
