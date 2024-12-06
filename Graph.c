#define MaxVertexNum 100  // 图中顶点数目的最大值


/* 邻接矩阵 */
/**
 * 在简单应用中,可直接用二维数组作为图的邻接矩阵(顶点信息等均可省略)
 * 当邻接矩阵的元素仅表示边是否存在时,EdgeType可采用值为0和1的枚举类型
 */
typedef char VertexType;  // 顶点数据类型

typedef int EdgeType;  // 权值数据类型

typedef struct {
    int vexnum, arcnum;  // 当前顶点数和边数
    VertexType vex[MaxVertexNum];  // 顶点表
    EdgeType edges[MaxVertexNum][MaxVertexNum];  // 邻接矩阵(边表)
} MGraph;


/* 邻接表 */

/**
 * 边结点
 */
typedef struct ArcNode {
    int adjvex;  // 连接/指向的邻接点的位置(编号)
    struct ArcNode *nextArc;  // 指向下一条邻接边/出边
    // InfoType info;  // 权值
} ArcNode;

/**
 * 顶点结点
 */
typedef struct VNode { 
    VertexType data;
    ArcNode *firstArc;  // 指向该顶点第一条邻接边/出边
} VNode, AdjList[MaxVertexNum];

/**
 * 邻接表
 */
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;


/* 十字链表(有向图) */
/**
 * 弧结点
 */
typedef struct ArcNode {
    int tailvex, headvex; // 弧尾与弧头
    struct ArcNode *hlink, *tlink;    // 指向弧头相同、弧尾相同的弧
    // int info;  // 该弧的相关信息
} ArcNode;

/**
 * 顶点结点
 */
typedef struct {
    VertexType data;  // 顶点信息
    ArcNode *firstIn, *firstOut;  // 指向第一条入边、第一条出边
} VNode;

typedef struct {
    VNode adjList[MaxVertexNum];  // 顶点结点仍是顺序存储
    int vexnum, arcnum;
} GLGraph;


/* 邻接多重表(无向图) */
/**
 * 边结点
 */
typedef struct ArcNode {
    int ivex, jvex;  // 连接的两个顶点
    struct ArcNode *ilink, *jlink;    // 指向下一条依附于ivex、jvex的边
    // int info;  // 该边的相关信息
    // bool mark;  // 指示该边是否被搜索过
} ArcNode;
/**
 * 顶点结点
 */
typedef struct {
    VertexType data;  // 顶点信息
    ArcNode *firstedge;  //指向第一条依附的边
} VNode;

typedef struct {
    VNode adjlist[MaxVertexNum];
    int vexnum, arcnum;
} AMLGraph;


/**
 * 广度优先搜索遍历BFS
 */
bool visited[MaxVertexNum];  // 访问标记
SqQueue qu;  // 辅助队列

void BFSTraverse(Graph g) {
    // 初始化标记数组
    for (int i; = 0; i < g.vexnum; ++i)
        visited[i] = FALSE;
    initQueue(qu);
    // 对每个连通分量调用一次BFS
    for (i = 0; i < g.vexnum; ++i)
        if (!visited[i])
            BFS(g, i);  // 可选下面三种实现之一
}

/**
 * 从顶点v出发广度优先遍历图g(邻接表)
 */
void BFS_AL1(ALGraph g, int v) {
    visit(v);
    visited[v] = TRUE;
    enQueue(qu, v);
    while (!isEmpty(qu)) {
        deQueue(qu, v);
        // 访问v所有未访问过的邻接点
        for (ArcNode *p = g.vertices[v].firstArc; p; p = p->nextArc)
            int w = p->adjvex;
            if (!visited(w)) {
                visit(w);
                visited[w] = TRUE;
                enQueue(qu, w);
            }
    }
}

/**
 * 从顶点v出发广度优先遍历图g(邻接表)
 */
void BFS_AL2(ALGraph g, int v) {
    enQueue(qu, v);
    while (!isEmpty(qu)) {
        int size = getQuSize(qu);
        while (size > 0) {
            deQueue(qu, v);
            visit(v);
            visited[v] = TRUE;
            --size;
            // 访问v所有未访问过的邻接点
            for (ArcNode *p = g.vertices[v].firstArc; p; p = p->nextArc) {
                int w = p->adjvex;
                if (!visited(w))
                    enQueue(qu, w);
            }
        }
    }
}


/**
 * 从顶点v出发广度优先遍历图g(邻接矩阵)
 */
void BFS_M(MGraph g, int v) {
    visit(v);
    visited[v] = TRUE;
    enQueue(qu, v);
    while (!isEmpty(qu)) {
        deQueue(qu, v);
        for (int w = 0; w < g.vexnum; ++w) {
            if (!visited[w] && g.edges[v][w] == 1) {
                visit[w];
                visited[w] = TRUE;
                enQueue(qu, w);
            }
        }
    }
}


/**
 * BFS求解单源最短路径(非带权图)
 * 各顶点到u的最短路径
 */
bool visited[MaxVertexNum];  // 访问标记

SqQueue qu;  // BFS辅助队列

int dist[MaxVertexNum];  // 距离

void minDistBFS1(Graph g, int u) {
    // 初始化距离
    for (i = 0; i < g.vexnum; i++)
        dist[i] = -1;

    // 初始化标记数组
    for (int i; = 0; i < g.vexnum; i++)
        visited[i] = FALSE;

    visited[u] = TRUE;
    dist[u] = 0;
    enQueue(qu, u);
    while (!isEmpty(qu)) {
        deQueue(qu, u);
        // 访问u所有未访问过的邻接点,使其距离在u距离的基础上+1
        for (int w = getFirsrNeighbor(g, u); w >= 0; w = getNextNeighbor(g, u, w))
            if (!visited(w)) {
                visited[w] = TRUE;
                dist[w] = dist[u] + 1;
                enQueue(qu, w);
            }
    }
}

void minDistBFS2(Graph g, int u) {
    for (i = 0; i < g.vexnum; i++)
        dist[i] = -1;
    for (int i; = 0; i < g.vexnum; i++)
        visited[i] = FALSE;

    initQueue(qu);
    enQueue(qu, u);
    int dist = 0;
    while (!isEmpty(qu)) {
        int size = getQuSize(qu);
        while (size > 0) {
            deQueue(qu, u);
            visited[u] = TRUE;
            dist[u] = dist;
            --size;
            // 访问u所有未访问过的邻接点
            for (int w = getFirsrNeighbor(g, u); w >= 0; w = getNextNeighbor(g, u, w))
                if (!visited(w))
                    enQueue(qu, w);
        }
        ++dist;
    }
}


/**
 * 深度优先搜索遍历DFS
 */
bool visited[MaxVertexNum];  // 访问标记数组

void DFSTraverse(Graph g) {
    // 标记数组初始化
    for (int i = 0; i < g.vexnum; ++i)
        visited[i] = FALSE;

    // 从顶点0开始遍历
    for (int i = 0; i < g.vexnum; ++i)
        if(!visited[i])
            DFS(g, i);
}

/**
 * 从顶点v出发广度优先遍历图g(通用)
 */
void DFS(Graph g, int v) {
    visite(v);
    visited[v] = TRUE;
    for (int w = getFirstNeighbor(g, v); w >= 0; w = getNextNeighbor(g, v, w))
        if (!visited[w])
            DFS(g, w);
}

/**
 * 从顶点v出发广度优先遍历图g(邻接表)
 */
void DFS_AL(ALGraph g, int v) {
    visit[v];
    visited[v] = TRUE;
    for (ArcNode *p = g.vertices[v].firstArc; p; p = p->nextArc) {
        int w = p->adjvex;
        if (!visited[w])
            DFS_AL(G, w);
    }
}

/**
 * 从顶点v出发广度优先遍历图g(邻接矩阵)
 */
void DFS_M(MGraph g, int v) {
    visit[v];
    visited[v] = TRUE;
    for (int w = 0; w < g.vexnum; ++j)
        if (!visited[w] && g.edges[v][w] == 1)
            DFS_M(g, w);
}

/**
 * 普里姆算法
 * @param G   无向连通图
 * @param v0  从v0开始
 * @param sum 返回权值和
 */
void prim(MGraph g, int v0, int &sum) {
    int lowcost[MaxVertexNum], vset[MaxVertexNum], v;  // 与v关联的边权值数组、显示加入情况的顶点表、从v开始延伸树
    int i, j, k, min;
    v = v0;
    for (i = 0; i < g.vexnum; i++) {  // 初始化lowcost[]和vset[]
        lowcost[i] = g.edges[v][i];
        vset[i] = 0;
    }
    vset[v] = 1;
    sum = 0;
    for (i = 0; i < g.vexnum - 1; i++) {
        min = INF;
        for (j = 0; j < g.vexnum; j++)  // 找v外延的最小边
            if (vset[j] == 0 && lowcost[j] < min) {
                min = lowcost[j];
                k = j;  // 最小边找到了，下一个顶点也有了
            }
        vset[k] = 1;
        v = k;
        sum += min;
        for (j = 0; j < g.vexnum; j++)  // 更新lowcost[]
            if (vset[j] == 0 && g.edges[v][j] < lowcost[j])  // 细品G.edges[v][j]<lowcost[j]
                lowcost[j] = g.edges[v][j];
    }
}


typedef struct {
    int a, b;  // 边的两个顶点
    int w;  // 权值
} Road;

Road road[MaxVertexNum-1];
int v[MaxVertexNum];  // 并查集数组

int getRoot(int a) {  // 查找根结点
    while(a != v[a])
        a = v[a];
    return a;
}


/**
 * 克鲁斯卡尔算法
 * @param G    无向连通图
 * @param sum  返回权值和
 * @param road 边数组
 */
void kruskal(MGraph G, int &sum, Road road[]) {
    int i;
    int a, b;
    sum = 0;
    for (i = 0; i < G.vexnum; i++)
        v[i] = i;
    sort(road, G.arcnum);  // 边按权值升序排序
    for (i = 0; i < G.arcnum; i++) {
        a = getRoot(road[i].a);
        b = getRoot(road[i].b);
        if (a != b) {  // a,b不在同一个连通分量
            v[a] = b;
            sum += road[i].w;
        }
    }
}


/**
 * 迪杰斯特拉算法
 */
void dijkstra(MGraph g, int v, int dist[], int path) {
    int set[MaxSize];
    int min, i, j, u;
    // 以邻接矩阵值初始化
    for (i = 0; i < g.n; i++) {
        dist[i] = g.edges[v][i];
        set[i] = 0;  // 都未并入
        path[i] = g.edges[v][i] < INF ? v : -1;
    }

    // v是源点，首先并入
    set[v] = 1;
    for (i = 0; i < g.vexnum-1; ++i) {   // 注意是n-1次
        min = INF;
        // 寻找距离源点最近的尚未并入的顶点
        for (j = 0; j < g.vexnum; ++j) {
            if (set[j] == 0 && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }
        set[u] = 1;  // 并入
        // 更新剩余结点
        for (j = 0; j < g.vexnum; j++) {
            if (set[j] == 0 && dist[u] + g.edges[u][j] < dist[j]) {
                dist[j] = dist[u] + g.edges[u][j];
                path[j] = u;
            }
        }
    }
}

void printPath(int path[], int a) {  // 输出最短路径
    int stack[MaxSize], top = -1;
    while (path[a] != -1) {
        stack[++top] = a;
        a = path[a];
    }
    stack[++top] = a;
    while (top != -1)
        cout << stack[top--] << " ";
    cout << endl;
}


/**
 * 弗洛伊德算法
 * @param G    图
 * @param Path 记录当前两顶点间最短路径要经过的中间顶点
 */
void floyd(MGraph G, int Path[][MaxSize]) {
    int i, j, k;
    int A[MaxSize][MaxSize];
    for (i = 0;i < g.vexnum; i++) {
        for (j = 0;j < g.vexnum; j++) {
            A[i][j] = g.edges[i][j];
            Path[i][j] = -1;
        }
    }
    for (k = 0;k < g.vexnum; k++) { // 中间点
        for (i = 0; i < g.vexnum; i++) { // 端点1
            for (j = 0; j < g.vexnum; j++) { // 端点2
                if (A[i][j] > A[i][k] + A[k][j]) {  // 能不能插
                    A[i][j] = A[i][k] + A[k][j];
                    Path[i][j] = k;
                }
            }
        }
    }
}


/**
 * 拓扑排序
 *
 * 时间复杂度
 * 邻接表 O(|V|+|E|)
 * 邻接矩阵 O(|V|^2)
 */
bool topologicalSort(Graph g) {
    SqStack st;
    initStack(st);  // 存储入度为0的顶点
    int print[MaxSize];  // 存储排序序列
    // 将入度为0的顶点入栈
    int i;
    for (i = 0; i < g.vexnum; ++i)
        if (indegree[i] == 0)
            push(st, i);
    int count = 0;  // 记录已排好的顶点数

    while (!isEmpty(st)) {
        pop(st, i);
        print[count++] = i;
        // 所有i指向的顶点的入度-1
        for (ArcNode* p = g.vertices[i].firstarc; p; p = p->nextArc)
            // 将入度减为0的顶点压入栈
            if (!(--indegree[p->adjvex]))
                push(st, p->adjvex);
    }

    return count == g.vexnum;
}