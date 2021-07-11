//内存结构体
typedef struct memory_node
{
    int size; //内存大小
    int address; //内存始址
} memoryNode;


//分区结构体
typedef struct link_node
{
    int id;//分区号
    int size;//分区大小
    int address; //分区始址
    char flag[20]; //分区状态，空闲或者占用作业名
    struct link_node *next;
} node;

//段表
typedef struct segment_node
{
    int a[10][10];
    struct segment_node *next;
} segmentNode;


memoryNode memory;
node *head;
node *s;
segmentNode *h=NULL;



