/**
 * 栈
 */

/* 顺序栈 */
#define MaxSize 50
typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

/**
 * 初始化
 */
void initStack(SqStack &st) {
   st.top = -1;
}

/**
 * 判栈空
 * @return 栈空与否
 */
bool isEmpty(SqStack st) {
    return st.top == -1;
}

/**
 * 判栈满
 * @return 栈满与否
 */
bool isFull(SqStack st) {
    return st.top == MaxSize - 1;
}

/**
 * 进栈
 * @param  st 栈
 * @param  e  进栈元素的值
 * @return    操作结果
 */
bool push(SqStack &st, ElemType e) {
    if (isFull(st)) return false;
    st.data[++st.top] = e;
    return true;
}

/**
 * 出栈
 * @param  st 栈
 * @param  e  记录出栈元素的值
 * @return    操作结果
 */
bool pop(SqStack &st, ElemType &e) {
    if (isEmpty(st)) return false;
    e = st.data[st.top--];
    return true;
}

/**
 * 读栈顶
 * @param  st 栈
 * @param  e  记录栈顶值
 * @return    操作结果
 */
bool getTop(SqStack st, ElemType &e) {
    if (isEmpty(st)) return false;
    e = st.data[st.top];
    return true;
}


/* 链栈(带头结点) */ 
typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode, *LiStack;

/**
 * 判栈空
 * @return 栈空与否
 */
bool isEmpty(LiStack lst) {
    return lst->next == NULL;
}

/**
 * 进栈(头进)
 * @param  e  进栈元素的值
 */
void push(LiStack &lst, ElemType e) {
    // 新结点
    LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
    p->data = e;
    p->next = NULL;  // 可省,但是好习惯

    // 头插
    p->next = lst->next;
    lst->next = p;
}

/**
 * 出栈(头出)
 * @param  e  记录出栈元素的值
 */
bool pop(LiStack &lst, ElemType &e) {
    // 判空
    if (isEmpty(lst)) return fasle;

    LinkNode *p = lst->next;
    e = p->data;  // 记录出栈元素值
    lst->next = p->next;
    free(p);

    return true;
}