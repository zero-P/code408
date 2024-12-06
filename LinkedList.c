/**
 * 线性链表
 */

/* 静态链表 */
#define MaxSize 50
typedef struct {
    ElemType data;
    int next;
} SLinkList[MaxSize];

// 静态链表以next==-1作为其结束的标志

/* 单链表结点 */
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

/**
 * 单链表初始化
 * 默认带头结点
 */
bool initList(LinkList &liList) {
    liList = (LNode*)malloc(sizeof(LNode));
    liList->next = NULL;
    return true;
}

/**
 * 尾插法建立单链表
 * @param liList 单链表
 * @param arr    存放元素值的数组
 * @param num    元素个数
 * T(n)=O(n)
 */
void createListT(LinkList &liList, int arr[], int num) {
    // 初始化链表,设置头结点
    initList(liList);

    // s用来接纳新结点,r用来跟踪链表尾结点
    LNode *s, *r = liList;

    // 尾插操作
    for (int i = 0; i < num; ++i) {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = arr[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;  // 尾结点指针置空
}

/**
 * 头插法建立单链表
 * @param liList 待建单链表
 * @param arr    存放元素值的数组
 * @param num    元素个数
 * T(n)=O(n)
 */
void createListH(LinkList &liList, int arr[], int num) {
    // 初始化链表,设置头结点
    initList(liList);

    // s用来接纳新结点
    LNode *s;

    // 头插操作
    for (int i = 0; i < num; ++i) {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = arr[i];
        s->next = liList->next;
        liList->next = s;
    }
}

/**
 * 按位序查找结点
 * T(n)=O(n)
 */
LNode *getElemBySeq(LinkList liList, int seq) {
    // 位序校验
    if (seq < 0) return NULL;

    LNode *p = liList;
    while (seq-- > 0 && p != NULL)
        p = p->next;

    return p;  // 若seq大于表长则会返回NULL
}

/**
 * 按值查找结点
 * 返回数据域等于给定值val的第一个结点(的指针)
 * T(n)=O(n)
 */
LNode *getElemByVal(LinkList liList, ElemType val) {
    LNode *p = liList->next;
    while (p != NULL && p->data != val)
        p = p->next;

    return p;  // 找不到则会返回NULL
}

/**
 * 后插(在结点p后插入新结点s)
 * T(n)=O(1)
 */
void insertBehind(LNode *p, LNode *s) {
    s->next = p->next;
    p->next = s;
}

/**
 * 在指定位序seq插入新结点s
 * T(n)=O(n)
 */
void insertBySeq(LinkList liList, int seq, LNode *s) {
    // 位序校验
    if (seq < 1) return;

    // 后插到第i-1个结点的后面
    LNode* preNode = getElemBySeq(liList, seq-1);
    if (preNode == NULL) return false;
    insertBehind(behindNode, s);
}

/**
 * 前插1(在给定结点p前插入新结点s)
 * T(n)=O(n)
 */
void insertFront1(LNode *p, LNode *s, LinkList liList) {
    // 转化为后插: 插到p的前驱结点的后面
    LNode *q = liList;
    while (q->next != p)
        q = q->next;
    insertBehind(q, s);
}

/**
 * 前插2(在给定结点p前插入新结点s)
 * T(n)=O(1)
 */
void insertFront2(LNode *p, LNode *s) {
    // 伪前插真后插: 后插,然后数据域交换
    insertBehind(p, s);
    ElemType tmp = p->data;
    p->data = s->data;
    s->data = tmp;
}

/**
 * 根据前驱结点删除结点(即删除后继结点)
 * T(n)=O(1)
 */
void delLNodeByPre(LNode *pre) {
    LNode *q = pre->next;
    pre->next = pre->next->next;
    free(q);
}

/**
 * 按位序删除结点
 * T(n)=O(n)
 */
void delLNodeBySeq(LinkList liList, int seq) {
    // 位序校验
    if (seq < 1) return;

    // 根据前驱结点进行删除操作
    LNode* preNode = getElemBySeq(liList, seq-1);
    if (preNode == NULL || preNode->next == NULL)
        return false;
    delLNodeByPre(preNode);
}

/**
 * 根据后继结点删除结点
 * @param p 要删除的结点
 * T(n)=O(1)
 */
void delLNodeByNext(LNode *p) {
    // 不能用于删除尾结点
    if (p->next == NULL) return;

    // 将后继结点的数据域赋予其自身,然后删除后继结点
    p->data = p->next->data;
    delLNodeByPre(p);
}

/**
 * 求表长(带头结点)
 * T(n)=O(n)
 */
int getLiListLen(LinkList liList) {
    LNode *p = liList;
    int len = 0;
    while (p->next != NULL) {
        p = p->next;
        ++len;
    }
    return len;
}

/**
 * 两个非递减单链表A、B归并为一个非递减单链表C
 */
void mergeLiList1(LinkList A, LinkList B, LinkList &C) {
    // 设置指针跟踪A、B当前的最小值结点
    LNode *p = A->next;
    LNode *q = B->next;

    // 初始化C
    C = A;  // 用A的头结点做C的头结点
    C->next = NULL;

    LNode *r = C;  // 设置指针r跟踪C尾结点
    free(B);  // B的头结点没用了

    // 归并操作
    while (p != NULL && q != NULL) {
        if (p->data <= q->data) {
            r->next = p;
            p = p->next;
        } else {
            r->next = q;
            q = q->next;
        }
        r = r->next;
    }
    
    // 收尾工作
    r->next = NULL;
    if (p != NULL) r->next = p;
    if (q != NULL) r->next = q;
}

/**
 * 两个非递减单链表A、B归并为一个非递增单链表C
 */
void mergeLiList2(LinkList A, LinkList B, LinkList &C) {
    LNode *p = A->next;
    LNode *q = B->next;
    C = A;
    C->next = NULL;
    free(B);

    // 归并操作
    LNode *s;  // 指向要头插的结点
    while (p != NULL && q != NULL) {
        if (p->data <= q->data) {
            s = p;
            p = p->next;
        } else {
            s = q;
            q = q->next;            
        }
        insertBehind(C, s); // 头插
    }

    // 收尾工作
    while (p != NULL) {
        s = p;
        p = p->next;
        insertBehind(C, s); // 头插
    }
    while (q != NULL) {
        s = q;
        q = q->next;
        insertBehind(C, s);  // 头插
    }
}

/* 双链表结点 */
typedef struct DLNode {
    ElemType data;
    struct DLNode *prior, *next;
} DLNode, *DLinkList;

/**
 * 尾插建表
 * @param L 待建双链表
 * @param a 存放元素值的数组
 * @param n 元素个数
 */
void createDlistT(DLinkList &L, int a[], int n) {
    // 初始化双链表,设置头结点
    L = (DLNode*)malloc(sizeof(DLNode));
    L->prior = NULL;
    L->next = NULL;

    DLNode *s;  // 接纳新结点
    r = L;  // 跟踪尾结点

    for (int i = 0; i < n; ++i) {
        s = (DLNode*)malloc(sizeof(DLNode));
        s->data = a[i];
        r->next = s;
        s->prior = r;
        r = s;
    }
    r->next = NULL;
}

/**
 * 后插(s插到p后)
 */
void insertBehindD(DLNode *p, DLNode *s) {
    s->next = p->next;
    s->prior = p;
    p->next = s;
    if (s->next != NULL) s->next->prior = s;
}

/**
 * 删除p的后继
 */
void delDLNode(DLNode *p) {
    DLNode *q = p->next;
    p->next = q->next;
    if (q->next != NULL) q->next->prior = p;
    free(q);
}

/* 循环单链表 */
判空: 头结点的next指针是否等于头指针

/* 循环双链表 */
判空: 头结点的prior和next指针是否都等于头指针