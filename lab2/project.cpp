#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
int p[27]; //并查集，用于判断两个点是否直接或间接连通
struct per
{
    int u, v, w;

} map[80];
bool cmp(per a, per b)
{
    return a.w < b.w;
}
int find(int x)
{
    return x == p[x] ? x : p[x] = find(p[x]);
}

int main()
{
    int n;
    while (scanf("%d", &n), n)
    {
        int i, j;
        for (i = 0; i < 27; i++)
            p[i] = i;
        int k = 0;
        for (i = 0; i < n - 1; i++) //构造边的信息
        {
            char str;
            int m;
            cin >> str >> m;
            for (j = 0; j < m; j++, k++)
            {
                char str2;
                int t;
                cin >> str2 >> t;
                map[k].u = (str - 'A');
                map[k].v = (str2 - 'A');
                map[k].w = t;
            }
        }

        sort(map, map + k, cmp); //将边从小到大排序
        int ans = 0;             //结果
        for (i = 0; i < k; i++)
        {
            int x = find(map[i].u);
            int y = find(map[i].v);
            if (x != y)
            { //如果两点不在同一连通分量里，则将两点连接，并存储该边

                ans += map[i].w;
                p[x] = y;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}