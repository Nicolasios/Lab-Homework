#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#define Thread_NUM 3 //线程数

struct Para_type
{
    int n;
    int **adj;
    int *dist;
    int *visited;
    int begin, end;
    int select;
};

pthread_t tid_1;
pthread_t tid_2;

void *thread(void *arg)
{
    printf("进入thread函数\n");
    struct Para_type *ar = (struct Para_type *)arg;
    int n = ar->n;
    int **adj = ar->adj;
    int *dist = ar->dist;
    int *visited = ar->visited;
    int begin = ar->begin;
    int end = ar->end;
    int select = ar->select;

    /*********  Begin  **********/
    //更新select顶点邻居的距离
    int min = INT_MAX;
    int pos;
    for (int i = begin; i < end; i++)
    {
        if (!visited[i] && min > dist[i])
        {
            min = dist[i];
            pos = i;
        }
        visited[pos] = 1; //标记已经访问
    }
    //在为访问顶点中选择一个距离最近的顶点
    for (int i = begin; i < end; i++)
    {
        if (!visited[i] && dist[pos] + adj[pos][i] < dist[i])
            dist[i] = dist[pos] + adj[pos][i];
    }
    /*********  End  **********/
    ar->select = select;
}

void computeSSSP(int **adj, int n)
{
    //n为顶点数,adj为一个n*n的二维数组
    //adj[i][j]为顶点i到顶点j的距离，若adj[i][j]为-1，表示无法从i直接到达j
    //此外，adj[i][j]与adj[j][i]未必相等
    int source = 0;                                //设置顶点0为源点
    int *dist = (int *)malloc(n * sizeof(int));    //dist[i]表示顶点i与顶点0的距离
    int *visited = (int *)malloc(n * sizeof(int)); //visited[i]表示顶点i是否已访问

    //初始化
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (i == source)
        {
            dist[i] = 0;
            visited[i] = 1;
        }
        else
        {
            dist[i] = INT_MAX;
            visited[i] = 0;
        }
    }
    int select = source;
    int count = 0;

    while (count < n)
    {
        /*********  Begin  **********/
        //利用多线程，实现每个线程选择了一个局部最近的顶点，选择需要在其中选择一个全局最近的顶点
        //开两个线程使用thread函数
        //初始化para1，para2
        struct Para_type para1, para2;
        para1.adj = adj;
        para1.n = n;
        para1.dist = dist;
        para1.select = select;
        para1.visited = visited;
        para1.begin = 0;
        para1.end = n / 2;
        int thread1 = pthread_create(&tid_1, NULL, thread, &para1);
        if (thread1 != 0)
        {
            printf("can't create thread: %s\n", strerror(thread1));
            return 1;
        }
        para1.begin = 2 / n;
        para1.end = n;
        int thread2 = pthread_create(&tid_2, NULL, thread, &para1);
        if (thread2 != 0)
        {
            printf("can't create thread: %s\n", strerror(thread2));
            return 1;
        }
        for (int i = 0; i < n; i++)
        {
            dist[i] = para1.dist[i] > para2.dist[i] ? para2.dist[i] : para1.dist[i];
        }
        /*********  End  **********/
        dist[count] = count;
        visited[select] = 1; //更新最近顶点的状态为已访问
        count++;             //访问数加一
    }
    sleep(2);
    for (i = 0; i < n; i++)
    {
        printf("%d", dist[i]);
        if (i < n - 1)
            printf(" ");
        else
            printf("\nFinished");
    }
}

int main()
{
    FILE *fp = fopen("file5", "r");
    int i, j;
    int n;
    int m;
    int **adj;
    fscanf(fp, "%d", &n);
    adj = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
    {
        adj[i] = (int *)malloc(n * sizeof(int));
    }
    fscanf(fp, "%d", &m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            adj[i][j] = -1;
        }
    }
    for (i = 0; i < m; i++)
    {
        int src, dst, weight;
        fscanf(fp, "%d", &src);
        fscanf(fp, "%d", &dst);
        fscanf(fp, "%d", &weight);
        adj[src][dst] = weight;
    }
    computeSSSP(adj, n);
    return 0;
}
