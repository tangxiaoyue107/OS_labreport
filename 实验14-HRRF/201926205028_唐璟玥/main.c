#include <stdio.h>
#include <stdlib.h>
#define MAX 20
typedef struct
{
    int hour;
    int min;
}time;
typedef struct
{
    char name[MAX];//����
    time arrive;  //�뾮ʱ��
    int zx;//ִ��ʱ��
    time jobTime;//��ҵ����ʱ��
    int jobWait;//��ҵ���ȵȴ�ʱ��
    time processTime;  //���̵���ʱ��
    int processWait;//���̵ȴ�ʱ��
    time finish; //���ʱ��
    int Time;   //��תʱ��
    float zzxs;//��Ȩ��תϵ��
    float response;//��Ӧ��
    int flag;   //�Ƿ��ѱ����й��ı�־
}Process;
void Init(Process a[], int N)
{
    int i;
    printf("201926205028 �ƭZ�h HRRF\n");
    printf("������ÿ����ҵ��\n��ҵ��\t��ҵ�뾮ʱ��\t��������ʱ��\n");
    for(i=0; i<N; i++)
    {
        scanf("%s", a[i].name);
        scanf("%d:%d", &a[i].arrive.hour,&a[i].arrive.min);
        scanf("%d", &a[i].zx);
        a[i].flag = a[i].response = 0 ;
    }
    printf("------------------------��ʼ״̬------------------------\n");
    printf("��ҵ�������\t��ҵ��\t��ҵ�뾮ʱ��\t����ʱ��\n");
    for(i=0; i<N; i++)
        printf("%d\t\t%s\t\t%d:%d\t\t%d\n", i, a[i].name, a[i].arrive.hour,a[i].arrive.min, a[i].zx);
    printf("----------------------------------------------------------\n\n");
}

int search(Process a[], int N)
{
    int i, index1, index2;
    for(i=0; i<N; i++)
    {
        if(!a[i].flag)
        {
            index1 = i;
            break;
        }
    }
    index2 = index1;
    for(i=index1+1; i<N; i++)
    {
        if(a[i].response && !a[i].flag)
        {
            if(a[i].response > a[index2].response)
                index2 = i;
        }
    }
    return index2;
}

void HRRF(Process a[], int N)
{
    int i, pre, j = N - 1, index, series = 0, TIME = 0, least = 0;
    float ZZXS=0.0000;
    for(i=1; i<N; i++)
    {
        if(a[i].arrive.hour*60+a[i].arrive.min < a[least].arrive.hour*60+a[least].arrive.min)
            least = i;
    }
    pre = least;
    a[least].flag = 1;
    a[least].finish.hour = (a[least].zx + a[least].arrive.hour*60+a[least].arrive.min)/60;
    a[least].finish.min = (a[least].zx + a[least].arrive.hour*60+a[least].arrive.min)%60;
    a[least].processTime.hour = a[least].arrive.hour;
    a[least].processTime.min = a[least].arrive.min;
    a[least].processWait = a[least].processTime.hour*60+a[least].processTime.min-a[least].arrive.hour*60-a[least].arrive.min;
    a[least].Time = a[least].finish.hour*60+a[least].finish.min - a[least].arrive.hour*60-a[least].arrive.min;
    a[least].zzxs = 1.0000*a[least].Time/a[least].zx;
    printf("��ҵ��\t�뾮ʱ��\t����ʱ��\t����ʱ��\t������\t���̵���ʱ�� ������ ����ʱ��  ��תʱ��  ��Ȩ��תϵ��\n");
    printf("%s\t%2d:%02d\t\t%02d:%02d\t\t%d�����ӣ�\t%2d�����ӣ� %02d:%02d      0(��)  %02d:%02d     %3d�����ӣ�   %.4f\n",a[least].name, a[least].arrive.hour,a[least].arrive.min, a[least].processTime.hour,a[least].processTime.min,
           a[least].zx,a[least].processWait,a[least].processTime.hour,a[least].processTime.min, a[least].finish.hour,a[least].finish.min, a[least].Time,a[least].zzxs);
    while(j--)
    {
        for(i=0; i<N; i++)
        {
            if(a[pre].finish.hour*60+a[pre].finish.min >= a[i].arrive.hour*60+a[i].arrive.min && !a[i].flag)
                a[i].response = ((float)(a[pre].finish.hour*60+a[pre].finish.min - a[i].arrive.hour*60-a[i].arrive.min) / (float)a[i].zx) + 1;
        }
        index = search(a, N);
        series++;
        a[index].flag = 1;
        a[index].processTime.hour = a[pre].finish.hour;
        a[index].processTime.min = a[pre].finish.min;
        a[index].finish.hour = (a[index].processTime.hour*60 + a[index].zx+a[index].processTime.min)/60;
        a[index].finish.min = (a[index].processTime.hour*60 + a[index].zx+a[index].processTime.min)%60;
        a[index].processWait = a[index].processTime.hour*60+a[index].processTime.min-a[index].arrive.hour*60-a[index].arrive.min;
        a[index].Time = a[index].finish.hour*60+a[index].finish.min - a[index].arrive.hour*60-a[index].arrive.min;
        a[index].zzxs =1.0000*a[index].Time/a[index].zx;
        printf("%s\t%2d:%02d\t\t%02d:%02d\t\t%d�����ӣ�\t%d�����ӣ� %02d:%02d      0(��)  %02d:%02d     %3d�����ӣ�   %.4f\n", a[index].name, a[index].arrive.hour,a[index].arrive.min, a[index].processTime.hour,a[index].processTime.min,a[index].zx, a[index].processWait,a[index].processTime.hour
                    ,a[index].processTime.min,a[index].finish.hour,a[index].finish.min, a[index].Time,a[index].zzxs);
        pre = index;
    }
    for(i=0; i<N; i++)
    {
        TIME += a[i].Time;
        ZZXS +=a[i].zzxs;
    }

    printf("��ҵƽ����תʱ�䣺%.2f\n", (1.0 * TIME / N));
    printf("ϵͳ��Ȩƽ����תʱ��Ϊ��%.4f\n", (1.0000 * ZZXS / N));
}

int main()
{
    int N;
    printf("��������ҵ������");
    scanf("%d", &N);
    Process a[N];
    Init(a, N);
    HRRF(a, N);
    getch();
    return 0;
}
/*

4
JOB1 8:00 120
JOB2 8:50 50
JOB3 9:00 10
JOB4 9:50 20

*/
