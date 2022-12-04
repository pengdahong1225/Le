#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<stack>
#include<algorithm>
#include<functional>
#include<queue>
using namespace std;
/* 链表 */
typedef struct ListNode {
    ListNode(int x) : val(x), next(nullptr) {}
    int val;
    struct ListNode* next;
}ListNode;
/* 二叉树 */
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
/* 线索二叉树 */
typedef struct ThreadTreeNode{
    int val;
    struct ThreadTreeNode* left;
    struct ThreadTreeNode* right;
    /*区别本节点的左右指针指向的是孩子(0)还是前驱后继(1)*/
    int ltag;
    int rtag;
}ThreadTreeNode;