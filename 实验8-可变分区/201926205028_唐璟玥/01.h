//�����ṹ��
typedef struct link_node
{
    int size;//������С
    int address; //����ʼַ
    char flag[20]; //����״̬�����л���ռ����ҵ��
    struct link_node *next;
} node;
node *head;
node *s;

//��ҵ�ṹ��
typedef struct job_node
{
    int id;
    char station[20];
    int size;
} job;

