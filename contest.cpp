#include "source.h"
class Solution
{
public:
    vector<string> cellsInRange(string s)
    {
        vector<string> ans;
        int colNum = s[3] - s[0];
        int rowNum = s[4] - s[1];
        for (int col = 0; col <= colNum; col++)
        {
            for (int row = 0; row <= rowNum; row++)
            {
                string temp = "";
                temp += (s[0] + col);
                temp += (s[1] + row);
                ans.push_back(temp);
            }
        }
        return ans;
    }
    long long minimalKSum(vector<int> &nums, int k)
    {
        std::sort(nums.begin(), nums.end());
        int len = nums.size();
        long long ans = 0;
        int i, j = 0;
        for (i = 1; i <= k; i++)
        {
            if (nums[j] != i)
            {
                nums.push_back(i);
                i++;
            }
        }
        return ans;
    }
    bool search(vector<int> &nums, int target)
    {
        int len = nums.size();
        int i = 0, j = len - 1;
        /*找到旋转点*/
        while (i <= j)
        {
            int mid = (i + j) / 2;
            if (nums[mid] > nums[j])
                i = mid + 1;
            else if (nums[mid] < nums[j])
                j = mid;
            else
                j--;
        }
        int pos = i;
        cout << "pos=" << pos << endl;
        /*判断target在左数组还是右数组*/
        if (target >= nums[0] && target <= nums[pos - 1])
        {
            cout << "if" << endl;
            i = 0, j = pos - 1;
            while (i <= j)
            {
                int mid = (i + j) / 2;
                if (nums[mid] > target)
                    i = mid + 1;
                else if (nums[mid] < target)
                    j = mid - 1;
                else
                    return true;
            }
        }
        else if (target >= nums[pos] && target <= nums[len - 1])
        {
            cout << "else if" << endl;
            i = pos, j = len - 1;
            while (i <= j)
            {
                int mid = (i + j) / 2;
                if (nums[mid] > target)
                    j = mid - 1;
                else if (nums[mid] < target)
                    i = mid + 1;
                else
                    return true;
            }
        }
        return false;
    }

    int movingCount(int m, int n, int k)
    {
        count = 0;
        vector<vector<bool>> flag(m, vector<bool>(n, false));
        dfs(0, 0, m, n, k, flag);
        return count;
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> ans;
        if (!root)
            return ans;
        stack<TreeNode *> nodeStack;
        while (!nodeStack.empty() || root)
        {
            while (root)
            {
                nodeStack.push(root);
                root = root->left;
            }
            if (!nodeStack.empty())
            {
                root = nodeStack.top();
                nodeStack.pop();
                ans.push_back(root->val);
                root = root->right;
            }
        }
        return ans;
    }

private:
    int count;
    void dfs(int i, int j, int &m, int &n, int &k, vector<vector<bool>> &flag)
    {
        if (i < 0 || i >= m || j < 0 || j >= n || flag[i][j] || GetSum(i, j) > k)
            return;
        else if (GetSum(i, j) <= k)
        {
            count++;
            cout << "(" << i << "," << j << "):";
            cout << count << endl;
        }
        flag[i][j] = true;
        dfs(i - 1, j, m, n, k, flag);
        dfs(i + 1, j, m, n, k, flag);
        dfs(i, j - 1, m, n, k, flag);
        dfs(i, j + 1, m, n, k, flag);
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
        // cout << "sum="<<sum << endl;
        return sum;
    }
};
