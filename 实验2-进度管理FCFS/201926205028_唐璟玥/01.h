typedef struct data
{
    int hour;
    int min;
}time;

//���̽ṹ��
typedef struct link_node
{
    int id;//���
    char name[20];//��������
    time arrive;//�����������ʱ��
    int zx;//ִ��ʱ��
    time start;//��ʼʱ��
    time finish;//���ʱ��
    int zz;//��תʱ�䣺���ʱ��-�����������ʱ��
    float zzxs;//��Ȩ��תϵ��=��תʱ��/ִ��ʱ��
    struct link_node *next;
}node;

//����
typedef struct
{
    node *front;//ͷ�ڵ��
    node *rear;//β����
}queue;

