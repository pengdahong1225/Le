#include "source.h"

/* 二叉树遍历 */
class Solution
{
public:
    /*前序遍历递归法*/
    vector<int> preorderTraversal(TreeNode *root)
    {
        std::vector<int> num;
        if (root == nullptr)
            return num;
        preOrder(root, num);
        return num;
    }
    /*前序遍历迭代法*/
    vector<int> preorderTraversal2(TreeNode *root)
    {
        std::vector<int> num;
        if (root != nullptr)
        {
            std::stack<TreeNode *> NodeStack;
            TreeNode *node = root;
            NodeStack.push(node);
            while (!NodeStack.empty())
            {
                node = NodeStack.top();
                NodeStack.pop();
                num.push_back(node->val);
                /*先压右子树，再压左子树*/
                if (node->right != nullptr)
                    NodeStack.push(node->right);
                if (node->left != nullptr)
                    NodeStack.push(node->left);
            }
        }
        return num;
    }
    /*中序遍历递归法*/
    vector<int> inorderTraversal(TreeNode *root)
    {
        std::vector<int> num;
        if (root == nullptr)
            return num;
        inOrder(root, num);
        return num;
    }
    /*中序遍历迭代法*/
    vector<int> inorderTraversal2(TreeNode *root)
    {
        std::vector<int> num;
        if (root != nullptr)
        {
            std::stack<TreeNode *> NodeStack;
            TreeNode *node = root;
            /* 栈不为空或者树还没有遍历完 */
            while (!NodeStack.empty() || node != nullptr)
            { 
                if (node != nullptr)
                {
                    NodeStack.push(node);
                    node = node->left;
                }
                else
                {
                    node = NodeStack.top();
                    NodeStack.pop();
                    num.push_back(node->val);
                    /*处理右节点*/
                    node = node->right;
                }
            }
        }
        return num;
    }
    /*后序遍历递归*/
    vector<int> postorderTraversal(TreeNode *root)
    {
        std::vector<int> num;
        if (root == nullptr)
            return num;
        postOrder(root, num);
        return num;
    }
    /*后序遍历迭代*/
    vector<int> postorderTraversal2(TreeNode *root)
    {
        std::vector<int> num;
        if (root != nullptr)
        {
            std::stack<TreeNode *> NodeStack;
            TreeNode *node = root;
            NodeStack.push(node);
            while (!NodeStack.empty())
            {
                node = NodeStack.top();
                NodeStack.pop();
                num.push_back(node->val);
                /*先压左节点*/
                if (node->left != nullptr)
                    NodeStack.push(node->left);
                /*再压右节点*/
                if (node->right != nullptr)
                    NodeStack.push(node->right);
            }
            std::reverse(num.begin(), num.end());
        }
        return num;
    }
    /*层序遍历*/
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        std::vector<vector<int>> result;
        if (root == nullptr)
            return result;
        std::deque<TreeNode *> nodeQue;
        nodeQue.push_back(root);//根节点入队
        while (!nodeQue.empty())
        {
            std::vector<int> temp;
            int len = nodeQue.size(); /*必须在for循环外边获取len，因为for里面会对队列加入新的节点，改变len*/
            for (int i = 0; i < len; i++)
            {
                /*取出元素，放入列表*/
                TreeNode *node = nodeQue.front();
                nodeQue.pop_front();
                temp.push_back(node->val);
                /*处理下一层节点*/
                if (node->left != nullptr)
                    nodeQue.push_back(node->left);
                if (node->right != nullptr)
                    nodeQue.push_back(node->right);
            }
            /*每一层结束之后把上一层的列表加入返回列表中*/
            result.push_back(temp);
        }
        return result;
    }
private:
    void preOrder(TreeNode *node, std::vector<int> &num)
    {
        if (node == nullptr)
            return;
        /*插入根，然后分别深入左和右*/
        num.push_back(node->val);
        preOrder(node->left, num);
        preOrder(node->right, num);
    }
    void inOrder(TreeNode *node, std::vector<int> &num)
    {
        if (node == nullptr)
            return;
        inOrder(node->left, num);
        num.push_back(node->val);
        inOrder(node->right, num);
    }
    void postOrder(TreeNode *node, std::vector<int> &num)
    {
        if (node == nullptr)
            return;
        postOrder(node->left, num);
        postOrder(node->right, num);
        num.push_back(node->val);
    }
};

/* 二叉树编码与解码 */
class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        /* 空节点用‘#’代替，节点之间用‘,’分隔 */
        string ans = "";
        if (root == nullptr)
            return "#";
        /* bfs */
        std::queue<TreeNode *> nodeQue;
        nodeQue.push(root);
        while (!nodeQue.empty())
        {
            int len = nodeQue.size();
            for (int i = 0; i < len; i++)
            {
                TreeNode *node = nodeQue.front();
                nodeQue.pop();
                if (node == nullptr)
                {
                    ans += "#,";
                    continue;
                }
                ans += std::to_string(node->val);
                ans += ",";
                /* 下一层入队 */
                nodeQue.push(node->left);
                nodeQue.push(node->right);
            }
        }
        return ans;
    }
    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        if (data == "#")
            return nullptr;
        /* 去除‘,’ 由于二叉树中可能有节点数值大于9或为负数，所以不能直接遍历string*/
        vector<string> realData;
        string temp = "";
        for (auto i : data)
        {
            if (i == ',')
            {
                realData.push_back(temp);
                temp.clear();
                temp = "";
            }
            else
                temp += i;
        }
        /* deserialize */
        TreeNode *root = new TreeNode(std::atoi(realData[0].c_str()));
        std::queue<TreeNode *> nodeQue;
        nodeQue.push(root);
        for (int i = 1; i < realData.size(); i++)
        {
            /* 每个节点都做一次父节点，构造局部二叉树 */
            TreeNode *parent = nodeQue.front();
            nodeQue.pop();
            /* 每次取两个 */
            if (realData[i] != "#")
            {
                TreeNode *left = new TreeNode(std::atoi(realData[i].c_str()));
                parent->left = left;
                nodeQue.push(left);
            }
            if (realData[++i] != "#")
            {
                TreeNode *right = new TreeNode(std::atoi(realData[i].c_str()));
                parent->right = right;
                nodeQue.push(right);
            }
        }
        return root;
    }
};

/* 由遍历序列构造二叉树 */
class Solution
{
public:
    /* 中序+前序 */
    TreeNode* buildTree_1(vector<int>& preorder, vector<int>& inorder) {
        vector<int> leftorder,rightorder;
        int R = preorder[0];
        int i;
        for(i=0;i<inorder.size();i++)
        {
            if(inorder[i]==R)
                break;
            leftorder.push_back(inorder[i]);
        }
        for(i+=1;i<inorder.size();i++)
        {
            rightorder.push_back(inorder[i]);
        }
    }
    
    /* 中序+后序 */
    TreeNode* buildTree_2(vector<int>& preorder, vector<int>& postorder) {
        
    }
};

/* 线索二叉树 */
class Solution
{
public:
    /*先序线索*/
    void CreatePreThreadTree(ThreadTreeNode* root)
    {
        if(root==nullptr)
            return;
        pre = nullptr;
        preOrderThreadTree(root);
        if(pre->right == nullptr)
            pre->rtag = 1;//将最后一个节点设为线索
    }
    void preOrderThreadTree(ThreadTreeNode* root)
    {
        if(root==nullptr)
            return;
        visit(root);
        if(root->ltag == 0)//左节点不是前驱线索(避免‘绕圈’)
            preOrderThreadTree(root->left);
        preOrderThreadTree(root->right);
    }
    /*中序线索*/
    void CreateInThreadTree(ThreadTreeNode* root)
    {
        if(root==nullptr)
            return;
        pre = nullptr;
        inOrderThreadTree(root);
        if(pre->right == nullptr)
            pre->rtag = 1;//将最后一个节点设为线索
    }
    void inOrderThreadTree(ThreadTreeNode* root)
    {
        if(root == nullptr)
            return;
        inOrderThreadTree(root->left);
        visit(root);
        inOrderThreadTree(root->right);
    }
    /*后续线索*/
    void CreatePostThreadTree(ThreadTreeNode* root)
    {
        if(root==nullptr)
            return;
        pre = nullptr;
        postOrderThreadTree(root);
        if(pre->right == nullptr)
            pre->rtag = 1;//将最后一个节点设为线索
    }
    void postOrderThreadTree(ThreadTreeNode* root)
    {
        if(root==nullptr)
            return;
        pre = nullptr;
        postOrderThreadTree(root->left);
        postOrderThreadTree(root->right);
        visit(root);
    }

    /**中序**/
    /*找到以中序遍历中第一个被遍历的节点*/
    ThreadTreeNode* FirstNode(ThreadTreeNode* root)
    {
        while(root->ltag == 0)
            root = root->left;
        return root;
    }
    /*找到node节点的中序后继节点*/
    ThreadTreeNode* NextNode(ThreadTreeNode* node)
    {
        if(node->rtag == 0)
            return FirstNode(node); //node的右子树中最先被中序遍历的节点(最左下节点)
        return node->right;
    }
    /*利用中序线索二叉树进行中序遍历  非递归*/
    void Inorder(ThreadTreeNode* root,vector<int>& nums)
    {
        for(ThreadTreeNode* node=FirstNode(root);node!=nullptr;node=NextNode(node))
            nums.push_back(node->val);
    }
    /*找到以中序遍历中最后一个被遍历的节点*/
    ThreadTreeNode* LastNode(ThreadTreeNode* root)
    {
        while(root->rtag == 0)
            root = root->right;
        return root;
    }
    /*找到node节点的中序前驱节点*/
    ThreadTreeNode* PreNode(ThreadTreeNode* node)
    {
        if(node->ltag == 0)
            return LastNode(node->left); //node的左子树种最后被中序遍历的节点(最右下节点)
        return node->left;
    }
    /*利用中序线索二叉树进行逆中序遍历  非递归*/
    void RevInorder(ThreadTreeNode* root,vector<int>& nums)
    {
        for(ThreadTreeNode* node=LastNode(root);node!=nullptr;node=PreNode(node))
            nums.push_back(node->val);
    }
    
    /**先序和后序**/
    /*找到node节点的先序后继节点*/
    ThreadTreeNode* NextNode(ThreadTreeNode* root)
    {
        if(root->ltag == 0)
            return root->left;
        else
            return root->right;
    }
    /*找到node节点的先序前继节点和后序后继节点都要基于三叉链表*/
private:
    /*添加线索*/
    void visit(ThreadTreeNode* node)
    {
        if(node->left == nullptr)
        {
            node->left = pre;
            node->ltag = 1;
        }
        if(pre!=nullptr && pre->right==nullptr)
        {
            pre->right = node;
            pre->right->rtag = 1;
        }
        pre = node;
    }
    ThreadTreeNode* pre=nullptr;
};

