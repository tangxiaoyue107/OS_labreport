#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "01.h"
//����
void recycle_froms(node *head);
//��ӡ�ѷ����δ����ķ���
void print_fenqu(node *head);
//��������
void first_allo(node *head);
//��������
void good_allo(node *head);
//�����
void bad_allo(node *head);
//����˵�
void allocate_caidan(node *head);



//����
void recycle_froms(node *head)
{
    char name[10];
    int flag=0;
    print_fenqu(head);
    printf("��������յ���ҵ��:");
    scanf("%s",name);
    node *p=s->next;//���ѷ�����������ҵ���ҵ��
    node *pre=s;
    while(p)
    {
        if(strcmp(p->flag,name)==0)
        {
            //��Դ����
            flag=1;//�ҵ�����ҵ
            printf("�ҵ�����\n");
            node *t=(node*)malloc(sizeof(node));
            t->address=p->address;

            t->size=p->size;
            t->next=NULL;

            node *q=head->next;
            node *pre_q=head;//δ����
            pre_q->address=0;
            pre_q->size=0;
            if(!head->next)
            {
                strcpy(t->flag,"����");
                head->next=t;
                pre->next=p->next;//�ѷ���ı���Ҫ�ͷŵ��ѻ��յ�δ�������Ľ��
                free(p);
                printf("���ճɹ�!\n");
                break;
            }

            while(q)
            {
                printf("11");
                if(pre_q->address+pre_q->size < t->address && t->address+t->size < q->address)//���¶�û�л�����
                {
                    printf("���¶�û�л�����\n");
                    pre_q->next=t;
                    t->next=q;
                    strcpy(t->flag,"����");
                    break;
                }
                else if(pre_q->address+pre_q->size == t->address && t->address+t->size < q->address)//���п���������û��
                {
                    printf("���п���������û��\n");
                    pre_q->size=pre_q->size+t->size;
                    free(t);
                    break;
                }
                else if(pre_q->address+pre_q->size < t->address && t->address+t->size == q->address)//���п���������û��
                {
                    printf("���п���������û\n");
                    q->size=q->size+t->size;
                    q->address = q->address-t->size;
                    free(t);
                    break;
                }
                else if(pre_q->address+pre_q->size == t->address && t->address+t->size == q->address)//���¶��п�����
                {
                    printf("���¶��л�����\n");
                    pre_q->size=pre_q->size+t->size+q->size;
                    if(q->next)//���q��next����NULL��p�������һ��
                        pre_q->next=q->next;
                    else//���p�����һ��
                        pre_q->next=NULL;
                }
                pre_q=q;
                q=q->next;
            }
            if(q==NULL)
            {
                strcpy(t->flag,"����");
                pre_q->next=t;
            }
            pre->next=p->next;//�ѷ���ı���Ҫ�ͷŵ��ѻ��յ�δ�������Ľ��
            free(p);
            printf("���ճɹ�!\n");
            break;
        }
        pre=p;
        p=p->next;
    }
    if(flag==0)
    {
        printf("������%s��ҵ",name);
    }
    print_fenqu(head);
}

//��ӡ�ѷ����δ����ķ���
void print_fenqu(node *head)
{
    int i=1;
    printf("\n*********************����������*********************\n");
    printf("�������������ѷ���:������������\n");
    printf("������\t��С��KB��\t��ʼ��KB��\t״̬\n");
    node *q=s->next;
    while(q)
    {
        printf("%d\t %d\t\t%d\t\t%s\n",i,q->size,q->address,q->flag);
        i++;
        q=q->next;
    }

    printf("������������δ����:������������\n");
    printf("������\t��С��KB��\t��ʼ��KB��\t״̬\n");
    node *p=head->next;
    while(p)
    {
        printf("%d\t %d\t\t%d\t\t%s\n",i,p->size,p->address,p->flag);
        i++;
        p=p->next;
    }
}
//��������
void first_allo(node *head)
{
    char name[10];
    int size;
    print_fenqu(head);
    printf("��������ҵ��:");
    scanf("%s",name);
    printf("������%s��Ҫ����������С����λ:KB��:");
    scanf("%d",&size);

    node *p=head->next;//δ����
    node *pre =head;
    node *q= s->next;//�ѷ���
    node *pre_q =s;
    int flag=1;
    while(p)//���δ������ڴ滹�����ڴ棬ѭ�����ҷ����ڴ��С�ķ������������䣩
    {
        if(p->size==size)//�����������ڴ�==δ�����ڴ�Ĵ�С
        {
            node *t=(node *)malloc(sizeof(node));//����һ��Node �����ڴ���Ϣ
            //���ȷ���
            t->address=p->address;//��ַ
            t->size=p->size;//��С
            strcpy(t->flag,name);//��ҵ��
            while(q&&q->address < t->address)//�ҵ���ַ��С����ڴ�ص����򣬲���
            {
                pre_q=q;
                q=q->next;
            }
            if(q!=NULL)//���q���ڣ�˵��pre_q�������һ��
            {
                pre_q->next=t;//����t���ѷ����½��
                t->next=q;
            }
            else//pre_q�����һ��
            {
                pre_q->next=t;
                t->next=NULL;
            }
            pre->next=p->next;//�ͷŵ�δ�����ڴ��е��ѷ�����p
            free(p);
            printf("����ɹ�!\n");
            flag=0;
            break;
        }
        else if(p->size > size)//�����������ڴ�<δ�����ڴ�������֮һ
        {
            node *t=(node *)malloc(sizeof(node));
            t->address=p->address;//��ʼ��ַ
            t->size=size;//��С
            strcpy(t->flag,name);//��ҵ��
            while(q&&q->address < t->address)
            {
                pre_q=q;//�ҵ��ѷ����������ڴ���ʼ��ַ��С��������λ��
                q=q->next;
            }
            if(q)
            {
                pre_q->next=t;
                t->next=q;
            }
            else
            {
                pre_q->next=t;
                t->next=NULL;
            }
            p->size=p->size-size;//p�Ĵ�С��С
            p->address=p->address+size;//p�ĵ�ַ�ı�
            printf("����ɹ�!\n");
            flag=0;
            break;
        }
        pre=p;
        p=p->next;
    }
    if(flag==1)
    {
        printf("����ʧ��!\n");
    }
    print_fenqu(head);
}
//��������
void good_allo(node *head)
{
    char name[10];
    int size;
    print_fenqu(head);
    printf("��������ҵ��:");
    scanf("%s",name);
    printf("������%s��Ҫ����������С����λ:KB��:");
    scanf("%d",&size);

    node *p=head->next;
    node *pre =head;
    node *q= s->next;
    node *pre_q =s;
    //Ѱ�����ʺ���С���ڴ�ռ�
    node *min_p=(node *)malloc(sizeof(node));
    node *min_pre=head;
    min_p->size=99999;
    int flag=1;
    while(p)
    {
        if(p->size>=size&&p->size<min_p->size)//�����ѭ���Ĺ����У��ҵ���������̴�С���ҳ��ȸ��ʺϣ�С���ľ��޸�Min_pre min_p
        {
            min_pre=pre;
            min_p=p;
        }
        pre=p;
        p=p->next;
    }
    if(min_p->size==size)
    {
        node *t=(node *)malloc(sizeof(node));
        t->address=min_p->address;
        t->size=min_p->size;
        strcpy(t->flag,name);
        while(q&&q->address < t->address)
        {
            pre_q=q;
            q=q->next;
        }
        if(q)
        {
            pre_q->next=t;
            t->next=q;
        }
        else
        {
            pre_q->next=t;
            t->next=NULL;
        }
        min_pre->next=min_p->next;
        free(min_p);
        printf("����ɹ�!\n");
        flag=0;
    }
    else if(min_p->size > size)
    {
        node *t=(node *)malloc(sizeof(node));
        t->address=min_p->address;
        t->size=size;
        strcpy(t->flag,name);
        while(q&&q->address < t->address)
        {
            pre_q=q;
            q=q->next;
        }
        if(q)
        {
            pre_q->next=t;
            t->next=q;
        }
        else
        {
            pre_q->next=t;
            t->next=NULL;
        }
        min_p->size=min_p->size-size;
        min_p->address=min_p->address+size;
        printf("����ɹ�!\n");
        flag=0;
    }
    if(flag==1)
        printf("����ʧ��!\n");
    print_fenqu(head);
}
//�����
void bad_allo(node *head)
{
    char name[10];
    int size;
    print_fenqu(head);
    printf("��������ҵ��:");
    scanf("%s",name);
    printf("������%s��Ҫ����������С����λ:KB��:");
    scanf("%d",&size);

    node *p=head->next;
    node *pre =head;
    node *q= s->next;
    node *pre_q =s;

    node *max_p=(node *)malloc(sizeof(node));//�����ѭ���Ĺ����У��ҵ���������̴�С���ҳ��ȸ��ʺϣ��󣩵ľ��޸�max_pre max_p
    node *max_pre=head;
    max_p->size=0;
    int flag=1;
    while(p)
    {
        if(p->size>=size&&p->size>max_p->size)
        {
            max_pre=pre;
            max_p=p;
        }
        pre=p;
        p=p->next;
    }
    if(max_p->size==size)
    {
        node *t=(node *)malloc(sizeof(node));
        t->address=max_p->address;
        t->size=max_p->size;
        strcpy(t->flag,name);
        while(q&&q->address < t->address)
        {
            pre_q=q;
            q=q->next;
        }
        if(q)
        {
            pre_q->next=t;
            t->next=q;
        }
        else
        {
            pre_q->next=t;
            t->next=NULL;
        }
        max_pre->next=max_p->next;
        free(max_p);
        printf("����ɹ�!\n");
        flag=0;
    }
    else if(max_p->size > size)
    {
        node *t=(node *)malloc(sizeof(node));
        t->address=max_p->address;
        t->size=size;
        strcpy(t->flag,name);
        while(q&&q->address < t->address)
        {
            pre_q=q;
            q=q->next;
        }
        if(q)
        {
            pre_q->next=t;
            t->next=q;
        }
        else
        {
            pre_q->next=t;
            t->next=NULL;
        }
        max_p->size=max_p->size-size;
        max_p->address=max_p->address+size;
        printf("����ɹ�!\n");
        flag=0;
    }
    if(flag==1)
        printf("����ʧ��!\n");
    print_fenqu(head);
}
//����˵�
void allocate_caidan(node *head)
{
    int choose;
    printf("*********�����㷨**********\n");
    printf("   *     1.���ȷ����㷨      *   \n");
    printf("   *     2.���ŷ����㷨      *   \n");
    printf("   *     3.������㷨      *   \n");
    printf("         ������ѡ��[ ]\b\b");
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:
            printf("1.���ȷ��䷨\n");
            first_allo(head);
            break;
        case 2:
            printf("2.���ŷ��䷨\n");
            good_allo(head);
            break;
        case 3:
            printf("3.����䷨\n");
            bad_allo(head);
            break;
        }
}

int main()
{
    int choose;
    node *newnode = (node*)malloc(sizeof(node));
    head = (node *)malloc(sizeof(node));
    head->next = NULL;
    s=(node *)malloc(sizeof(node));//sָ���ѷ��������
    s->next=NULL;

    printf("�������ڴ��ַ����:");
    scanf("%d",&newnode->size);
    printf("��������ʼ��ַ��СΪ:");
    scanf("%d",&newnode->address);
    strcpy(newnode->flag,"����");
    newnode->next = NULL;
    head->next=newnode;

    while(1)
    {
        printf("*********�ɱ��������**********\n");
        printf("   *     1.�ڴ����      *   \n");
        printf("   *     2.�ڴ�ȥ��      *   \n");
        printf("   *     0.�˳�          *   \n");
        printf("         ������ѡ��[ ]\b\b");
        scanf("%d",&choose);
        switch(choose)
        {
            case 1:
                printf("1.�ڴ����\n");
                allocate_caidan(head);
                break;
            case 2:
                printf("2.�ڴ�ȥ��\n");
                recycle_froms(head);
                break;
            case 0:
                printf("0.�˳�\n");
                return 0;
            }
    }
    return 0;
}
