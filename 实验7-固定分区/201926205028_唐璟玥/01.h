//�����ṹ��
typedef struct link_node
{
    int id;//������
    int size; //��������
    int address; //����ʼַ
    char station[10]; //����״̬
    struct link_node *next;
} node;

//��ҵ�ṹ��
typedef struct job_node
{
    int id;
    int name;
    int size;
    struct job_node *next
} job;

//����
typedef struct
{
    node *front;
    node *rear;
} queue;

