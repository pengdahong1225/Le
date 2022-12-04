#include "source.h"
/* 常见排序算法 */
class Solution
{
public:
    vector<int> getLeastNumbers(vector<int> &arr, int k)
    {
        quickSort(arr, 0, arr.size() - 1);
        return vector<int>(arr.begin(), arr.begin() + k);
    }

private:
    /* 升序 */
    /* 冒泡排序 O(n^2) */
    void bubbleSort(vector<int> &arr)
    {
        int len = arr.size();
        for (int i = 0; i < len - 1; i++)
        {
            for (int j = 0; j < len - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                    std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    /* 选择排序 O(n^2) */
    void SimpleSelectSort(vector<int> &arr)
    {
        int min,temp;
        for (int i = 0; i < arr.size() - 1; i++)
        {
            /* 每一轮都从无序序列中选择最小的元素放在i位置 */
            min = i;
            for (int j = i + 1; j < arr.size(); j++)
            {
                if (arr[min] > arr[j])
                    min = j;
            }
            if (min != i)
            {
                temp = arr[i];
                arr[i] = arr[min];
                arr[min] = temp;
            }
        }
    }
    /* 插入排序 O(n^2) */
    void insertSort(vector<int> &arr)
    {
        int len = arr.size();
        for (int i = 1; i < len; i++)
        {
            int key = arr[i];
            /* 每次都从有序序列的最后一个元素开始比较 */
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    /* 希尔排序 */
    void shellSort(vector<int> &arr)
    {
        int len = arr.size();
        int key, i, j;
        /* 步长循环,步长每次折半 */
        for (int step = len / 2; step > 0; step /= 2)
        {
            /* 每一组都采用插入排序 */
            for (i = step; i < len; i++)
            {
                key = arr[i];
                int j = i - step;
                while (j >= 0 && arr[j] > key)
                {
                    arr[j + step] = arr[j];
                    j -= step;
                }
                arr[j + step] = key;
            }
        }
    }

    /* 快速排序 */
    void quickSort(vector<int> &arr, int L, int R)
    {
        if (L >= R)
            return;
        int left = L, right = R;
        /* 选取arr[L]为基准数 */
        int pivot = arr[L];
        while (left < right)
        {
            /* 判断右边界,直到遇见小于基准数的元素 */
            while (left < right && arr[right] >= pivot)
                right--;
            if (left < right)
                arr[left] = arr[right];

            /* 判断左边界,直到遇见大于基准数的元素 */
            while (left < right && arr[left] <= pivot)
                left++;
            if (left < right)
                arr[right] = arr[left];
            /* 遍历完成后基准数放在left位置 */
            if (left >= right)
                arr[left] = pivot;
        }
        /* 左子序列和右子序列进行递归快排,pivot不需要加入后续排序 */
        quickSort(arr, L, right - 1);
        quickSort(arr, right + 1, R);
    }
    /* 归并排序 */

};

class MedianFinder
{
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        arr.push_back(num);
        quickSort(0, arr.size() - 1);
    }

    double findMedian()
    {
        int len = arr.size();
        if (len % 2 == 0)
            return (arr[len / 2] + arr[len / 2 - 1]) / 2.0;
        else
            return arr[len / 2];
    }

private:
    /* 插入排序 */
    void insertSort()
    {
        int len = arr.size();
        for (int i = 1; i < len; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    vector<int> arr;
    /* 快排 */
    void quickSort(int L, int R)
    {
        if (L >= R)
            return;
        int left = L, right = R;
        /* 选取arr[L]为基准数 */
        int pivot = arr[L];
        while (left < right)
        {
            /* 判断右边界,直到遇见小于基准数的元素 */
            while (left < right && arr[right] >= pivot)
                right--;
            if (left < right)
                arr[left] = arr[right];

            /* 判断左边界,直到遇见大于基准数的元素 */
            while (left < right && arr[left] <= pivot)
                left++;
            if (left < right)
                arr[right] = arr[left];
            /* 遍历完成后基准数放在left位置 */
            if (left >= right)
                arr[left] = pivot;
        }
        /* 左子序列和右子序列进行递归快排 */
        quickSort(L, right - 1);
        quickSort(right + 1, R);
    }
};
