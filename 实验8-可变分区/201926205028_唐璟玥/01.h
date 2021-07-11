//分区结构体
typedef struct link_node
{
    int size;//分区大小
    int address; //分区始址
    char flag[20]; //分区状态，空闲或者占用作业名
    struct link_node *next;
} node;
node *head;
node *s;

//作业结构体
typedef struct job_node
{
    int id;
    char station[20];
    int size;
} job;

