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

