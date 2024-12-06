/**
 * 顺序查找
 */
typedef struct {
    ElemType *elem;
    int tableLen;
} SSTable;

int seqSearch(SSTable st, ElemType key) {
    st.elem[0] = key;  // 哨兵,作用是使下面的for循环不必判断数组越界
    for (int i = st.tableLen; st.elem[i] != key; --i);
    return i;  // 若返回0则查找失败
}


/**
 * 折半查找/二分查找
 */
int biSearch(SSTable st, ElemType key) {
    int low = 0, high = st.length - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (st.elem[mid] == key) {
            return mid;
        } else if (st.elem[mid] > key) {
            high = mid - 1;
        } else {
            low = low + 1;
        }
    }
    return -1;
}

#define m 3  // B树的阶,暂设为3

typedef struct BTNode {
    int keyNum;  // 结点中关键字个数
    struct BTNode *parent;  // 指向双亲结点
    KeyType key[m+1];  // 关键字向量,0号单元未用
    struct BTNode *ptr[m+1];  // 子树指针向量
    Record *recprt[m+1];  // 记录指针向量,0号单元未用
} BTNode, *BTree;