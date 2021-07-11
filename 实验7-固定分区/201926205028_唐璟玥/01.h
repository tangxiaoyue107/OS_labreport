//分区结构体
typedef struct link_node
{
    int id;//分区号
    int size; //分区长度
    int address; //分区始址
    char station[10]; //分区状态
    struct link_node *next;
} node;

//作业结构体
typedef struct job_node
{
    int id;
    int name;
    int size;
    struct job_node *next
} job;

//队列
typedef struct
{
    node *front;
    node *rear;
} queue;

