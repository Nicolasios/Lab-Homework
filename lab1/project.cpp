#include <stdio.h>
#include <string.h>
int a[1002];

int find(int x)
{
    int r = x;
    while (a[r] != r)
        r = a[r]; //找到该元素所在的连通集合的代表元素 即根节点
    return r;
}

void merge(int x, int y) //如果X,Y不在一个集合中，将Y添加进X所在的连通集合并作为代表元素
{
    int fx, fy;
    fx = find(x);
    fy = find(y);
    if (fx != fy)
        a[fx] = fy;
}

int main()
{
    int n, m, x, y, count = -1;
    while (scanf("%d", &n) && n)
    {
        for (int i = 1; i <= n; i++)
            a[i] = i;
        for (scanf("%d", &m); m > 0; m--)
        {
            scanf("%d %d", &x, &y);
            merge(x, y);
        }
        for (int i = 1; i <= n; i++)
            if (a[i] == i)
                count++; //需要额外建设的道路就等于所有连通集合数目减一
        printf("%d\n", count);
        memset(a, 0, sizeof(a));
        count = -1;
    }
    return 0;
}