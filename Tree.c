/**
 * 树与二叉树
 */

/* 二叉树结点(链式) */
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/**
 * 先序遍历NLR(递归)
 */
void preOrder(BiTree t) {
    if (t == NULL) return;
    
    visit(t);
    preOrder(t->lchild);
    preOrder(t->rchild);
}

/**
 * 中序遍历LNR(递归)
 */
void inOrder(BiTree t) {
    if (t == NULL) return;

    inOrder(t->lchild);
    visit(t);
    inOrder(t->rchild);
}

/**
 * 后序遍历LRN(递归)
 */
void postOrder(BiTree t) {
    if (t == NULL) return;

    postOrder(t->lchild);
    postOrder(t->rchild);
    visit(t);
}

/**
 * 先序遍历(非递归)
 */
void preOrderNonrecur(BiTree t) {
    SqStack st;
    initStack(st);
    BiTNode *p = t;
    while (p || !isEmpty(st)) {
        if (p) {
            visit(p);
            push(st, p);
            p = p->lchild;
        } else {
            pop(st, p);
            p = p->rchild;
        }
    }
}

/**
 * 中序遍历(非递归)
 */
void inOrderNonrecur(BiTree t) {
    SqStack st;
    initStack(st);
    BiTNode *p = t;
    while (p || !isEmpty(st)) {
        if (p) {
            push(st, p);
            p = p->lchild;
        } else {
            pop(st, p);
            visit(p);
            p = p->rchild;
        }
    }
}

/**
 * 后序遍历(非递归)
 */
void postOrderNonrecur(BiTree t){
    SqStack st;
    initStack(st);
    BiTNode *p = t;
    BiTNode *r = NULL;  // 跟踪上一次访问的结点
    while (p || !isEmpty(st)) {
        if (p) {  // 一路向左
            push(st, p);
            p = p->lchild;
        } else {
            getTop(st, p);
            if (p->rchild && p->rchild != r) {  // 右拐一下
                p = p->rchild;
            } else {  // 左右都走不了,那就访问
                pop(st, p);
                visit(p);
                r = p;
                p = NULL;  // 访问完需要重置p指针
            }
        }
    }
}

/**
 * 层次遍历
 */
void levelOrder(BiTree t) {
    if (t == NULL) return;

    SqQueue qu;
    initQueue(qu);
    enQueue(qu, t);
    BiTNode *p;
    while (!isEmpty(qu)) {
        deQueue(qu, p);
        visit(p);
        if (p->lchild) enQueue(qu, p->lchild);
        if (p->rchild) enQueue(qu, p->rchild);
    }
}

/* 线索二叉树 */
tpyedef struct TBiTNode {
    ElemType data;
    struct TBiTNode *lchild, *rchild;
    int ltag, rtag;  // 0孩子 1线索
} TBiTNode, *TBiTree;

/* 中序线索二叉树 */

/**
 * 通过中序遍历(递归)对二叉树线索化
 * @param p   当前访问的结点
 * @param pre 上一个访问的结点
 */
void inThread(TBiTNode *&p, TBiTNode *&pre) {
    if (p == NULL) return;

    // 线索化左子树
    inThread(p->lchild, pre);

    // 建立当前结点前驱线索
    if (p->lchild == NULL) {
        p->lchild = pre;
        p->ltag = 1;
    }

    // 建立前驱结点后继线索
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = p;
        pre->rtag = 1;
    }

    // 当前结点处理完毕,标记成为上一个访问的结点
    pre = p;

    // 线索化右子树
    inThread(p->rchild, pre);
}

/**
 * 通过中序遍历建立中序线索二叉树
 */
void createInThread(TBiTree t) {
    if (t == NULL) return;
    
    TBiTNode* pre = NULL;
    // 中序遍历线索化二叉树
    inThread(t, pre);
    // 处理最后一个结点
    pre->rchild = NULL;
    pre->rtag = 1;
}

/**
 * 求中序线索二叉树中中序序列下的第一个结点
 * @param  p 中序线索二叉树根结点
 * @return   目标结点
 */
TBiTNode *firstNodeIn(TBiTNode *p) {
    // 该树可能是子树,故循环条件不能是 p->lchild != NULL
    while (p->ltag == 0) p = p->lchild;  // 即最左结点
    return p;
}

/**
 * 求中序线索二叉树中中序序列下的最后一个结点
 * @param  p 中序线索二叉树根结点
 * @return   目标结点
 */
TBiTNode *lastNodeIn(TBiTNode *p) {
    // 该树可能是子树,故循环条件不能是 p->rchild != NULL
    while (p->rtag == 0) p = p->rchild;  // 即最右结点
    return p;
}

/**
 * 求中序线索二叉树中结点在中序序列下的前驱
 * @param  p 中序线索二叉树某结点
 * @return   p的前驱结点
 */
TBiTNode *priorNodeIn(TBiTNode *p) {
    return p->ltag == 1 ? p->lchild : lastNodeIn(p->lchild);
}

/**
 * 求中序线索二叉树中结点在中序序列下的后继
 * @param  p 中序线索二叉树某结点
 * @return   p的后继结点
 */
TBiTNode *nextNodeIn(TBiTNode *p) {
    return p->rtag == 1 ? p->rchild : firstNodeIn(p->rchild);
}

/**
 * 中序线索二叉树的中序遍历
 */
void inOrder(TBiTree t) {
    for (TBiTNode *p = firstNodeIn(t); p != NULL; p = nextNodeIn(p))
        visit(p);
}

/* 先序线索二叉树 */
/**
 * 通过先序遍历对二叉树线索化
 * @param p   当前访问的结点
 * @param pre 上次访问的结点
 */
void preThread(TBiTNode *&p, TBiTNode *&pre) {
    if (p == NULL) return;

    // 建立当前结点前驱线索
    if (p->lchild == NULL) {
        p->lchild = pre;
        p->ltag = 1;
    }
    // 建立前驱结点后继线索
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = p;
        pre->rtag = 1;
    }

    // 标记当前结点成为上一个访问过的结点
    pre = p;

    // 线索化左子树
    preThread(p->lchild, pre);

    // 线索化右子树
    preThread(p->rchild, pre);
}

/**
 * 求先序线索二叉树中结点在先序序列下的前驱
 * 为其双亲或是左兄弟子树最右叶结点
 * 都需要找到双亲,要是有左孩子就无法找到
 */

/**
 * 求先序线索二叉树中结点在先序序列下的后继
 */
TBiTNode *nextNodePre(TBiTNode *p) {
    return p->ltag == 0 ? p->lchild : p->rchild;
}

/**
 * 先序线索二叉树的先序遍历
 */
void preOrder(TBiTree t) {
    if (t ！= NULL) {
        TBiTNode *p = T;
        while (p ！= NULL) {
            while (p->ltag == 0) {  // 一路向左
                visit(p);
                p = p->lchild;
            }
            visit(p);
            p = p->rchild;  
        }
    }
}

/**
 * 通过后序遍历对二叉树线索化
 * @param p   正在访问的结点
 * @param pre 刚刚访问过的结点
 */
void postThread(TBiTNode *p, TBiTNode *&pre) {
    if (p == NULL) return;

    // 线索化左子树
    postThread(p->lchild, pre);

    // 线索化右子树
    postThread(p->rchild, pre);  

    // 建立当前结点的前驱线索
    if (!p->lchild) {
        p->lchild = pre;
        p->ltag = 1;
    }

    // 建立前驱结点的后继线索
    if (pre && !pre->rchild) {  
        pre->rchild = p;
        pre->rtag = 1;
    }

    // 标记当前结点成为上一个访问过的结点
    pre = p;
}

/**
 * 求后序线索二叉树中结点p在后序序列下的前驱
 */
TBiTNode *priorNodePost(TBiTNode *p) {
    return p->rtag == 0 ? p->rchild : p->lchild;
    // 有右孩子 → 右孩子
    // 无右孩子但有左孩子 → 左孩子
    // 左右孩子都无 → 左链域(线索)    
}

/**
 * 求后序线索二叉树中结点在后序序列下的后继
 * 为其双亲或是右兄弟子树最左叶结点
 * 都需要找到双亲,要是有右孩子就无法找到
 */

/**
 * 后序线索二叉树的后序遍历
 * 后继不一定找得到,可以给结点增加指向双亲的指针域或借助栈
 */


/* 二叉排序树 BST */
/**
 * 查找关键字 非递归
 * @param  T   二叉排序树
 * @param  key 关键字
 * @return     关键字结点
 */
BiTNode *searchBST(BiTree T, int key) {
    while (T && key != T->data)
        T = key < T->data ? T->lchild : T->rchild;
    return T;
}

/**
 * 插入关键字
 * @param  T   二叉排序树
 * @param  key 关键字
 * @return     成功1,失败0
 */
int insertBST(BiTree &T, int key) {
    if (!T) {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = key;
        T->lchild = T->rchild = NULL;
        return 1;
    }

    if (key == T->data) return 0;

    if (key < T->data) return BSTInsert(T->lchild, key);
    
    return BSTInsert(T->rchild, key);
}

/**
 * 删除
 */
// -1. 叶子结点直接删
// -2. 只有左/右子树，拿子树替换上
// -3. 左右子树都有，则拿直接前驱(左子树最右)/直接后继(右子树最左)值原位低缓，再按前两种情况删该直接前驱/直接后继

/**
 * 构造
 * @param T   二叉排序树
 * @param key 关键字数组
 * @param n   关键字个数
 */
void createBST(BiTree &T, int key[], int n) {
    T = NULL;
    for (int i = 0; i < n; ++i)
        insertBST(T, key[i]);
}

/* 树(双亲表示法) */
#define MAX_TREE_SIZE 100

/**
 * 结点
 */
typedef struct {
    ElemType data;
    int parent;
} TNode;

/**
 * 树
 */
typedef struct {
    TNode nodes[MAX_TREE_SIZE];
    int n;
} Tree;

/* 树(孩子兄弟表示法/二叉树表示法) */
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstChild, *nextSibling;  // 第一个孩子和右兄弟指针
} CSNode, *CSTree;

/* 并查集 */
/* 存储结构:树(森林)的双亲表示 */
#define SIZE 100
int uFSet[SIZE];  // 集合元素数组(双亲指针数组)

/**
 * 并查集的初始化
 * 将集合中的每个元素都初始化为只有一个单元素的子集合
 */
void initial(int uFSet[]) {
    for (int i = 0; i < SIZE; ++i)
        uFSet[i] = -1;
}

/**
 * 查找集合中单元素x所在的子集合,返回该子集合的根结点
 * 判断两个元素是否属于同一集合,只需分别找到它们的根结点,比较根结点是否相同即可
 */
int find(int uFSet[], int x) {
    while (uFSet[x] >= 0)
        x = uFSet[x];
    return x;
}

/**
 * 改进的find操作
 * 增加"压缩路径"功能
 */
int findPro(int uFSet[], int x) {
    int root = x;
    while (uFSet[root] >= 0)
        root = uFSet[root];
    // 压缩路径
    while (x != root) {
        int t = uFSet[x];  // 记录x当前的根结点
        uFSet[x] = root;  // x挂到根结点
        x = t;  // 再对x之前的根结点进行路径压缩
    }
    return root;
}

/**
 * 求两个不相交子集合的并集
 * 把子集合root2并入root1
 */
void union(int uFSet[], int root1, int root2) {
    if (root1 == root2) return;
    uFSet[root2] = root1;
}
// 如果将两个元素所在的集合合并为一个集合,那么就需要先找到两个元素的根结点

/**
 * 改进的union操作(小树合并到大树)
 * 需要令根结点的绝对值保存集合树中的成员数量
 */
void unionPro(int uFSet[], int root1, int root2) {
    if (root1 == root2) return;
    if (uFSet[root2] > uFSet[root1]) {  // root1成员更少
        uFSet[root1] += uFSet[root2];
        uFSet[root2] = root1;
    } else {
        uFSet[root2] += uFSet[root1];
        uFSet[root1] = root2;
    }
}