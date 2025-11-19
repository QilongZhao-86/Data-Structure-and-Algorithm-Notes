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