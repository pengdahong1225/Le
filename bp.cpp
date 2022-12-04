#include "source.h"
class Solution
{
public:
    /*动态规划*/
    int fib(int n)
    {
        /*底到顶*/
        int a = 0, b = 1, temp;
        if (n == 0)
            return a;
        else if (n == 1)
            return b;
        for (int i = 2; i <= n; i++)
        {
            temp = a;
            a = b;
            b = (b + temp) % 1000000007;
        }
        return b;
    }
    int translateNum(int num)
    {
        /*计数类的动态规划*/
        std::string str = std::to_string(num);
        if (str.size() < 2)
            return 1;
        /*dp[i]代表以i位为结尾的数字的翻译方案数量。*/
        std::vector<int> dp(str.size() + 1);
        /*至少有一种翻译方式*/
        dp[0] = dp[1] = 1;
        std::string temp;
        for (int i = 2; i <= str.size(); ++i)
        {
            temp = str.substr(i - 2, 2);
            if (temp.compare("10") >= 0 && temp.compare("25") <= 0)
            {
                dp[i] = dp[i - 1] + dp[i - 2];
            }
            else
            {
                dp[i] = dp[i - 1];
            }
        }
        return dp[str.size()];
    }
    int coinChange(std::vector<int> &coin_list, int amount)
    {
        std::vector<int> dp(amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i)
        { //用于遍历dp
            dp[i] = INT_MAX;
            for (int j = 0; j < coin_list.size(); ++j)
            { //遍历硬币列表2,5,7
                if (i >= coin_list[j] && dp[i - coin_list[j]] != INT_MAX)
                { // INT_MAX+1会溢出
                    dp[i] = std::min(dp[i - coin_list[j]] + 1, dp[i]);
                }
            }
        }
        if (dp[amount == INT_MAX])
        {
            return -1;
        }
        else
        {
            return dp[amount];
        }
    }
    int numWays(int n)
    {
        if (n < 2)
            return 1;
        else if (n == 2)
            return 2;
        std::vector<int> dp(n + 1); // dp[i]代表第i级台阶有dp[i]中跳法
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; ++i)
        {
            dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
        }
        return dp[n];
    }
    int fib2(int n)
    {
        /*动态规划法斐波那契*/
        std::vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;
        for (int i = 3; i <= n; ++i)
        {
            dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
        }
        return dp[n];
    }
    int maxSubArray(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        int res = nums[0]; //滚动变量
        for (int i = 1; i < nums.size(); ++i)
        {
            nums[i] = std::max(nums[i - 1] + nums[i], nums[i]);
            res = std::max(nums[i], res);
        }
        return res;
    }
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;
        else if (n == 1 || n == 2)
            return 1;
        std::vector<int> dp(n + 1);
        dp[0] = 0, dp[1] = dp[2] = 1;
        for (int i = 3; i <= n; ++i)
        {
            dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        }
        return dp[n];
    }
    int uniquePaths(int m, int n)
    {
        /*计数类的动态规划*/
        if (m < 1 || n < 1)
            return 0;
        /*dp[i][j]代表走到第i行第j列有多少种走法*/
        int **dp = new int *[m];
        for (int i = 0; i < m; ++i)
        {
            dp[i] = new int[n];
        }
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        int res = dp[m - 1][n - 1];
        for (int i = 0; i < m; ++i)
            delete[] dp[i];
        return res;
    }
    int JumpGame(std::vector<int> &nums)
    {
        /*求存在性的动态规划*/
        int len = nums.size();
        std::vector<bool> dp(len);
        dp[0] = true; // initialization
        for (int j = 1; j < len; ++j)
        {
            dp[j] = false;
            for (int i = 0; i < j; ++i)
            {
                if (dp[i] && i + nums[j] >= j)
                {
                    dp[j] = true;
                    break;
                }
            }
        }
        return dp[len - 1];
    }
    int maxValue(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        if (m == 0 || n == 0)
            return 0;
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for (int j = 1; j < n; j++)
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        for (int i = 1; i < m; i++)
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
                dp[i][j] = std::max(dp[i - 1][j] + grid[i][j], dp[i][j - 1] + grid[i][j]);
        }
        return dp[m - 1][n - 1];
    }

    int reverse(int x)
    {
        bool flag = false;
        if (x < 0)
        {
            x *= -1;
            flag = true;
        }
        std::string str = std::to_string(x);
        for (int i = 0; i < str.size() / 2; i++)
        {
            char temp = str[i];
            str[i] = str[str.size() - i - 1];
            str[str.size() - i - 1] = temp;
        }
        x = std::atoi(str.c_str());
        if (flag)
            x *= -1;
        return x;
    }
    bool isPalindrome(string s)
    {
        /*双指针：一个向前走，一个向后退*/
        int left = 0, right = s.size() - 1;
        while (true)
        {
            if (left == right)
                break;
            if (('a' > s[left] || s[left] > 'z') && ('A' > s[left] || s[left] > 'Z') && ('0' > s[left] || s[left] > '9'))
            {
                left++;
                continue;
            }
            if (('a' > s[right] || s[right] > 'z') && ('A' > s[right] || s[right] > 'Z') && ('0' > s[right] || s[right] > '9'))
            {
                right--;
                continue;
            }
            if (!(s[left] == s[right] || s[left] == s[right] - 32 || s[left] == s[right] + 32))
                return false;
            if (++left == right)
                break;
            right--;
        }
        return true;
    }
    vector<int> exchange(vector<int> &nums)
    {
        if (nums.size() < 2)
            return nums;
        int left = 0, right = nums.size() - 1;
        int temp = 0;
        while (left < right)
        {
            /*左偶右奇*/
            if ((nums[left] % 2 == 0) && (nums[right] % 2 != 0))
            {
                cout << "1" << endl;
                temp = nums[left];
                nums[left] = nums[right];
                nums[right] = temp;
            }
            /*左奇右奇*/
            else if (nums[left] % 2 != 0 && nums[right] % 2 != 0)
            {
                cout << "2" << endl;
                left++;
                continue;
            }
            /*左偶右偶*/
            else if (nums[left] % 2 == 0 && nums[right] % 2 == 0)
            {
                cout << "3" << endl;
                right--;
                continue;
            }
            /*左奇右偶*/
            left++;
            right--;
            cout << "ok" << endl;
        }
        return nums;
    }
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode *first = l1, *second = l2;
        ListNode *temp = nullptr, *pre = nullptr;
        while (true)
        {
            if (first->val <= second->val && first->next->val > second->val)
            {
                temp = second->next;
                second->next = first->next;
                first->next = second;
                second = temp;
            }
            pre = first;
            first = first->next;
            if (first == nullptr)
            {
                pre->next = second;
                break;
            }
            if (second == nullptr)
                break;
        }
        return l1;
    }
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int len = nums.size();
        std::vector<int> ans;
        if (len == 0)
            return ans;
        vector<int>::iterator left = nums.begin();
        vector<int>::iterator right = left + k;
        while (right != nums.end())
        {
            auto t1 = left;
            auto t2 = right;
            while (t1 < t2)
            {
                cout << *t1 << " ";
                t1++;
            }
            cout << endl;
            cout << "max=" << *std::max_element(left, right) << endl;
            ans.push_back(*std::max_element(left, right));
            left++;
            right++;
        }
        return ans;
    }
};
