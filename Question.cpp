#include "source.h"
/* 最近公共祖先 */
class Solution
{
public:
    /* 最近公共祖先的定义： 设节点 root 为节点 p,q 的某公共祖先，若其左子节点 root.left
    和右子节点 root.right 都不是 p,q 的公共祖先，则称 root 是 “最近的公共祖先”. */
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        while (root != nullptr)
        {
            if (p->val > root->val && q->val > root->val)
                root = root->right;
            else if (p->val < root->val && q->val < root->val)
                root = root->left;
            else
                break;
        }
        return root;
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr || root == p || root == q)
            return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left == nullptr && right == nullptr)
            return nullptr;
        else if (left == nullptr && right != nullptr)
            return right;
        else if (left != nullptr && right == nullptr)
            return left;
        return root;
    }
};

/*二叉树的最大深度*/
class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
    bool isBalanced(TreeNode *root)
    {
        /* 从底至顶,剪枝 */
        return dfs(root) != -1;
    }

private:
    int dfs(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int left = dfs(root->left);
        if (left == -1)
            return -1;
        int right = dfs(root->right);
        if (right == -1)
            return -1;
        return std::abs(left - right) < 2 ? std::max(left, right) + 1 : -1;
    }
};

/*二叉搜索树的第K大节点*/
class Solution
{
public:
    int kthLargest(TreeNode *root, int k)
    {
        std::stack<TreeNode *> Nodestack;
        while (!Nodestack.empty() || root != nullptr)
        {
            while (root != nullptr)
            {
                Nodestack.push(root);
                root = root->right;
            }
            if (!Nodestack.empty())
            {
                root = Nodestack.top();
                Nodestack.pop();
                if (k == 1)
                    return root->val;
                root = root->left;
                k--;
            }
        }
        return 0;
    }
};

/*删列造序*/
class Solution
{
public:
    int minDeletionSize(vector<string> &strs)
    {
        int count = 0;
        for (int col = 0; col < strs[0].size(); col++)
        {
            for (int row = 1; row < strs.size(); row++)
            {
                if (strs[row][col] < strs[row - 1][col])
                {
                    count++;
                    break;
                }
            }
        }
        return count;
    }
};

/*单词搜索*/
class Solution
{
public:
    bool exist(vector<vector<char>> &board, string word)
    {
        /* dfs+剪枝 */
        int rows = board.size();
        int cols = board[0].size();
        /* 每个格子都做一次起点开启dfs */
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (dfs(board, word, 0, i, j))
                    return true;
            }
        }
        return dfs(board, word, 0, 0, 0);
    }

private:
    bool dfs(vector<vector<char>> &board, string &word, int pos, int i, int j)
    {
        /* 剪枝 */
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || board[i][j] != word[pos])
            return false;
        if (board[i][j] == word[pos] && pos == word.size() - 1)
            return true;
        board[i][j] = '\0';
        bool res = dfs(board, word, pos + 1, i - 1, j) || dfs(board, word, pos + 1, i, j - 1) || dfs(board, word, pos + 1, i + 1, j) || dfs(board, word, pos + 1, i, j + 1);
        board[i][j] = word[pos];
        return res;
    }
};

/*两棵二叉搜索树中的所有元素*/
class Solution
{
public:
    vector<int> getAllElements(TreeNode *root1, TreeNode *root2)
    {
        vector<int> ans;
        dfs(root1, ans);
        dfs(root2, ans);
        insertSort(ans);
        return ans;
    }

private:
    void dfs(TreeNode *root, vector<int> &arr)
    {
        if (root == nullptr)
            return;
        std::stack<TreeNode *> nodeStack;
        nodeStack.push(root);
        while (!nodeStack.empty())
        {
            TreeNode *node = nodeStack.top();
            nodeStack.pop();
            arr.push_back(node->val);
            if (node->right != nullptr)
                nodeStack.push(node->right);
            if (node->left != nullptr)
                nodeStack.push(node->left);
        }
    }
    void insertSort(vector<int> &arr)
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

/*机器人的运动范围(回溯)*/
class Solution
{
public:
    int movingCount(int m, int n, int k)
    {
        if (k <= 0)
            return 0;
        count = 1;
        vector<vector<bool>> flag(m, vector<bool>(n, true));
        dfs(0, 0, m, n, k, flag);
        return count;
    }

private:
    int count;
    void dfs(int i, int j, int &m, int &n, int &k, vector<vector<bool>> &flag)
    {
        if (i < 0 || i >= m || j < 0 || j >= n || flag[i][j] || GetSum(i, j) > k)
            return;
        else if (GetSum(i, j) <= k)
            count++;
        flag[i][j] = true;
        dfs(i - 1, j, m, n, k, flag);
        dfs(i + 1, j, m, n, k, flag);
        dfs(i, j - 1, m, n, k, flag);
        dfs(i, j + 1, m, n, k, flag);
        /*回溯的时候不能把flag复位，因为题目是计算格子数，而不是计算路径数*/
    }
    int GetSum(int i, int j)
    {
        int sum = 0;
        while (i != 0)
        {
            sum += i % 10;
            i /= 10;
        }
        while (j != 0)
        {
            sum += j % 10;
            j /= 10;
        }
        return sum;
    }
};

/*矩阵中的幸运数*/
class Solution
{
public:
    vector<int> luckyNumbers(vector<vector<int>> &matrix)
    {
        vector<int> rowMinlist;
        vector<int> colMaxlist;
        /*找每一行的最小元素*/
        for (int i = 0; i < matrix.size(); i++)
        {
            int min = matrix[i][0];
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (matrix[i][j] < min)
                    min = matrix[i][j];
            }
            rowMinlist.push_back(min);
        }
        /*找每一列的最大元素*/
        for (int i = 0; i < matrix[0].size(); i++)
        {
            int max = matrix[0][i];
            for (int j = 0; j < matrix.size(); j++)
            {
                if (matrix[j][i] > max)
                    max = matrix[j][i];
            }
            colMaxlist.push_back(max);
        }
        /*找公共元素*/
        vector<int> ans;
        for (int i : rowMinlist)
        {
            for (int j : colMaxlist)
            {
                if (i == j)
                    ans.push_back(i);
            }
        }
        return ans;
    }
};

/*单词搜索*/
class Solution
{
public:
    bool exist(vector<vector<char>> &board, string word)
    {
        /*dfs+剪枝*/
        rows = board.size();
        cols = board[0].size();
        /*每个格子都做一次起点开启dfs*/
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }

private:
    int rows, cols;
    bool dfs(vector<vector<char>> &board, string &word, int i, int j, int k)
    {
        /* 剪枝 */
        if (i >= rows || j >= cols || i < 0 || j < 0 || board[i][j] != word[k])//这里k不会越界
            return false;
        if (board[i][j] == word[k] && k == word.size() - 1)
            return true;
        board[i][j] = '\0';
        bool res = dfs(board, word, i - 1, j, k + 1) || dfs(board, word, i + 1, j, k + 1) ||
                   dfs(board, word, i, j - 1, k + 1) || dfs(board, word, i, j + 1, k + 1);
        board[i][j] = word[k];//没有被剪掉就说明 board[i][j] == word[k]
        return res;
    }
};

/*全排列*/
class Solution
{
public:
    vector<string> permutation(string s)
    {
        dfs(s, 0);
        return ans;
    }

private:
    vector<string> ans;
    void dfs(string &s, int index)
    {
        if (index == s.size() - 1)
        {
            ans.push_back(s);
            return;
        }
        std::set<char> set;
        for (int i = index; i < s.size(); i++)
        {
            if (set.find(s[i]) != set.end()) //剪枝
                continue;
            set.insert(s[i]);          //此位次字符已经使用过了
            std::swap(s[i], s[index]); //交换位
            dfs(s, index + 1);         //开启固定第 x + 1 位字符
            std::swap(s[i], s[index]); //复位
        }
    }
};

/*实现strStr()函数*/
class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        if (haystack.empty() || needle.empty() || haystack.size() < needle.size())
            return 0;
        int first = 0, second;
        while (first < haystack.size())
        {
            second = 0;
            if (haystack[first] == needle[second])
            {
                /*进入判断*/
                for (int i = first; i < haystack.size(); i++)
                {
                    if (haystack[i] == needle[second])
                    {
                        if (second != needle.size() - 1)
                        {
                            second++;
                        }
                        else
                            return first;
                    }
                    else
                        break;
                }
            }
            first++;
        }
        return -1;
    }
};

/*回文数*/
class Solution
{
public:
    bool isPalindrome(string s)
    {
        string sData = "";
        for (char r : s)
        {
            if ((r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z') || (r >= '0' && r <= '9'))
            {
                if (std::isupper(r))
                    r = std::tolower(r);
                sData += r;
            }
        }
        if (sData.size() == 2)
            return sData[0] == sData[1] || sData[0] == sData[1] - 32;
        int left = 0, right = sData.size() - 1;
        while (left < right)
        {
            if (sData[left] != sData[right] && sData[left] != sData[right] - 32)
                return false;
            left++;
            right--;
        }
        return true;
    }
};


