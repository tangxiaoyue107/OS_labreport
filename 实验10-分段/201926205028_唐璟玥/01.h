//�ڴ�ṹ��
typedef struct memory_node
{
    int size; //�ڴ��С
    int address; //�ڴ�ʼַ
} memoryNode;


//�����ṹ��
typedef struct link_node
{
    int id;//������
    int size;//������С
    int address; //����ʼַ
    char flag[20]; //����״̬�����л���ռ����ҵ��
    struct link_node *next;
} node;

//�α�
typedef struct segment_node
{
    int a[10][10];
    struct segment_node *next;
} segmentNode;


memoryNode memory;
node *head;
node *s;
segmentNode *h=NULL;



