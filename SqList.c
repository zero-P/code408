/**
 * 顺序表
 */

/* 数组静态分配 */
#define MaxSize 50
typedef struct {
    ElemType data[MaxSize];
    int length;
} SqList;
// 初始化
void initList(SqList &sl) {
    sl.length = 0;
}

/* 数组动态分配 */
#define InitSize 100
typedef struct {
    ElemType *data;
    int MaxSize, length;
} SqList;
// 初始化
void initList(SqList &sl) {
    sl.data = (ElemType*)malloc(sizeof(ElemType)*InitSize);  // C
    sl.data = new ElemType[InitSize];  // C++
    sl.length = 0;
    sl.MaxSize = InitSize;
}

/**
 * 插入
 * @param sl 顺序表
 * @param i  插入位序 [1...sl.length+1]
 * @param e  待插值
 * @return   操作结果
 * T(n)      最好O(1) 最坏O(n) 平均O(n)
 */
bool insertList(SqList &sl, int i, ElemType e) {
    // 插入位序合法性校验
    if (i < 1 || i > sl.length + 1) return false;
    // 长度校验
    if (sl.length >= MaxSize) return false;

    // 插入操作
    for (int j = sl.length; j >= i; --j)
        sl.data[j] = sl.data[j-1];

    sl.data[i-1] = e;
    ++sl.length;

    return true;
}

/**
 * 删除
 * @param sl 顺序表
 * @param i  删除位序 [1...sl.length]
 * @param e  待删元素值
 * @return   操作结果
 * T(n)      最好O(1) 最坏O(n) 平均O(n)
 */ 
bool delList(SqList &sl, int i, ElemType &e) {
    // 删除位序合法性校验
    if (i < 1 || i > sl.length) return false;

    // 保存待删元素值
    e = sl.data[i-1];

    // 删除操作
    for (int j = i; j < sl.length; ++j)
        sl.data[j-1] = sl.data[j];

    --sl.length;

    return true;
}

/**
 * 按值查找(顺序查找)
 * @param sl 顺序表
 * @param e  待查值
 * @return   所在位序
 * T(n)      最好O(1) 最坏O(n) 平均O(n)
 */
int locateElem(SqList sl, ElemType e) {
    for (int i = 0; i < sl.length; ++i)
        if (e == sl.data[i])
            return i + 1;

    return 0;
}