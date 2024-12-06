/**
 * 队列
 */

/* 顺序队(循环队列) */
#define MaxSize 50
typedef stuct {
    int data[MaxSize];
    int front;  // 指向队头元素
    int rear;  // 指向队尾元素的下一个位置
} SqQueue;

/**
 * 初始化
 * @param qu 被操作的队列
 */
void initQueue(SqQueue &qu) {
    qu.front = qu.rear = 0;
}

/**
 * 判队空
 * @return 队空与否
 */
bool isEmpty(SqQueue qu){
    return qu.front == qu.rear;
}

/**
 * 判队满
 * 以牺牲一个存储单元的方式来区分队空和队满
 * @return 队满与否
 */
bool isFull(SqQueue qu){
    return ((qu.rear + 1) % maxSize) == qu.front;

    // 其他处理方式
    // 1.增设成员变量size,表示当前元素个数
    // 2.增设成员变量tag
    //   若因删除导致Q.rear == Q.front,tag设为0,表示队空;
    //   若因插入导致则设为1,表示队满
}

/**
 * 入队(尾入)
 * @param  qu 队列
 * @param  e 入队元素的值
 * @return   操作结果
 */
bool offer(SqQueue &qu, ElemType e) {
    // 先判满
    if (isFull(qu)) return false;

    qu.data[qu.rear] = e;
    qu.rear = (qu.rear + 1) % maxSize;
    return true;
}

/**
 * 出队(头出)
 * @param  qu 队列
 * @param  e 记录出队元素值
 * @return   操作结果
 */
bool poll(SqQueue &qu, ElemType &e) {
    // 先判空
    if (isEmpty(qu)) return false;

    e = qu.data[qu.front];
    qu.front = (qu.front + 1) % maxSize;
    return true;
}

/**
 * 获取队列长度
 * @return 队列长度
 */
int getQLen(SqQueue qu) {
    return (qu.rear - qu.front + MaxSize) % MaxSize;
}

/* 链队(带头结点) */
/**
 * 链队结点
 */
typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode;
/**
 * 链队
 */
typedef struct {
    LinkNode *front;  // 指向队头结点
    LinkNode *rear;  // 指向队尾结点
} LiQueue;

/**
 * 初始化
 */
void initQueue(LiQueue &lqu){
    lqu.front = lqu.rear = (LinkNode*)malloc(sizeof(LinkNode));  // 建立头结点
    lqu.front->next = NULL;
}

/**
 * 判队空
 */
bool isEmpty(LiQueue lqu) {
    return lqu.front == lqu.rear;
}

/**
 * 入队(尾入)
 */
void enQueue(LiQueue &lqu, ElemType e){
    // 创建新结点
    LinkNode *s = (LinkNode*)malloc(sizeof(LinkNode));
    s->data = e;
    s->next = NULL;
      
    // 入队操作  
    lqu.rear->next = s;
    lqu.rear = s;
}

/**
 * 出队(首出)
 */
bool deQueue(LiQueue &lqu, ElemType &e) {
    // 出队先判空
    if (isEmpty(lqu))  return false;

    // 出队操作
    LinkNode *p = lqu.front->next;
    e = p->data;
    lqu.front->next = p->next;

    // 若出队后队空了,则需要修改队尾指针
    if (lqu.rear == p) {
        lqu.rear = lqu.front;
    }

    free(p);

    return true;
}