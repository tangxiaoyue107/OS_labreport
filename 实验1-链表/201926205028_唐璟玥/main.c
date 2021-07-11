#include <stdio.h>
#include <stdlib.h>
//����ͷ�ڵ�ĵ�����
typedef int datatype;
typedef struct link_node
{
    datatype info;
    struct link_node *next;
}node;
typedef node *linklist;
//�����ʼ��
node *init()
{
    return NULL;
}
//����ֵΪx�Ľ�������
node *find(node *head,int i)
{
    int j=1;
    node *p=head;
    if(i<1) return NULL;
    while(p&&i!=j)
    {
        p=p->next;
        j++;
    }
    return p;
}
//��ӡ�����������ֵ
void display(node *head)
{
    node *p;
    p=head;
    if(!p) printf("\n�������ǿյģ�");
    else
    {
        printf("\n�������������ֵ�ǣ�\n");
        while(p)
        {
            printf("%5d",p->info);
            p=p->next;
        }
    }
}

//����ֵΪx��ĳ���ڵ�
int selectLink(linklist p,int x)
{
    linklist t=p;
    int i=1;
    while(t->next){
        t=t->next;
        if(t->info==x){
            return i;
        }
        i++;
    }
    return -1;
}
//����ֵΪx������ĵ�i��λ��
node *insert(node *head,datatype x,int i)
{
    node *p,*q;
    q=find(head,i);
    //printf("i=%d",i);
    if(!q&&i!=0)
    {

        printf("\n�Ҳ�����%d����㣬���ܲ���%d!",i,x);
    }
    else
    {
        p=(node*)malloc(sizeof(node));
        p->info=x;
        if(i==0)
        {
            p->next=head;
            head=p;
        }
        else
        {
            p->next=q->next;
            q->next=p;
        }
    }
    return head;
}
//ɾ��ֵΪx�Ľ��
node *dele(node *head,datatype x)
{
    node *pre=NULL,*p;
    if(!head)
    {
        printf("�������ǿյģ�");
        return head;
    }
    p=head;
    while(p&&p->info!=x)
    {
        pre=p;
        p=p->next;
    }
    if(p)
    {
        if(!pre) head=head->next;
        else pre->next=p->next;
        free(p);
    }
    return head;
}
//ͷ��
linklist creatbystack()
{
    linklist head,s;
    datatype x;
    head=NULL;
    printf("�����������������У�\n");
    scanf("%d",&x);
    while(x!=0)
    {
        s=(linklist)malloc(sizeof(node));
        s->info=x;
        s->next=head;
        head=s;
    }
    return head;
}
//β��
linklist creatbyqueue()
{
    linklist head,r,s;
    datatype x;
    head=r=NULL;
    printf("�����������������У�\n");
    scanf("%d",&x);
    while(x!=0)
    {
        s=(linklist)malloc(sizeof(node));
        s->info=x;
        if(head==NULL) head=s;
        else r->next=s;
        r=s;
        scanf("%d",&x);
    }
    if(r) r->next=NULL;
    return head;
}

//��ʽ���е�ɾ��
void delList(linklist head)
{
    linklist p=head;
    while(p)
    {
        head=p->next;
        free(p);
        p=head;
    }
}
//����
linklist Listsort(linklist head)
{
    linklist p,q;
    int t;
    p=head;
    while(p)
    {
        q=p->next;
        while(q)
        {
            if(p->info > q->info){
                t=p->info;
                p->info=q->info;
                q->info=t;
            }
            q=q->next;
        }
        p=p->next;
    }
    return head;
}



int main()
{
    node *head;
    int x,num,index,m,adress;
    head = init();
    head = creatbyqueue();
    display(head);
    printf("\n��������Ҫ���ҵ�Ԫ�أ�");
    scanf("%d",&m);
    adress=selectLink(head,m);
    if(adress==-1)
        printf("û�и�Ԫ�ء�\n");
    else
        printf("Ԫ��%d��λ��Ϊ��%d\n",m,adress);
    printf("\n��������Ҫɾ���Ľ���ֵ��");
    scanf("%d",&x);
    head = dele(head,x);
    display(head);
    printf("\n��������Ҫ�������ֵ��λ�ã�");
    scanf("%d %d",&num,&index);
    head = insert(head,num,index);
    display(head);
    printf("\n�Դ������������");
    head = Listsort(head);
    display(head);
    getch();
    return 0;
}
