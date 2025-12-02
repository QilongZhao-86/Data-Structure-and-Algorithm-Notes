# 回溯算法！！！
## 1. 组合问题（Combinations）

组合问题是回溯算法中最典型、最基础的题型之一。  
目标是在给定范围内，按要求选出若干元素，**强调“元素无序（顺序不重要）且不能重复选”**。

典型题目：  
- [LeetCode 77. Combinations](https://leetcode.cn/problems/combinations/description/)  
- 从 1~n 中选 k 个数，返回所有组合。

组合问题的标准特征：
- 选与不选  
- 顺序不敏感（[1,2] 与 [2,1] 视为同一组合）  
- 往往需要“从 i 开始选，下一层从 i+1 开始”来避免重复  
- 可以通过剪枝进行性能优化  

接下来进入详细的回溯分析与代码实现。

---

### 1.1 回溯算法思想概述

回溯（Backtracking）是一种“构建解 → 判断 → 撤销 → 换一种选法”的深度优先探索。

解决组合问题的核心思想：

1. **路径（path）**：当前已经选择的数字  
2. **选择列表（choices）**：还能选择哪些数字  
3. **结束条件**：当 path 的长度达到 k 时，得到一个组合

回溯本质 = 构建一条搜索路径，再在返回时撤回选择，继续探索其它路径。

---

### 1.2 回溯树结构（理解组合问题的关键）

以 n = 4, k = 2 为例，组合的选择过程是一棵树：
```

             []

      /       |       \
    [1]      [2]      [3]
   /   \     / \        \

[1,2] [1,3] [2,3] [2,4]   [3,4]
```
每条从根到叶子的路径（长度 = k）就是一个合法组合。

回溯算法就是按照这棵隐含搜索树进行 DFS。

---

### 1.3 剪枝思想（Pruning）

如果还需要选 `k - path.size()` 个数字，但剩余数字不够，则无法构成组合，可以提前停止。

例如在 n=4, k=3 时：

当 path=[3] → 剩余数字只有 {4} 1 个，但需要选 2 个 → 必然失败 → 直接剪枝

剪枝判断公式：

> i <= n - (k - path.size()) + 1

这个条件显著减少递归深度，加速回溯。

---

### 1.4 代码模板（最优写法）

下面给出 C++ 的组合问题标准模板，可直接用于所有“选 k 个”的组合题。

```cpp
class Solution {
private:
    vector<vector<int>> result;  // 存放最终结果
    vector<int> path;            // 当前路径（组合）
    
    void backtracking(int n, int k, int startIndex) {
        // 终止条件：选满 k 个
        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        // 剪枝：i 的上界保证剩余数字足够
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) {
            path.push_back(i);                  // 做选择
            backtracking(n, k, i + 1);         // 下一层选择从 i+1 开始
            path.pop_back();                   // 回溯（撤销选择）
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return result;
    }
};
```

⸻

### 1.5 代码逐行解释
	•	result：保存所有组合
	•	path：保存当前正在构造的组合
	•	startIndex：控制下一轮从哪里开始选择，避免重复

核心逻辑：
	1.	选择数字 i
path.push_back(i)
	2.	递归进入下一层，从 i+1 开始选
保证组合是递增的、无重复
	3.	回到上一层 → 撤销选择
path.pop_back()

剪枝部分：

i <= n - (k - path.size()) + 1

意思是：剩余可选数字必须够用，否则不进入分支。

⸻

### 1.6 示例 walkthrough（n=4, k=2）

回溯过程：

path=[]
i=1 → path=[1]
    i=2 → [1,2] ✔
    i=3 → [1,3] ✔
    i=4 → [1,4] ✔
回溯到 []
i=2 → path=[2]
    i=3 → [2,3] ✔
    i=4 → [2,4] ✔
回溯到 []
i=3 → path=[3]
    i=4 → [3,4] ✔
回溯到 []

结束。

最终输出：

[1,2]
[1,3]
[1,4]
[2,3]
[2,4]
[3,4]


⸻

### 1.7 组合问题的通用回溯模板（可复用）

如果你遇到更多类似的“从 N 个数字里选 K 个”，可以直接套下面这个模板：

def backtracking(start):
    if 选够了K个:
        收集结果
        return

    for i from start to n:
        做选择 i
        backtracking(i+1)
        撤销选择 i

剪枝版本：

> for i from start to n - (k - path.size()) + 1:

这是组合类问题的 万能模板。

⸻

### 1.8 小结

组合问题的本质：
	1.	树形结构的 DFS 搜索
	2.	每次选 or 不选当前数字
	3.	保证选出的数字递增（从 i → i+1）
	4.	剪枝保证剩余数字够用
	5.	路径达到 k 就是合法组合

