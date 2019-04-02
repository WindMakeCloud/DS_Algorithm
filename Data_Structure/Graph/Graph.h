/****************************************
 * 数据结构：无向图
 * 
 * *************************************/
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <climits>
using namespace std;    

template <typename Comparable>
class Graph
{
private:
    struct Vertex
    {
        int at;              // 数组位置
        Comparable element;  // 数据
        int color;           // 颜色
        int dist;            // ｓ到该节点距离
        Vertex * pre;        // 前驱顶点

        Vertex(int a = 0, const Comparable & theElement = Comparable{ },
               int c = WHITE, int d = INT_MAX, Vertex *p = nullptr)
            : at{a}, element{theElement}, color{c}, dist{d}, pre{p} { }
    };

    int V;                       // 顶点数目
    int E;                       // 边的数目
    vector<list<Vertex> *> adj;   // 邻接表

public:
    enum{WHITE, GRAY, BLACK};

    Graph() { }
    Graph(int n)
    {
        V = n;
        E = 0;
        adj = vector<list<Vertex> *>(n);
        for(int i = 0; i < n; ++i)
        {
            adj[i] = list<Vertex> { };
        }
    }

    int V() { return V; }
    int E() { return E; }

    void addEdge(Vertex v, Vertex w)
    {
        adj[v].push_back(w);       // 将w添加到v的链表中
        adj[w].push_back(v);       // 将v添加到w的链表中
        E++;
    }

    // 广度优先搜索算法，s是源结点，伪代码
    void BFS(Vertex & s)
    {
        s.color = GRAY;
        s.dist = 0;
        s.pre = nullptr;

        queue<Vertex> Q;
        Q.push(s);
        while(Q.size() != 0)
        {
            Vertex u{Q.pop()};
            for(auto & v : adj[u])
                if(v.color == WHITE)
                {
                    v.color = GRAY;
                    v.dist = u.dist + 1;
                    v.pre = u
                    Q.push(v);
                }
            u.color = BLACK;
        }
    }

    // 深度优先搜索算法，伪代码
    void DFS()
    {
        for(auto & u : V)
        {
            u.color = WHITE;
            u.pre = nullptr;
        }
        static int time = 0;

        for(auto & u : V)
            if(u.color == WHITE)
                DFS_VISIT(u);
    }
    void DFS_VISIT(Vertex & u)
    {
        time = time + 1;    // 结点u被发现
        u.d = time;
        u.color = GRAY;
        for(auto & v : adj[u])   // 探索边(u, v)
            if(v.color == WHITE)
            {
                v.pre = u;
                DFS_VISIT(v);
            }
        u.color = BLACK;    // 结点u变为黑色，完成结点的探索
        time = time + 1;
        u.f = time;
    }
};

#endif