typedef struct node
{
    int size;//需要分配空间的大小
    int a[1000];//块号
    int zihao[1000];//字号
    int weihao[1000];//位号
    int zhu[1000];//柱面号
    int citou[1000];//磁头号
    int shanqu[1000];//扇区号
    char name[10];//作业名
    struct node *next;
}linklist;


