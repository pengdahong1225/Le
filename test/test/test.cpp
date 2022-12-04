// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "source.h"
using namespace std;
class MedianFinder
{
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        arr.push_back(num);
        std::for_each(arr.begin(), arr.end(), [&](int a) {cout << a << " "; });
        cout << '\n';
        insertSort();
        std::for_each(arr.begin(), arr.end(), [&](int a) {cout << a << " "; });
        cout << '\n';
    }

    double findMedian()
    {
        int len = arr.size();
        cout << "arr[len / 2]=" << arr[len / 2] << endl;
        cout << "arr[len / 2 - 1]=" << arr[len / 2 - 1] << endl;
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
};

class Solution
{
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2)
    {
        vector<int> ans;
        dfs(root1, ans);
        dfs(root2, ans);
        insertSort(ans);
        return ans;
    }

    void shellSort(vector<int>& arr)
    {
        int len = arr.size();
        int key, i, j;
        /* 步长循环 */
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

private:
    void dfs(TreeNode* root, vector<int>& arr)
    {
        if (root == nullptr)
            return;
        std::stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        while (!nodeStack.empty())
        {
            TreeNode* node = nodeStack.top();
            nodeStack.pop();
            arr.push_back(node->val);
            if (node->right != nullptr)
            {
                cout << "right"<< endl;
                nodeStack.push(node->right);
            }
            if (node->left != nullptr)
            {
                cout << "left" << endl;
                nodeStack.push(node->left);
            }
        }
    }
    void insertSort(vector<int>& arr)
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
};

int main()
{
    Solution obj;
    /*TreeNode* root1,*root2;
    root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(4);

    root2 = new TreeNode(1);
    root2->left = new TreeNode(0);
    root2->right = new TreeNode(3);
    vector<int> arr = obj.getAllElements(root1, root2);
    std::for_each(arr.begin(), arr.end(), [](int it) {cout << it << " "; });
    cout << endl;*/

    vector<int> arr{ 15,5,2,7,12,6,1,4,3,9,8,10 };
    cout << "arr: " << endl;
    std::for_each(arr.begin(), arr.end(), [](int it) {cout << it << " "; });
    obj.shellSort(arr);
    cout << '\n' << "shellSort arr:" << endl;
    std::for_each(arr.begin(), arr.end(), [](int it) {cout << it << " "; });
    return 0;
}
