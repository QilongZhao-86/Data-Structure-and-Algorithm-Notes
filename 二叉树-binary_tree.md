# 二叉树
## 遍历
### 前序遍历（根-左-右）
#### 方法一：递归
思路与算法

首先我们需要了解什么是二叉树的前序遍历：按照访问根节点——左子树——右子树的方式遍历这棵树，而在访问左子树或者右子树的时候，我们按照同样的方式遍历，直到遍历完整棵树。因此整个遍历过程天然具有递归的性质，我们可以直接用递归函数来模拟这一过程。

定义 preorder(root) 表示当前遍历到 root 节点的答案。按照定义，我们只要首先将 root 节点的值加入答案，然后递归调用 preorder(root.left) 来遍历 root 节点的左子树，最后递归调用 preorder(root.right) 来遍历 root 节点的右子树即可，递归终止的条件为碰到空节点。

代码
```cpp
class Solution {
public:
    void preorder(TreeNode *root, vector<int> &res) {
        if (root == nullptr) {
            return;
        }
        res.push_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }

    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> res;
        preorder(root, res);
        return res;
    }
};
```
复杂度分析

时间复杂度：O(n)，其中 n 是二叉树的节点数。每一个节点恰好被遍历一次。

空间复杂度：O(n)，为递归过程中栈的开销，平均情况下为 O(logn)，最坏情况下树呈现链状，为 O(n)。

#### 方法二：迭代
思路与算法

我们也可以用迭代的方式实现方法一的递归函数，两种方式是等价的，区别在于递归的时候隐式地维护了一个栈，而我们在迭代的时候需要显式地将这个栈模拟出来，其余的实现与细节都相同，具体可以参考下面的代码.
```cpp
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }

        stack<TreeNode*> stk;
        TreeNode* node = root;
        while (!stk.empty() || node != nullptr) {
            while (node != nullptr) {
                res.emplace_back(node->val);
                stk.emplace(node);
                node = node->left;
            }
            node = stk.top();
            stk.pop();
            node = node->right;
        }
        return res;
    }
};
```
复杂度分析

时间复杂度：O(n)，其中 n 是二叉树的节点数。每一个节点恰好被遍历一次。

空间复杂度：O(n)，为迭代过程中显式栈的开销，平均情况下为 O(logn)，最坏情况下树呈现链状，为 O(n)。

#### 方法三：Morris 遍历
思路与算法

有一种巧妙的方法可以在线性时间内，只占用常数空间来实现前序遍历。这种方法由 J. H. Morris 在 1979 年的论文「Traversing Binary Trees Simply and Cheaply」中首次提出，因此被称为 Morris 遍历。

Morris 遍历的核心思想是利用树的大量空闲指针，实现空间开销的极限缩减。其前序遍历规则总结如下：

新建临时节点，令该节点为 root；

如果当前节点的左子节点为空，将当前节点加入答案，并遍历当前节点的右子节点；

如果当前节点的左子节点不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点：

如果前驱节点的右子节点为空，将前驱节点的右子节点设置为当前节点。然后将当前节点加入答案，并将前驱节点的右子节点更新为当前节点。当前节点更新为当前节点的左子节点。

如果前驱节点的右子节点为当前节点，将它的右子节点重新设为空。当前节点更新为当前节点的右子节点。

重复步骤 2 和步骤 3，直到遍历结束。

这样我们利用 Morris 遍历的方法，前序遍历该二叉树，即可实现线性时间与常数空间的遍历。

代码

```cpp
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }

        TreeNode *p1 = root, *p2 = nullptr;

        while (p1 != nullptr) {
            p2 = p1->left;
            if (p2 != nullptr) {
                while (p2->right != nullptr && p2->right != p1) {
                    p2 = p2->right;
                }
                if (p2->right == nullptr) {
                    res.emplace_back(p1->val);
                    p2->right = p1;
                    p1 = p1->left;
                    continue;
                } else {
                    p2->right = nullptr;
                }
            } else {
                res.emplace_back(p1->val);
            }
            p1 = p1->right;
        }
        return res;
    }
};
```
复杂度分析

时间复杂度：O(n)，其中 n 是二叉树的节点数。没有左子树的节点只被访问一次，有左子树的节点被访问两次。

空间复杂度：O(1)。只操作已经存在的指针（树的空闲指针），因此只需要常数的额外空间。
### 中序遍历（左-根-右）
#### 方法一：递归
思路与算法
首先我们需要了解什么是二叉树的中序遍历：按照访问左子树——根节点——右子树的方式遍历这棵树，而在访问左子树或者右子树的时候，我们按照同样的方式遍历，直到遍历完整棵树。因此整个遍历过程天然具有递归的性质，我们可以直接用递归函数来模拟这一过程。
定义 inorder(root) 表示当前遍历到 root 节点的答案。按照定义，我们只要首先递归调用 inorder(root.left) 来遍历 root 节点的左子树，然后将 root 节点的值加入答案，最后递归调用 inorder(root.right) 来遍历 root 节点的右子树即可，递归终止的条件为碰到空节点。
代码
```cpp
class Solution {
public:
    void inorder(TreeNode *root, vector<int> &res) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。每一个节点恰好被遍历一次。
空间复杂度：O(n)，为递归过程中栈的开销，平均情况下为 O(logn)，最坏情况下树呈现链状，为 O(n)。
#### 方法二：迭代
思路与算法
我们也可以用迭代的方式实现方法一的递归函数，两种方式是等价的，区别在于递归的时候隐式地维护了一个栈，而我们在迭代的时候需要显式地将这个栈模拟出来，其余的实现与细节都相同，具体可以参考下面的代码.
```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }

        stack<TreeNode*> stk;
        TreeNode* node = root;
        while (!stk.empty() || node != nullptr) {
            while (node != nullptr) {
                stk.emplace(node);
                node = node->left;
            }
            node = stk.top();
            stk.pop();
            res.emplace_back(node->val);
            node = node->right;
        }
        return res;
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。每一个节点恰好被遍历一次。
空间复杂度：O(n)，为迭代过程中显式栈的开销，平均情况下为 O(logn)，最坏情况下树呈现链状，为 O(n)。
#### 方法三：Morris 遍历
思路与算法
有一种巧妙的方法可以在线性时间内，只占用常数空间来实现中序遍历。这种方法由 J. H. Morris 在 1979 年的论文「Traversing Binary Trees Simply and Cheaply」中首次提出，因此被称为 Morris 遍历。
Morris 遍历的核心思想是利用树的大量空闲指针，实现空间开销的极限缩减。其中序遍历规则总结如下：
新建临时节点，令该节点为 root；
如果当前节点的左子节点为空，将当前节点加入答案，并遍历当前节点的右子节点；
如果当前节点的左子节点不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点：
如果前驱节点的右子节点为空，将前驱节点的右子节点设置为当前节点。当前节点更新为当前节点的左子节点。
如果前驱节点的右子节点为当前节点，将它的右子节点重新设为空。将当前节点加入答案，当前节点更新为当前节点的右子节点。
重复步骤 2 和步骤 3，直到遍历结束。
这样我们利用 Morris 遍历的方法，中序遍历该二叉树，即可实现线性时间与常数空间的遍历。
代码
```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }

        TreeNode *p1 = root, *p2 = nullptr;

        while (p1 != nullptr) {
            p2 = p1->left;
            if (p2 != nullptr) {
                while (p2->right != nullptr && p2->right != p1) {
                    p2 = p2->right;
                }
                if (p2->right == nullptr) {
                    p2->right = p1;
                    p1 = p1->left;
                    continue;
                } else {
                    p2->right = nullptr;
                }
            }
            res.emplace_back(p1->val);
            p1 = p1->right;
        }
        return res;
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。没有左子树的节点只被访问一次，有左子树的节点被访问两次。
空间复杂度：O(1)。只操作已经存在的指针（树的空闲指针），因此只需要常数的额外空间。

### 后序遍历（左-右-根）
#### 方法一：递归
思路与算法
首先我们需要了解什么是二叉树的后序遍历：按照访问左子树——右子树——根节点的方式遍历这棵树，而在访问左子树或者右子树的时候，我们按照同样的方式遍历，直到遍历完整棵树。因此整个遍历过程天然具有递归的性质，我们可以直接用递归函数来模拟这一过程。
定义 postorder(root) 表示当前遍历到 root 节点的答案。按照
定义，我们只要首先递归调用 postorder(root.left) 来遍历 root 节点的左子树，然后递归调用 postorder(root.right) 来遍历 root 节点的右子树，最后将 root 节点的值加入答案即可，递归终止的条件为碰到空节点。
代码
```cpp
class Solution {
public:
    void postorder(TreeNode *root, vector<int> &res) {
        if (root == nullptr) {
            return;
        }
        postorder(root->left, res);
        postorder(root->right, res);
        res.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> res;
        postorder(root, res);
        return res;
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。每一个节点恰好被遍历一次。
空间复杂度：O(n)，为递归过程中栈的开销，平均情况下为 O(logn)，最坏情况下树呈现链状，为 O(n)。
#### 方法二：迭代
思路与算法
我们也可以用迭代的方式实现方法一的递归函数，两种方式是等价的，区别在于递归的时候隐式地维护了一个栈，而我们在迭代的时候需要显式地将这个栈模拟出来，其余的实现与细节都相同，具体可以参考下面的代码.
```cpp
class Solution {
public:

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }

        stack<TreeNode*> stk;
        TreeNode* node = root;
        TreeNode* prev = nullptr;

        while (!stk.empty() || node != nullptr) {
            while (node != nullptr) {
                stk.emplace(node);
                node = node->left;
            }
            node = stk.top();
            if (node->right == nullptr || node->right == prev) {
                res.emplace_back(node->val);
                stk.pop();
                prev = node;
                node = nullptr;
            } else {
                node = node->right;
            }
        }
        return res;
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。每一个节点恰好被遍历一次。
空间复杂度：O(n)，为迭代过程中显式栈的开销，平均情况下为 O(logn)，最坏情况下树呈现链状，为 O(n)。
#### 方法三：Morris 遍历
思路与算法
有一种巧妙的方法可以在线性时间内，只占用常数空间来实现后序遍历。这种方法由 J. H. Morris 在 1979 年的论文「Traversing Binary Trees Simply and Cheaply」中首次提出，因此被称为 Morris 遍历。
Morris 遍历的核心思想是利用树的大量空闲指针，实现空间开销的极限缩减。其后序遍历规则总结如下：
新建临时节点，令该节点为 root；
如果当前节点的左子节点为空，遍历当前节点的右子节点；
如果当前节点的左子节点不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点：
如果前驱节点的右子节点为空，将前驱节点的右子节点设置为当前节点。当前节点更新为当前节点的左子节点。
如果前驱节点的右子节点为当前节点，将它的右子节点重新设为空。然后按照从当前节点的左子节点到前驱节点的路径反向遍历该路径上的节点并加入答案。当前节点更新为当前节点的右子节点。
重复步骤 2 和步骤 3，直到遍历结束。
这样我们利用 Morris 遍历的方法，后序遍历该二叉树，即可实现线性时间与常数空间的遍历。
代码
```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }

        TreeNode *p1 = root, *p2 = nullptr;

        while (p1 != nullptr) {
            p2 = p1->left;
            if (p2 != nullptr) {
                while (p2->right != nullptr && p2->right != p1) {
                    p2 = p2->right;
                }
                if (p2->right == nullptr) {
                    p2->right = p1;
                    p1 = p1->left;
                    continue;
                } else {
                    p2->right = nullptr;
                    addPath(res, p1->left, p2);
                }
            }
            p1 = p1->right;
        }
        addPath(res, root, p2);
        return res;
    }

    void addPath(vector<int> &res, TreeNode *from, TreeNode *to) {
        reversePath(from, to);
        TreeNode *p = to;
        while (true) {
            res.emplace_back(p->val);
            if (p == from) {
                break;
            }
            p = p->right;
        }
        reversePath(to, from);
    }

    void reversePath(TreeNode *from, TreeNode *to) {
        if (from == to) {
            return;
        }
        TreeNode *x = from, *y = from->right, *z;
        while (true) {
            z = y->right;
            y->right = x;
            x = y;
            y = z;
            if (x == to) {
                break;
            }
        }
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。没有左子树的节点只被访问一次，有左子树的节点被访问两次。
空间复杂度：O(1)。只操作已经存在的指针（树的空闲指针），因此只需要常数的额外空间。

### 层序遍历
思路与算法
层序遍历又称广度优先遍历，是指从二叉树的根节点开始，逐层从左到右访问每一个节点，直到遍历完整棵树。我们可以利用队列这一数据结构来实现层序遍历，具体做法如下：
将根节点加入队列；
当队列不为空时，执行以下操作：
从队列中取出队首节点 node，并将 node 的值加入答案；
如果 node 的左子节点不为空，将左子节点加入队列；
如果 node 的右子节点不为空，将右子节点加入队列；
代码
```cpp
class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }

        queue<TreeNode*> q;
        q.emplace(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            res.emplace_back(node->val);
            if (node->left != nullptr) {
                q.emplace(node->left);
            }
            if (node->right != nullptr) {
                q.emplace(node->right);
            }
        }
        return res;
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。每一个节点恰好被遍历一次。
空间复杂度：O(n)，为队列的开销，最坏情况下队列中会存储 O(n) 个节点。
如果是按二维vector返回每一层的节点值，可以参考[102. 二叉树的层序遍历](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)。
写法如下：
```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr) {
            return res;
        }

        queue<TreeNode*> q;
        q.emplace(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                level.emplace_back(node->val);
                if (node->left != nullptr) {
                    q.emplace(node->left);
                }
                if (node->right != nullptr) {
                    q.emplace(node->right);
                }
            }
            res.emplace_back(level);
        }
        return res;
    }
};
``` 
## 搜索
### 深度优先搜索（DFS）
深度优先搜索（DFS）是一种用于遍历或搜索树或图的算法。它从根节点开始，沿着树的深度遍历尽可能深的节点，然后回溯。
在二叉树中，DFS 可以通过递归或栈来实现。以下是使用递归实现 DFS 的示例代码：
```cpp  
class Solution {
    void dfs(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        // 访问当前节点
        dfs(node->left);
        dfs(node->right);
    }
};
```
如果需要使用栈来实现 DFS，可以参考以下代码：
```cpp
class Solution {
    vector<int> dfs(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }

        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty()) {
            TreeNode* node = stk.top();
            stk.pop();
            result.push_back(node->val);
            if (node->right != nullptr) {
                stk.push(node->right);
            }
            if (node->left != nullptr) {
                stk.push(node->left);
            }
        }
        return result;
    }           
};
``` 
### 广度优先搜索（BFS）
广度优先搜索（BFS）是一种用于遍历或搜索树或图的算法。它从根节点开始，先访问所有同一层的节点，然后再访问下一层的节点。
在二叉树中，BFS 通常使用队列来实现。以下是使用队列实现 BFS 的示例代码：
```cpp
class Solution {
    vector<int> bfs(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            result.push_back(node->val);
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        return result;
    }           
};
```
## 二叉搜索树
二叉搜索树（Binary Search Tree，BST）是一种特殊的二叉树，其中每个节点的值都满足以下性质：
左子树上所有节点的值都小于根节点的值。
右子树上所有节点的值都大于根节点的值。
这种性质使得二叉搜索树在查找、插入和删除操作上具有较高的效率，平均时间复杂度为 O(log n)，但在最坏情况下（例如插入有序数据）可能退化为链表，时间复杂度为 O(n)。
### 查找
在二叉搜索树中查找一个值，可以利用其有序性质。以下是查找操作的示例代码：
```cpp
class Solution {
public:
    bool searchBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return false;
        }
        if (root->val == val) {
            return true;
        } else if (val < root->val) {
            return searchBST(root->left, val);
        } else {
            return searchBST(root->right, val);
        }
    }
};
```
### 插入
在二叉搜索树中插入一个值，同样可以利用其有序性质。以下是插入操作的示例代码：
```cpp
class Solution {
public:     
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }
        if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
        } else {
            root->right = insertIntoBST(root->right, val);
        }
        return root;
    }
};
```
### 删除
在二叉搜索树中删除一个值，需要考虑三种情况：删除的节点是叶子节点、删除的节点有一个子节点、删除的节点有两个子节点。以下是删除操作的示例代码：
```cpp
class Solution {
public:     
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                return root->right;
            } else if (root->right == nullptr) {
                return root->left;
            } else {
                TreeNode* minNode = findMin(root->right);
                root->val = minNode->val;
                root->right = deleteNode(root->right, minNode->val);
            }
        }
        return root;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};
```
## 平衡二叉树
平衡二叉树（Balanced Binary Tree）是一种特殊的二叉树，其中每个节点的左右子树高度差不超过 1。这种性质使得平衡二叉树在查找、插入和删除操作上具有较高的效率，平均时间复杂度为 O(log n)。
### 判断是否为平衡二叉树

判断一棵二叉树是否为平衡二叉树，可以通过递归计算每个节点的高度，并检查其左右子树的高度差是否超过 1。以下是判断操作的示例代码：
```cpp
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return checkHeight(root) != -1;
    }

    int checkHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = checkHeight(node->left);
        if (leftHeight == -1) {
            return -1;
        }
        int rightHeight = checkHeight(node->right);
        if (rightHeight == -1) {
            return -1;
        }
        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        return max(leftHeight, rightHeight) + 1;
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。每个
节点被访问一次。
空间复杂度：O(h)，其中 h 是二叉树的高度。为递归 过程中栈的开销，平均情况下为 O(log n)，最坏情况下树呈现链状，为 O(n)。
## 构建二叉树
### 从前序和中序遍历构建二叉树
根据二叉树的前序遍历和中序遍历结果，可以唯一确定一棵二叉树。前序遍历的第一个节点是根节点，在中序遍历中找到该节点的位置，左侧的节点构成左子树，右侧的节点构成右子树。然后递归地对左右子树进行同样的操作。
以下是从前序和中序遍历构建二叉树的示例代码：
```cpp
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

    TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
                    vector<int>& inorder, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) {
            return nullptr;
        }

        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);

        int inRootIndex = inStart;
        while (inRootIndex <= inEnd && inorder[inRootIndex] != rootVal) {
            inRootIndex++;
        }
        int leftTreeSize = inRootIndex - inStart;

        root->left = build(preorder, preStart + 1, preStart + leftTreeSize,
                           inorder, inStart, inRootIndex - 1);
        root->right = build(preorder, preStart + leftTreeSize + 1, preEnd,
                            inorder, inRootIndex + 1, inEnd);

        return root;
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。每个节点被访问一次。
空间复杂度：O(n)，为递归过程中栈的开销，平均情况下为 O(log n)，最坏情况下树呈现链状，为 O(n)。
### 从中序和后序遍历构建二叉树
根据二叉树的中序遍历和后序遍历结果，可以唯一确定一棵二叉树。后序遍历的最后一个节点是根节点，在中序遍历中找到该节点的位置，左侧的节点构成左子树，右侧的节点构成右子树。然后递归地对左右子树进行同样的操作。
以下是从中序和后序遍历构建二叉树的示例代码：
```cpp
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return build(inorder, 0, inorder.size() - 1,
                     postorder, 0, postorder.size() - 1);
    }

    TreeNode* build(vector<int>& inorder, int inStart, int inEnd,
                    vector<int>& postorder, int postStart, int postEnd) {
        if (inStart > inEnd || postStart > postEnd) {
            return nullptr;
        }

        int rootVal = postorder[postEnd];
        TreeNode* root = new TreeNode(rootVal);

        int inRootIndex = inStart;
        while (inRootIndex <= inEnd && inorder[inRootIndex] != rootVal) {
            inRootIndex++;
        }
        int leftTreeSize = inRootIndex - inStart;

        root->left = build(inorder, inStart, inRootIndex - 1,
                           postorder, postStart, postStart + leftTreeSize - 1);
        root->right = build(inorder, inRootIndex + 1, inEnd,
                            postorder, postStart + leftTreeSize, postEnd - 1);

        return root;
    }
};
```
复杂度分析
时间复杂度：O(n)，其中 n 是二叉树的节点数。每个节点被访问一次。
空间复杂度：O(n)，为递归过程中栈的开销，平均情况下为 O(log n)，最坏情况下树呈现链状，为 O(n)。
