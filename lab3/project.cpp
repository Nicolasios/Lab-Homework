#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct node
{
    int a, b, s;
} p[10005];
int f[105];
bool cmp(node x, node y) //按权值对边排序
{
    return x.s < y.s;
}
int find(int x)
{
    if (f[x] == x)
        return x;
    return f[x] = find(f[x]);
}
int join(int x, int y) //判断两点是否在一棵树上
{
    int t1, t2;
    t1 = find(x);
    t2 = find(y);
    if (t1 != t2) //如果不是就把边加入树中并把两个点连到一棵树上
    {
        f[t2] = t1;
        return 1;
    }
    return 0;
}
int main()
{
    int n, m;
    while (scanf("%d", &n) && n)
    {
        memset(f, 0, sizeof(0));
        int sum = 0, count = 0;
        m = (n - 1) * n / 2;
        for (int i = 0; i < m; i++)
            scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].s);
        sort(p, p + m, cmp);
        for (int i = 1; i <= n; i++)
            f[i] = i;
        for (int i = 0; i < m; i++)
        {
            if (join(p[i].a, p[i].b))
            {
                count++;
                sum += p[i].s;
            }
            if (count == n - 1)
                //n个点之间最多n-1条线
                break;
        }
        printf("%d\n", sum);
    }
    return 0;
}