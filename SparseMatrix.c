/**
 * 稀疏矩阵
 */


/* 顺序存储 */
/* 三元组表示*/
/**
 * 三元组顺序表建立
 * @param A 存储稀疏矩阵的二维数组
 * @param m A行数
 * @param n A列数
 * @param B 三元组顺序表
 */
void createTrimat(float A[][maxSize], int m, int n, float B[][3]) {
    int k = 1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0) {
                B[k][0] = A[i][j];  // 值
                B[k][1] = i;  // 行标
                B[k][2] = j;  // 列标
                ++k;
            }
    B[0][0] = k - 1;  // 第0行用来存储非零元素个数、行数和列数
    B[0][1] = m;
    B[0][2] = n;
}

/**
 * 通过三元组顺序表打印稀疏矩阵
 * @param B 三元组
 */
void print(float B[][3]) {
    int k = 1;
    for (int i = 0; i < B[0][1]; ++i) {
        for (int j = 0; j < B[0][2]; ++j) {
            if (i == (int)B[k][1] && j == (int)B[k][2]) {
                printf("%d ", B[k][0]);
                ++k;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

/* 伪地址表示 */
每行只有两个存储单元: 值与伪地址.
伪地址即元素在矩阵中按照行优先或列优先存储的相对位置.
对于m×n的稀疏矩阵,其元素A[i][j]的伪地址计算方法: n(i−1)+j,可反推真实地址.

/* 链式存储 */
/* 邻接表表示 */

/* 十字链表普通结点 */
tpyedef struct OLNode {
    int row, col;  // 行列下标
    struct OLNode *right, *down;  // 该非零元所在行表和列表的后继链域
    float val;
} OLNode;

/* 十字链表头结点 */
tpyedef struct {
    OLNode *rhead, *chead;
    int m, n, k;  // 行数、列数、非零元个数
} CrossList;

/**
 * 十字链表建立
 * @param A 存储稀疏矩阵的二维数组
 * @param m A行数
 * @param n A列数
 * @param k 非零元个数
 * @param B 十字链表
 */
bool createCrossListMat(float A[][maxSize], int m, int n, int k, CrossList &M) {
    // 初始化十字链表头结点
    if (M.rhead != NULL) free(M.rhead);
    if (M.chead != NULL) free(M.chead);
    M.m = m;
    M.n = n;
    M.k = k;
    
    // 初始化每个行表、列表的头结点
    if (!(M.rhead = (OLNode*)malloc(sizeof(OLNode)*m))) return false;  // m个行表头结点
    for (int i = 0; i < m; ++i) {
        M.rhead[i].right = NULL;
        M.rhead[i].down = NULL;
    }
    if(!(M.chead = (OLNode*)malloc(sizeof(OLNode)*n))) return false;  // n个列表头结点
    for (int i = 0; i < n; ++i) {
        M.chead[i].right = NULL;
        M.chead[i].down = NULL;
    }
    
    // 先统一设置好指向每个列表尾结点的指针
    OLNode *temp_c[maxSize];
    for (int j = 0; j < n; ++j)
        temp_c[j] = &(M.chead[j]);

    // 往十字链表里装结点
    // 从上到下、从左往右,一行一行地装
    for (int i = 0; i < m; ++i) {
        OLNode *r = &(M.rhead[i]);  // 跟踪当前行表的尾结点
        for (int j = 0; j < n; ++j) {
            if (A[i][j] != 0) {
                OLNode *p = (OLNode*)malloc(sizeof(OLNode));
                p->cow = i;
                p->rol = j;
                p->val = A[i][j];
                p->down = NULL;
                p->right = NULL;
                r->right = p;
                r = p;
                // 更新当前列表尾结点指针
                temp_c[j]->down = p;
                temp_c[j] = p;
            }
        }
    }

    return true;
}