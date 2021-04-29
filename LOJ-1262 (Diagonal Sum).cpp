#include <bits/stdc++.h>
using namespace std;

#define mx 200
int rgraph[mx][mx], parent[mx];
int nodes, src, sink;

struct Edge
{
    int v, flow, c, rev;
};

class Graph
{
    int V;
    int *level;
    vector<Edge>*adj;
public:
    Graph(int V)
    {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }
    void addEdge(int u, int v, int C)
    {
        Edge a{v, 0, C, adj[v].size()};
        Edge b{u, 0, 0, adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }
    void makeEdge(int n, int m);
    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxFlow(int s, int t);
};

bool Graph::BFS(int s = src, int t = sink)
{
    for(int i = 0; i < V; i++)
        level[i] = -1;
    level[s] = 0;
    queue<int>q;
    q.push(s);
    vector<Edge>::iterator it;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(it = adj[u].begin(); it != adj[u].end(); it++)
        {
            Edge &e = *it;
            if(level[e.v] < 0 && e.flow < e.c)
            {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }
    return level[t] < 0 ? false : true;
}

int Graph::sendFlow(int u, int flow, int t, int start[])
{
    if(u == t)
        return flow;
    for( ; start[u] < adj[u].size(); start[u]++)
    {
        Edge &e = adj[u][start[u]];
        if(level[e.v] == level[u] + 1 && e.flow < e.c)
        {
            int curr_flow = min(flow, e.c - e.flow);
            int temp_flow = sendFlow(e.v, curr_flow, t, start);
            if(temp_flow > 0)
            {
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;
                rgraph[u][e.v] += temp_flow;
                rgraph[e.v][u] -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}

int Graph::DinicMaxFlow(int s = src, int t = sink)
{
    if(s == t)
        return -1;
    int total = 0;
    while(BFS() == true)
    {
        int *start = new int[V+1] {0};
        while(int flow = sendFlow(s, INT_MAX, t, start))
            total += flow;
    }
    return total;
}

void Graph::makeEdge(int n, int m)
{
    int i, j, k, u, v;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= m; j++)
        {
            u = i + j - 1;
            v = n + 2*m - 1 + i - j;
            //rgraph[u][v] = 99;
            addEdge(u, v, 99);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int m, n, i, j, k, t, kase(0), nd, mn, sub, r__g, u, v;
    scanf("%d", &t);
    while(t-- && ++kase)
    {
        scanf("%d %d", &n, &m);
        nodes = 2 * (n + m);
        Graph MAT(nodes);
        src = 0, sink = nodes - 1, nd = 1;
        k = n + m - 1;
        mn = min(m, n);
        int left[k], right[k];
        for(i = 0; i < k; i++)
            scanf("%d", &left[i]);
        for(i = 0; i < k; i++)
            scanf("%d", &right[i]);

        memset(rgraph, 0, sizeof(rgraph));
        //start of making the nodes
        for(i = 0, sub = 1; i < k; i++, nd++)
        {
            if((i+1) < mn)
            {
                MAT.addEdge(src, nd, left[i] - sub);
                sub++;
            }
            else if((i+1) >= mn && (n + m - (i+1)) >= mn)
                MAT.addEdge(src, nd, left[i] - sub);
            else
            {
                --sub;
                MAT.addEdge(src, nd, left[i] - sub);
            }
            r__g = rgraph[src][nd];
        }
        for(i = 0, sub = 1; i < k; i++, nd++)
        {
            if((i+1) < mn)
            {
                MAT.addEdge(nd, sink, right[i] - sub);
                sub++;
            }
            else if((i+1) >= mn && (n + m - (i+1)) >= mn)
                MAT.addEdge(nd, sink, right[i] - sub);
            else
            {
                --sub;
                MAT.addEdge(nd, sink, right[i] - sub);
            }
            r__g = rgraph[nd][sink];
        }
        //end of making the nodes

        MAT.makeEdge(n, m);

        MAT.DinicMaxFlow();
        printf("Case %d:\n", kase);
        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= m - 1; j++)
            {
                u = i + j - 1;
                v = n + 2*m - 1 + i - j;
                printf("%d ", rgraph[u][v] + 1);
            }
            u = i + j - 1;
            v = n + 2*m - 1 + i - j;
            printf("%d", rgraph[u][v] + 1);
            printf("\n");
        }
    }
    return 0;
}
