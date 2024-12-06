#include <stdio.h>
#include <malloc.h>

/* 公用小函数 */
/**
 * 两数交换
 * @param a 数a
 * @param b 数b
 */
void swap(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * 打印数组
 * @param nums 数组
 * @param len  数组长度
 */
void printfArray(int *nums, int len) {
    for (int i = 0; i < len; i++)
        printf("%d ", nums[i]);
}


/* 插入排序 */
/**
 * 直接插入排序
 * @param A 待排序表
 * @param n 表长(首位为哨兵)
 * @时间复杂度 O(n) O(n^2)
 */
void insertSort(int A[], int n) {
    int i, j;
    for (i = 2; i < n; ++i)
        if (A[i] < A[i-1]) {  // [1,i-1]有序
            A[0] = A[i];  // 哨兵
            for (j = i - 1; A[0] < A[j]; --j)
                A[j+1] = A[j];
            A[j+1] = A[0];
        }
}


/**
 * 折半插入排序
 * @param A 待排序表(无重复)
 * @param n 表长(首位为哨兵)
 * @时间复杂度 O(nlog2{n}) O(n^2)
 */
void biInsertSort(int A[], int n) {
    int i, j, low, high, mid;
    for (i = 2; i <= n; ++i) {
        A[0] = A[i];  // 哨兵
        low = 1;
        high = i - 1;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (A[mid] > A[0])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // 插入位置为high+1
        // high+1到i-1的元素往后挪一位
        for (j = i - 1; j > high; --j)
            A[j+1] = A[j];
        A[high+1] = A[0];
    }
}


/**
 * 希尔排序(缩小增量排序)
 * @param A 待排序表
 * @param n 表长(首位只用作暂存)  // 想下为啥A[0]不能作为哨兵了?
 * @时间复杂度 取决于增量序列函数 希尔增量O(n^2)
 */
void shellSort(int A[], int n) {
    int i, j, d;
    for (d = n / 2; d >= 1; d /= 2)  // 希尔增量
        for (i = d + 1; i <= n; ++i)  // 按组循环
            if (A[i] < A[i-d]) {
                A[0] = A[i];
                for (j = i - d; j > 0 && A[0] < A[j]; j -= d)
                    A[j+d] = A[j];
                A[j+d] = A[0];
            }
}


/* 交换排序 */
/**
 * 冒泡排序 (从后往前)
 * @param A 待排序表
 * @param n 表长
 * @时间复杂度 O(n^2)
 */
void bubbleSort(int A[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool flag = false;
        for (int j = n - 1; j > i; --j)
            if (A[j] < A[j-1]) {
                swap(&A[j], &A[j-1]);
                flag = true;
            }
        // 一整趟下来没交换,说明全员已有序
        if (!flag) return;
    }
}


/**
 * 快速排序-子表划分操作
 * @return 当前子表枢轴位置
 */
int partition(int A[], int low, int high) {
    int pivot = A[low];  // 当前表首元素设为枢轴
    while (low < high) {
        while (high > low && A[high] >= pivot)  // 从当前最右开始找一个小的放到左边
            --high;
        A[low++] = A[high];
        while (low < high && A[low] <= pivot)  // 从当前最左开始找一个大的放到右边
            ++low;
        A[high--] = A[low];
    }
    A[low] = pivot;
    return low;
}

/**
 * 快速排序
 * @param low 表头
 * @param high 表尾
 * @时间复杂度 O(nlog2{n}) O(n^2)
 */
void quickSort(int A[], int low, int high) {
    if (low >= high) return;

    // 划分当前表
    int pivotPos = partition(A, low, high);
    // 当前表划分结束
    // pivot放在了其最终位置A[pivotPos]上
    // A[low…pivotPos-1]都比pivot小,A[pivotPos+1…high]都比pivot大
    // 接下来分别递归地对A[low…pivotPos-1]和A[pivotPos+1…high]两个子表重复上述过程
    quickSort(A, low, pivotPos-1);
    quickSort(A, pivotPos+1, high);
}


/**
 * 简单选择排序
 * @param A 待排序表
 * @param n 表长
 * @时间复杂度 O(n^2)
 */
void selectSort(int A[], int n) {
    int i, j, min;
    for (i = 0; i < n; ++i) {
        min = i;
        for (j = i + 1; j < n; ++j)
            if (A[min] > A[j])
                min = j;
        if (min != i)
            swap(&A[i], &A[min]);
    }
}

/**
 * 向下调整子树
 * @param A   大根堆(A[0]用作暂存)
 * @param k   待调整子树根结点
 * @param len 堆容量
 */
void headAdjust(int A[], int k, int len) {
    if (len == 1) return;
    A[0] = A[k];  // A[0]暂存根结点值
    // 向下调整
    for (int i = 2 * k; i <= len; i *= 2) {
        // i取最大子结点
        if (i < len && A[i] < A[i+1]) ++i;
        if (A[0] >= A[i]) break;
        A[k] = A[i];
        k = i;  // i为新根,继续向下筛选
    }
    A[k] = A[0];  // 被筛选结点的值放入最终位置
}

/**
 * 初始建堆
 * @param A   待排序表(A[0]用作暂存)
 * @param len 堆容量
 * 时间复杂度  O(n)
 */
void buildMaxHeap(int A[], int len) {
    // 从结点n/2到1向下调整堆
    for (int i = len / 2; i > 0; i--) {  
        headAdjust(A, i, len);
    }
}

/**
 * 堆排序
 * @param A   待排序表(A[0]用作暂存)
 * @param len 堆容量
 */
void headSort(int A[], int len) {
    // 初始建堆
    buildMaxHeap(A, len);
    // 输出与调整
    for (int i = len; i > 1; --i) {
        // 输出堆顶元素(和堆底元素交换)
        swap(&A[i], &A[1]);
        // 调整剩余i-1个元素为大根堆
        headAdjust(A, 1, i-1);
    }
}

/**
 * 堆 插入和上浮
 * 算法思路：把新结点放到堆的末端,再对这个新结点向上调整
 * 一次上浮,最多和所有的父节点交换,共h次
 * 时间复杂度：O(logn)
 */

/**
 * 堆 删除和下沉
 * 算法思路：删除堆顶元素,尾结点覆盖顶结点,堆大小-1,从堆顶进行下沉
 * 一次下沉,每一层最多和一个孩子交换一次
 * 时间复杂度：O(logn)
 */


/**
 * 二路归并操作
 */
int n;
int *B = (int *)malloc(n*sizeof(int));  // 辅助数组
void merge(int A[], int low, int mid, int high) {
    int i, j, k;
    // 要归并的两个表的元素先复制到辅助数组B对应位置上
    for (k = low; k <= high; ++k)
        B[k] = A[k];

    // 归并 在B中比较,取较小值依次复制到A中
    for (i = low, j = mid + 1, k = low; i <= mid && j <= high; ++k)
            A[k] = B[i] <= B[j] ? B[i++] : B[j++];

    // 可能存在某一个子表有多余元素尚未参与比较而另一个子表全部元素已归并完成的情况
    while (i <= mid)    A[k++] = B[i++];
    while (j <= high)   A[k++] = B[j++];
}

/**
 * 二路归并排序
 * 时间复杂度 O(nlogn) 单趟O(n),共需logn↑趟
 */
void mergeSort(int A[], int low, int high) {
    if (low >= high) return;

    // 从中间划分两个子序列
    int mid = low + (high - low) / 2;
    // 对左侧子序列进行递归二路排序
    mergeSort(A, low, mid);
    // 对右侧子序列进行递归二路排序
    mergeSort(A, mid+1, high);
    // 归并
    merge(A, low, mid, high);
}

/**
 * 计数排序-空间换时间
 * 时间复杂度:O(n+k)
 */
void countSort(int A[], int B[], int n, int k) {
    int i, C[k];
    // 初始化计数数组
    for (i = 0; i < k; ++i)
        C[i] = 0;
    // C[A[i]]保存的是等于A[i]的元素的个数
    for (i = 0; i < n; ++i)
        ++C[A[i]];
    // C[x]保存的是小于等于x的元素个数
    for (i = 1; i < k; ++i)
        C[i] += C[i-1];
    // 从后往前遍历,将元素A[i]放在输出数组B的正确位置上
    for (i = n - 1; i >= 0; --i)
        B[--C[A[i]]] = A[i];
}

/**
 * 计数排序-时间换空间
 * 时间复杂度:O(n^2)
 */
void cmpCountSort(int a[], int b[], int n) {
    int i, j, *count;
    count = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) count[i] = 0;
    for (i = 0; i < n - 1; ++i)
        for (j = n + 1; j < n; ++j)
            if (a[i] < a[j])
                ++count[j];
            else
                ++count[i];
    for (i = 0; i < n; ++i) b[count[i]] = a[i];
    free(count);
}

int main() {
    int A[] = {2,4,3,0,2,3};
    int B[6];
    countSort(A,B,6,5);
    printfArray(B, 6);
    return 0;
}