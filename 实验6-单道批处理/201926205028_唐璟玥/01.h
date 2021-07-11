typedef struct  data
{
    int hour;
    int min;
}time;

typedef struct node
{
    char name[20];//名字
    time arrive;//入井时间
    int zx;//执行时间
    time jobTime;//作业调度时间
    int jobWait;//作业调度等待时间
    time processTime ;//进程调度时间
    int processWait;//进程调度等待时间
    time finish;//完成时间
    int zz;//周转时间
    float zzxs;//带权周转系数
    struct node* next;
} linklist;
typedef struct
{
    linklist *front;
    linklist *rear;
} queue;

