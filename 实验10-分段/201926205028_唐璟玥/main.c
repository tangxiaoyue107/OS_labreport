#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "01.h"
node* initMemory();// ��ʼ���ڴ�ռ�
void allocate(node *head);//����˵�
void goodAllocation(node* head,int size,char c[10]);
void badAllocation(node* head,int size,char c[10]);
void firstAllocation(node* head,int size,char c[10]);
void print(node* head);//��ӡ���� �ѷ���δ����ķ��������
void reorder(node* head);//�޸�id
void recyle(node* head);//����

// ��ʼ���ڴ�ռ�
node* initMemory()
{
    //��ͷ�ڵ㣬headָ����ǿ��з�����
    node* head=(node*)malloc(sizeof(node));
    head->next = NULL;
    node* q=(node*)malloc(sizeof(node));
    printf("�������ڴ��С��");
    scanf("%d",&memory.size);
    printf("��������ʼ��ַ��");
    scanf("%d",&memory.address);
    q->id=1;
    q->size=memory.size;
    q->address=memory.address;
    strcpy(q->flag,"����");
    q->next=NULL;
    head->next=q;
    return head;
}
//����˵�
void allocate(node *head)
{
    char name[5];
    int size;
    int c;
    printf("*********�����㷨**********\n");
    printf("   *     1.���ȷ����㷨      *   \n");
    printf("   *     2.���ŷ����㷨      *   \n");
    printf("   *     3.������㷨      *   \n");
    printf("         ������ѡ��[ ]\b\b");
    scanf("%d",&c);
    print(head);
    printf("��������ҵ��:");
    scanf("%s",&name);
    printf("������%s��Ҫ����������С:",name);
    scanf("%d",&size);
    switch(c)
    {
        case 1:
            firstAllocation(head,size,name);
            break;
        case 2:
            goodAllocation(head,size,name);
            break;
        case 3:
            badAllocation(head,size,name);
            break;
    }
}
//���ʷ�
void goodAllocation(node* head,int size,char c[10])
{
    node* mark=NULL;
    int m,n,count=1,i=0;
    segmentNode *t;
    t=(segmentNode*)malloc(sizeof(segmentNode));
    node* new;
    char a[5]="0";
    node* p;
    p=head->next;
    int rest;
    printf("������Ҫ�ֳɼ��Σ�");
    scanf("%d",&m);
    while(m!=0)
    {
        m--;
        printf("ʣ��%dKB���ڴ棬�������%d�εĴ�С��",size,count);
        scanf("%d",&n);
        size=size-n;
        while(p)
        {
            if((n<=p->size)&&(p->flag[0]!='j')&&(p->flag!='J'))      //�ҵ����ʴ�Сδ����λ��
            {
                if(mark==NULL)
                    mark=p;
                else if(p->size<mark->size)
                    mark=p;
            }
            p=p->next;
        }

        if((n<=mark->size)&&(mark->flag[0]!='j')&&(mark->flag[0]!='J'))
        {
            rest=mark->size-n;
            if(rest==0)
            {
                strcpy(mark->flag,c);
                mark->flag[4]='0'+count-1;
                mark->flag[5]='\0';
            }

            else
            {
                mark->size=n;
                strcpy(mark->flag,c);
                mark->flag[4]='0'+count-1;
                mark->flag[5]='\0';           //�ѷ��䲿�ִ���
                new=(node*)malloc(sizeof(node));
                new->address=mark->address+n;
                new->size=rest;
                strcpy(new->flag,a);


                new->next=mark->next;
                mark->next=new;
                reorder(head);
            }
        }
        t->a[i][0]=i;
        t->a[i][1]=n;
        t->a[i][2]=mark->address;
        i++;
        count++;
        print(head);
    }
    t->a[i][0]=-1;
    t->next=h;
    h=t;
    printf("\n����ɹ���\n");
    printf("************��ӡ%s�α�************\n",c);
    printf("�κ�\t�γ�\t��ַ\n");
    for(i=0; i<10; i++)
    {
        if(t->a[i][0]!=-1)
            printf("%d\t%d\t%d\n",t->a[i][0],t->a[i][1],t->a[i][2]);
        else
            break;
    }
}
//�����
void badAllocation(node* head,int size,char c[10])
{
    node* mark=NULL;
    node* new;
    segmentNode *t;
    t=(segmentNode*)malloc(sizeof(segmentNode));
    char a[5]="0";
    node* p;
    p=head->next;
    int rest;
    int m,n,i=0,count=1;
    printf("������Ҫ�ֳɼ��Σ�");
    scanf("%d",&m);
    while(m!=0)
    {
        m--;
        printf("ʣ��%dKB���ڴ棬�������%d�εĴ�С��",size,count);
        scanf("%d",&n);
        size=size-n;
        while(p)
        {
            if((n<=p->size)&&(p->flag[0]!='j')&&(p->flag!='J'))      //�ҵ����ʴ�Сδ����λ��
            {
                if(mark==NULL)
                    mark=p;
                else if(p->size>mark->size)
                    mark=p;
            }
            p=p->next;
        }
        if((n<=mark->size)&&(mark->flag[0]!='j')&&(mark->flag[0]!='J'))
        {
            rest=mark->size-size;
            if(rest==0)
            {
                strcpy(mark->flag,c);
                mark->flag[4]='0'+count-1;
                mark->flag[5]='\0';
            }
            else
            {
                mark->size=n;
                strcpy(mark->flag,c);
                mark->flag[4]='0'+count-1;
                mark->flag[5]='\0';           //�ѷ��䲿�ִ���
                new=(node*)malloc(sizeof(node));
                new->address=mark->address+n;
                new->size=rest;
                strcpy(new->flag,a);
                new->next=mark->next;
                mark->next=new;
                reorder(head);
            }
        }
        t->a[i][0]=i;
        t->a[i][1]=n;
        t->a[i][2]=mark->address;
        i++;
        count++;
        print(head);
    }
    t->a[i][0]=-1;
    t->next=h;
    h=t;
    printf("\n����ɹ���\n");
    printf("************��ӡ%s�α�************\n",c);
    printf("�κ�\t�γ�\t��ַ\n");
    for(i=0; i<10; i++)
    {
        if(t->a[i][0]!=-1)
            printf("%d\t%d\t%d\n",t->a[i][0],t->a[i][1],t->a[i][2]);
        else
            break;
    }
}
//���ȷ���
void firstAllocation(node* head,int size,char c[10])
{
    node* new;
    segmentNode *t=NULL;
    int k;
    t=(segmentNode*)malloc(sizeof(segmentNode));
    int m,n,count=1;
    int i=0;
    char a[5]="0";
    node* p;
    p=head->next;
    int rest;
    printf("������Ҫ�ֳɼ��Σ�");
    scanf("%d",&m);
    while(m!=0)
    {
        m--;
        printf("ʣ��%dKB���ڴ棬�������%d�εĴ�С��",size,count);
        scanf("%d",&n);
        size=size-n;
        while((p->next)&&((n>p->size)||(p->flag[0]=='j')||(p->flag[0]=='J')))      //�ҵ����ʴ�Сδ����λ��
            p=p->next;
        if(p->next=NULL)
        {
            printf("Խ���жϣ�\n");
            return ;
        }
        if((n<=p->size)&&(p->flag[0]!='j')&&(p->flag[0]!='J'))
        {
            rest=p->size-n;
            if(rest==0)
            {
                strcpy(p->flag,c);
                p->flag[4]='0'+count-1;
                p->flag[5]='\0';
            }
            else
            {
                p->size=n;
                strcpy(p->flag,c);                    //�ѷ��䲿�ִ���
                k=count-1;
                p->flag[4]='0'+count-1;
                p->flag[5]='\0';
                new=(node*)malloc(sizeof(node));
                new->address=p->address+n;
                new->size=rest;
                strcpy(new->flag,a);
                new->next=p->next;
                p->next=new;
                reorder(head);
            }
            t->a[i][0]=i;
            t->a[i][1]=n;
            t->a[i][2]=p->address;
            i++;
            count++;
        }
        print(head);
    }
    t->a[i][0]=-1;
    t->next=h;
    h=t;
    printf("\n����ɹ���\n");
    printf("************��ӡ%s�α�************\n",c);
    printf("�κ�\t�γ�\t��ַ\n");
    for(i=0; i<10; i++)
    {
        if(t->a[i][0]!=-1)
            printf("%d\t%d\t%d\n",t->a[i][0],t->a[i][1],t->a[i][2]);
        else
            break;
    }
}

//��ӡ���� �ѷ���δ����ķ��������
void print(node* head)
{
    node* p=head;
    printf("******************����������*********************\n");

    printf("�ѷ��䣺\n");
    printf("�����\t��С��KB��\t��ʼ��KB��\t״̬\n");
    {
        p=head->next;
        while(p)
        {
            if(  (p->flag[0]=='j')||(p->flag[0]=='J')   )
                printf("%d\t%d\t\t%d\t\t%s\n",p->id,p->size,p->address,p->flag);
            p=p->next;
        }
    }

    printf("\n\nδ���䣺\n");
    printf("�����\t��С��KB��\t��ʼ��KB��\t״̬\n");
    {
        p=head->next;
        while(p)
        {
            if(  (p->flag[0]!='j')&&(p->flag[0]!='J')   )
                printf("%d\t%d\t\t%d\t\t����\n",p->id,p->size,p->address);
            p=p->next;
        }
    }
}

//�޸�id
void reorder(node* head)
{
    int count=1;
    node*p=head;
    while(p->next)
    {
        p=p->next;
        if((p->flag[0]=='j')||(p->flag[0]=='J'))
        {
            p->id=count;
            count++;
        }
    }
    p=head;
    while(p->next)
    {
        p=p->next;
        if((p->flag[0]!='j')&&(p->flag[0]!='J'))
        {
            p->id=count;
            count++;
        }
    }
}

//����
void recyle(node* head)
{
    print(head);
    printf("������������յ���ҵ����");
    char c[10];
    scanf("%s",c);
    char a[5]="0";
    int i=0;
    int count=0;

    node* p;
    p=head;
    while(p->next)
    {
        if(p->next->flag[3]==c[3])
        {
            count=1;
            if((p!=head)&&(p->flag[0]!='j')&&(p->flag[0]!='J'))
            {
                if((p->next->next)&&((p->next->next->flag[0]!='j')&&(p->next->next->flag[0]!='J')))      //������������
                {
                    p->size+=p->next->size;
                    p->size+=p->next->next->size;
                    p->next=p->next->next->next;
                }
                else                                                                                                //������������
                {
                    p->size+=p->next->size;
                    p->next=p->next->next;
                }
            }
            else                                                                                                     //�����ڴ���
            {
                if((p->next->next)&&((p->next->next->flag[0]!='j')&&(p->next->next->flag[0]!='J')))            //������������С��
                {
                    strcpy(p->next->flag,a);
                    p->next->size+=p->next->next->size;
                    p->next->next=p->next->next->next;
                    p=p->next;
                }
                else                                                                                                 //������������С��
                {
                    strcpy(p->next->flag,a);
                    p=p->next;
                }
            }
            printf("����%s�Ķ�%s%d�ɹ���\n",c,c,i);
            reorder(head);
            i++;
        }
        else
            p=p->next;
    }


    if(count==0)
        printf("������յ���ҵ�����ڣ�\n");
    print(head);
}


int main()
{
    node* head;
    int c;
    int flag=1;
    head=initMemory();//��ʼ��
    while(flag)
    {
        printf("*********�ɱ��������**********\n");
        printf("   *     1.�ڴ����      *   \n"  );
        printf("   *     2.�ڴ�ȥ��      *   \n"  );
        printf("   *     0.�˳�          *   \n"  );
        printf("         ������ѡ��[ ]\b\b"       );
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                printf("1.�ڴ����\n");
                allocate(head);
                break;
            case 2:
                printf("2.�ڴ�ȥ��\n");
                recyle(head);
                break;
            case 0:
                printf("0.�˳�\n");
                flag=0;
                break;
        }
    }
    getch();
    return 0;

}
