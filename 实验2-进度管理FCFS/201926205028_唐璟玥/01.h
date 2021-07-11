typedef struct data
{
    int hour;
    int min;
}time;

//进程结构体
typedef struct link_node
{
    int id;//编号
    char name[20];//进程名字
    time arrive;//到达就绪队列时间
    int zx;//执行时间
    time start;//开始时间
    time finish;//完成时间
    int zz;//周转时间：完成时间-到达就绪队列时间
    float zzxs;//带权周转系数=周转时间/执行时间
    struct link_node *next;
}node;

//队列
typedef struct
{
    node *front;//头节点出
    node *rear;//尾结点进
}queue;

