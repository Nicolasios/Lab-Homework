
## A-畅通工程

### 题目描述：
> 某省调查城镇交通状况，得到现有城镇道路统计表，表中列出了每条道路直接连通的城镇。省政府“畅通工程”的目标是使全省任何两个城镇间都可以实现交通（但不一定有直接的道路相连，只要互相间接通过道路可达即可）。问最少还需要建设多少条道路？

### 输入测试:
> 测试输入包含若干测试用例。每个测试用例的第1行给出两个正整数，分别是城镇数目N ( < 1000 )和道路数目M；随后的M行对应M条道路，每行给出一对正整数，分别是该条道路直接连通的两个城镇的编号。为简单起见，城镇从1到N编号。
注意:两个城市之间可以有多条道路相通,也就是说
3 3
1 2
1 2
2 1
这种输入也是合法的
当N为0时，输入结束，该用例不被处理。

### 输出测试
```
    4 2
    1 3
    4 3
    3 3
    1 2
    1 3
    2 3
    5 2
    1 2
    3 5
    999 0  
    0
```

### 代码实现:

```
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
```

## B-Jungle Road

### 题目描述：
> The Head Elder of the tropical island of Lagrishan has a problem. A burst of foreign aid money was spent on extra roads between villages some years ago. But the jungle overtakes roads relentlessly, so the large road network is too expensive to maintain. The Council of Elders must choose to stop maintaining some roads. The map above on the left shows all the roads in use now and the cost in aacms per month to maintain them. Of course there needs to be some way to get between all the villages on maintained roads, even if the route is not as short as before. The Chief Elder would like to tell the Council of Elders what would be the smallest amount they could spend in aacms per month to maintain roads that would connect all the villages. The villages are labeled A through I in the maps above. The map on the right shows the roads that could be maintained most cheaply, for 216 aacms per month. Your task is to write a program that will solve such problems.

### 输入测试:
> The input consists of one to 100 data sets, followed by a final line containing only 0. Each data set starts with a line containing only a number n, which is the number of villages, 1 < n < 27, and the villages are labeled with the first n letters of the alphabet, capitalized. Each data set is completed with n-1 lines that start with village labels in alphabetical order. There is no line for the last village. Each line for a village starts with the village label followed by a number, k, of roads from this village to villages with labels later in the alphabet. If k is greater than 0, the line continues with data for each of the k roads. The data for each road is the village label for the other end of the road followed by the monthly maintenance cost in aacms for the road. Maintenance costs will be positive integers less than 100. All data fields in the row are separated by single blanks. The road network will always allow travel between all the villages. The network will never have more than 75 roads. No village will have more than 15 roads going to other villages (before or after in the alphabet). In the sample input below, the first data set goes with the map above.

```
        9
        A 2 B 12 I 25
        B 3 C 10 H 40 I 8
        C 2 D 18 G 55
        D 1 E 44
        E 2 F 60 G 38
        F 0
        G  1 H 35
        H 1 I 35
        3
        A 2 B 10 C 40
        B 1 C 20
        0
```
### 输出测试
> The output is one integer per line for each data set: the minimum cost in aacms per month to maintain a road system that connect all the villages. Caution: A brute force solution that examines every possible set of roads will not finish within the one minute time limit.

```
        216
        30
```

### 代码实现:

```
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
```
