typedef struct  data
{
    int hour;
    int min;
}time;

typedef struct node
{
    char name[20];//����
    time arrive;//�뾮ʱ��
    int zx;//ִ��ʱ��
    time jobTime;//��ҵ����ʱ��
    int jobWait;//��ҵ���ȵȴ�ʱ��
    time processTime ;//���̵���ʱ��
    int processWait;//���̵��ȵȴ�ʱ��
    time finish;//���ʱ��
    int zz;//��תʱ��
    float zzxs;//��Ȩ��תϵ��
    struct node* next;
} linklist;
typedef struct
{
    linklist *front;
    linklist *rear;
} queue;

