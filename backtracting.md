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

下面给你写一份**从 2 开始的 Combination Sum II（LeetCode 40）专题笔记**，风格与之前的回溯专题保持一致，标题清晰、结构规整、带树形图讲解“为什么不去重会生成重复答案”。

---

## 2. 组合问题：Combination Sum II（去重版）

[Combination Sum II](https://leetcode.cn/problems/combination-sum-ii/) 是组合类回溯题中非常典型也非常“精细”的一个分支：
**数组中有重复元素，但结果中不能出现重复组合。**

这就与上一题纯“组合问题”相比，多了一个关键任务：
**控制同一层的重复选择。**

整理得更完整一点，这道题有三个要点：

1. 每个数只能选一次（典型组合问题特征；回溯下一层传 `i+1`）
2. 数组可能含重复元素
3. 最终输出的组合不能重复

---

### 2.1 题目示例（核心示例）

输入：

```
candidates = [10,1,2,7,6,1,5]
target = 8
```

输出：

```
[
  [1,1,6],
  [1,2,5],
  [1,7],
  [2,6]
]
```

第一眼容易忽视的重点：

* 输入数组里 **两个 1 不挨着**
* 输出中允许出现两个 1，但每个组合只能出现一次（结果不能重复）

所以如何避免重复，是我们接下来要分析的重点。

---

### 2.2 回溯模型

这个题仍然是标准回溯框架：

```
for 从 start 到 末尾:
    做选择
    递归（i+1）
    撤销选择
```

关键差异：
**需要去重 → 必须排序 → 然后跳过同层重复值。**

---

### 2.3 为什么会产生重复？（非常关键）

排序后的数组是：

```
[1,1,2,5,6,7,10]
 index: 0 1 2 3 4 5  6
```

其中 index 0 和 1 都是 **1**。

---

### 2.4 ● 不加去重时，会产生两个 `[1,7]`

看搜索路径（这是理解本题的核心）：

### 路径一：从 index 0 的 1 出发

```
选择 1(a, index 0)
  → 继续搜索到 7
    → 得到 [1,7]
```

### 路径二：从 index 1 的 1 出发

```
选择 1(b, index 1)
  → 继续搜索到 7
    → 又得到 [1,7]
```

两条路径走出来的组合内容一样，但来自不同的数组位置。
如果不做去重，这两个路径都会被记录下去。

也就是说：

```
ans = [
  [1,7],   // 来自 1(a)
  [1,7],   // 来自 1(b)
]
```

组合重复一模一样。

---

### 2.5 ● 不加去重时，也会产生两个 `[1,2,5]`

结构完全相同：

```
1(a) → 2 → 5   => [1,2,5]
1(b) → 2 → 5   => [1,2,5]
```

只要 value 一样，路径的值序列就一样，但你却 push 两次 —— 重复不可避免。

---

### 2.6 ● 本质原因

**同一层的“重复数字”生成了“重复的递归起点”。**

路径不同，但组合相同，这是“同层重复”的经典特征。

关键词：**同层（重要！）**

如果概念还没完全稳固，可以看下面的图。

---

### 2.7 搜索树图示：展示重复是如何出现的

画顶层搜索树（未去重）：

```
                           []
            ------------------------------------------
            1(a)         1(b)        2        5 ...
```

注意：

* 1(a) 和 1(b) 在同一层（都在根节点下面）
* 每个都会继续往下扩展
* 后续看到的 2、5、6、7 都一样

于是就出现了：

```
1(a) → 7  -- produces --> [1,7]
1(b) → 7  -- produces --> [1,7]  (duplicate)
```

或者：

```
1(a) → 2 → 5 --> [1,2,5]
1(b) → 2 → 5 --> [1,2,5] (duplicate)
```

这就是不去重的搜索树。

重复完全不是 BUG，而是树本身带来的。

---

### 2.8 如何去重？（同层去重核心语句）

为了避免“同层重复展开”，我们使用：

```cpp
if (i > start && candidates[i] == candidates[i - 1]) 
    continue;
```

含义：

* `i > start`：说明这是**同一层**的后续节点
* `candidates[i] == candidates[i-1]`：说明值重复
* → 快速跳过该节点，不允许它作为新的起点产生另一棵子树

效果：

* 只允许同层重复数字中的 **第一个** 作为起点
* 对于组合问题，这恰好能去掉所有重复路径

搜索树变成：

```
                        []
       ------------------------------------------
       1(a)           2        5        6 ...
   （1(b) 被剪掉）
```

于是：

* `[1,7]` 只会出现一次
* `[1,2,5]` 只会出现一次
* `[1,1,6]` 仍然会出现一次（因为这个不是同层重复）

---

### 2.9 完整代码模板

这是最终可用、逻辑最清晰的写法：

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;

    void dfs(vector<int>& candidates, int target, int start) {
        if (target == 0) {
            ans.push_back(path);
            return;
        }

        for (int i = start; i < candidates.size(); ++i) {
            // ——【同层去重】：跳过同一层重复的数字
            if (i > start && candidates[i] == candidates[i - 1]) 
                continue;

            if (candidates[i] > target) 
                break;

            path.push_back(candidates[i]);
            dfs(candidates, target - candidates[i], i + 1);  // i+1 保证每个元素最多用一次
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0);
        return ans;
    }
};
```

---

### 2.10 本节总结（你可以直接放进笔记里）

1. 本题的核心是 **同层去重**。
2. 不去重时，相同的数字会在同一层生成多个递归起点，导致重复组合。
3. 排序 + `(i > start && candidates[i] == candidates[i-1]) continue;`
   可以有效避免重复。
4. 组合问题用 `i+1` 控制每个数只能使用一次。
5. 通过画搜索树，可以清楚看到为什么重复会出现、为什么去重能消灭重复。
---
## 3. 回文分割（LeetCode 131）

本题要求：将字符串分割成若干子串，使得每个子串都是回文字符串，并返回所有可能的分割方案。
[LeetCode 131. Palindrome Partitioning](https://leetcode.cn/problems/palindrome-partitioning/)
要点包括：

1. **回文判断要快速查询（使用 DP）**
2. **回溯生成所有分割方案（使用划分型回溯框架）**
3. **回文 DP 与回溯配合使用**

---

### 3.1 问题分析

对任意字符串 `s`，我们需要找到所有可能的划分方式，使得每一段 `s[l:r]` 都是回文。

例如：

```
输入：s = "aab"
输出：
[
  ["a","a","b"],
  ["aa","b"]
]
```

由于回溯会频繁检查某个区间 `[i,j]` 是否为回文，如果每次都用双指针检查，开销会非常大。

所以引入 **DP 预处理**，提前得出：

```
isPalindrome[i][j] = s[i..j] 是否为回文
```

之后回溯时可以 O(1) 查表，提高效率。

---

### 3.2 回文判断 DP

#### DP 数组定义

```
isPalindrome[i][j] = (s[i..j] 是不是回文)
```

#### DP 递推公式

```
当 i == j 时：单字符 → 必是回文

当 j - i == 1 时：两个字符 → s[i] == s[j]

当 j - i >= 2 时：
    s[i] == s[j] 且 isPalindrome[i+1][j-1] 为真
```

因此转移方程为：

```
if (j == i)  isPalindrome[i][j] = true
else if (j - i == 1) isPalindrome[i][j] = (s[i] == s[j])
else isPalindrome[i][j] = (s[i] == s[j] && isPalindrome[i+1][j-1])
```

#### 遍历顺序

因为 `isPalindrome[i][j]` 依赖 `isPalindrome[i+1][j-1]`，所以必须：

* **i 从后往前 ↓**
* **j 从 i 往后 →**

完整代码：

```cpp
void computePalindrome(const string& s) {
    isPalindrome.resize(s.size(), vector<bool>(s.size(), false));
    for (int i = s.size() - 1; i >= 0; i--) {
        for (int j = i; j < s.size(); j++) {
            if (j == i) 
                isPalindrome[i][j] = true;
            else if (j - i == 1) 
                isPalindrome[i][j] = (s[i] == s[j]);
            else 
                isPalindrome[i][j] = (s[i] == s[j] && isPalindrome[i+1][j-1]);
        }
    }
}
```

DP 完成后，我们可以 O(1) 判断任何区间是否为回文。

---

### 3.3 回溯划分子串

#### 回溯函数定义

```
startIndex 指向当前需要分割的位置
path 保存当前分割方案
result 保存所有方案
```

框架为：

```
如果 startIndex 走到末尾 → 得到一个有效方案
否则枚举区间 [startIndex, i]
    若是回文 → 加入 path → 递归 → 回溯弹出
```

关键点：
**只有当 isPalindrome[startIndex][i] 为真时才尝试分割。**

完整回溯代码：

```cpp
void backtracking(const string& s, int startIndex) {
    if (startIndex >= s.size()) {
        result.push_back(path);
        return;
    }

    for (int i = startIndex; i < s.size(); i++) {

        // 若不是回文，跳过当前 i
        if (!isPalindrome[startIndex][i]) {
            continue;
        }

        // 是回文，尝试加入
        string sub = s.substr(startIndex, i - startIndex + 1);
        path.push_back(sub);

        // 递归处理剩余部分
        backtracking(s, i + 1);

        // 回溯
        path.pop_back();
    }
}
```

这里 `continue` 只跳过 **非回文路径** 的 push / 递归 / pop，
但 **回文路径一定会执行 push → 递归 → pop**，保证回溯完整性。

---

### 3.4 主函数整合

```cpp
vector<vector<string>> partition(string s) {
    result.clear();
    path.clear();
    computePalindrome(s);
    backtracking(s, 0);
    return result;
}
```

---

### 3.5 时间复杂度分析

* **回文 DP 预处理：O(n²)**
* **回溯枚举所有方案：最坏 O(n·2ⁿ)**
  因为每个位置都可以选择切或不切
* 总体上性能足够应对题目限制（n ≤ 16）

---

### 3.6 总结

1. 通过 DP 预处理所有 `[i,j]` 回文区间，回溯时能 O(1) 判断。
2. 回溯负责枚举所有可能的切分方式。
3. DP + 回溯是本题的标准高效组合。
---

## 4. 复原 IP 地址（Restore IP Addresses）
题目链接：[Leetcode 93.复原 IP 地址](https://leetcode.cn/problems/restore-ip-addresses/description/)
给定字符串 `s`，将其拆分成所有可能的合法 IPv4 地址。IPv4 由四段构成，每段满足：

1. 值在 **0~255 之间**
2. **不能有前导零**（除了单独一个“0”）

本题的关键是：
段数固定（4），每段长度 ≤3，因此状态空间非常小，天然适合 **回溯**，甚至可以直接写成 **三层暴力循环**。

---

### 4.1 IPv4 的结构与关键限制

合法 IPv4：

```
A . B . C . D
A, B, C, D ∈ [0, 255]
```

拆分过程只有两件事要做：

* 选出四个“切割点”
* 检查每段是否合法

每段的字符串长度只能是 1 / 2 / 3，因此最多只有 **3 × 3 × 3 × 3 = 81 种组合**，规模极小。

---

### 4.2 搜索树图示：回溯到底在做什么？

以 `"255255"` 为例，回溯搜索树大致如下（只画前两层）：

```
(segId=0, start=0)
   /         |         \
 "2"       "25"       "255"
  ↓          ↓          ↓
(segId=1, start=1/2/3)
   / | \     / | \      / | \
 ... ...     ... ...    ... ...
```

特点：

* 深度固定为 4（四段）
* 每层最多 3 个分叉（段长 1/2/3）
* 图极小，本质上常数级复杂度

因此本题是典型的“小搜索空间枚举”问题。

---

### 4.3 **回溯解法：逐段构造 IP 地址**

---

#### 4.3.1 思路总结

用 DFS 去构造第 `segId` 段，从下标 `segStart` 开始取数字。

关键规则：

1. **填完 4 段且刚好用完字符串 → 得到一个 IP**
2. **字符串提前用完 → 回溯**
3. **遇到前导零 → 该段必须为 "0"**
4. **一般情况 → 尝试长度 1/2/3，只要 ≤255 即可深入下一层**

---

#### 4.3.2 带注释的完整代码（C++）

```cpp
class Solution {
private:
    static constexpr int SEG_COUNT = 4;
    // constexpr：编译期常量，不占用额外空间，效率最高。
    // SEG_COUNT=4 表示 IPv4 有固定 4 段。

private:
    vector<string> ans;     // 存放所有合法的 IP 地址
    vector<int> segments;   // 临时数组，存当前 DFS 已经构造好的各段数值

public:
    // 深度优先搜索
    // segId: 当前正在构造第 segId 段（0~3）
    // segStart: 当前段从字符串 s 的哪个下标开始取数字
    void dfs(const string& s, int segId, int segStart) {

        // ------------ 情况 1：已经构造了 4 段 ------------
        if (segId == SEG_COUNT) {
            // 如果此时已经完全用完字符串 → 属于合法 IP
            if (segStart == s.size()) {

                string ipAddr;

                // 将 4 段拼成字符串，例如 "192.168.0.1"
                for (int i = 0; i < SEG_COUNT; ++i) {
                    ipAddr += to_string(segments[i]);  // 数字转字符串并拼接
                    if (i != SEG_COUNT - 1) {
                        ipAddr += ".";                 // 中间加点
                    }
                }

                // move(ipAddr)：避免产生一次不必要的拷贝，提高性能
                // ans.push_back(ipAddr) 也可以用，但会复制
                ans.push_back(move(ipAddr));
            }
            return; // 无论是否成功，都结束此路径
        }

        // ------------ 情况 2：字符串提前用完 ------------
        // 例如已经构造到第 2 段，但 s 已经没有字符可用了
        if (segStart == s.size()) {
            return; // 后面没法构造更多段，直接回溯
        }

        // ------------ 情况 3：段以 '0' 开头，只能是 0 ------------
        // 前导零禁止，例如 "01", "00", "023" 都非法
        if (s[segStart] == '0') {
            segments[segId] = 0;                       // 该段只能取 "0"
            dfs(s, segId + 1, segStart + 1);           // 下一段从 segStart+1 开始
            return; // 注意这里必须 return，不能再尝试多位数
        }

        // ------------ 情况 4：正常情况：枚举段长为 1~3 的数字 ------------
        int addr = 0;  // 当前段的数值累加

        for (int segEnd = segStart; segEnd < s.size(); ++segEnd) {

    // 用逐位累加方式计算这个段的数值：
    // 例如字符 '2','3','5' → 235
            addr = addr * 10 + (s[segEnd] - '0');

    // 检查是否在合法范围内
    // IPv4 单段必须是 1~255（前导零在上面处理了，因此无需考虑 addr==0 的多位情况）
            if (addr > 0 && addr <= 255) {

                segments[segId] = addr;                // 把该段记录下来

                // 下一段从 segEnd+1 开始继续 DFS
                dfs(s, segId + 1, segEnd + 1);

            } else {
                // 超出范围 (addr >255) 后，继续往后扩长度只会更大，无需尝试
                break;  // 剪枝
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        segments.resize(SEG_COUNT); // 预先分配空间给四段
        dfs(s, 0, 0);               // 从第 0 段、下标 0 开始 DFS
        return ans;                 // 返回所有合法 IP
    }
};

```

---

### 4.4 暴力循环写法（等价但不通用）

因为本题规模固定，甚至可以直接写成 **三层循环** + 判断：

* 选出 a、b、c 三个切割点（四段由三个切点确定）
* 对四段分别检查合法性

#### 思路可视化：

```
s = ABCDEFG...

i  = 第一段的结尾
j  = 第二段的结尾
k  = 第三段的结尾
```

#### 暴力代码（C++）：

```cpp
vector<string> restoreIpAddresses(string s) {
    vector<string> ans;
    int n = s.size();

    // i, j, k 是三个切割点，段长最多 3
    for (int i = 1; i <= 3 && i < n; ++i) {
        for (int j = i + 1; j <= i + 3 && j < n; ++j) {
            for (int k = j + 1; k <= j + 3 && k < n; ++k) {

                string a = s.substr(0, i);
                string b = s.substr(i, j - i);
                string c = s.substr(j, k - j);
                string d = s.substr(k);

                if (valid(a) && valid(b) && valid(c) && valid(d)) {
                    ans.push_back(a + "." + b + "." + c + "." + d);
                }
            }
        }
    }
    return ans;
}

bool valid(const string& seg) {
    if (seg.size() == 0 || seg.size() > 3) return false;
    if (seg[0] == '0' && seg.size() > 1) return false;
    int val = stoi(seg);
    return val >= 0 && val <= 255;
}
```

你可以看到，它的确是“三层循环 + 判断”，逻辑比 DFS 更直接。

---

### 4.5 回溯 vs 暴力循环：图示对比

#### 回溯的搜索树：

```
                  DFS(0,0)
           /         |         \
         1 位      2 位       3 位
          ↓         ↓           ↓
                DFS(1, x)
          /         |         \
        1 位       2 位       3 位
                ...
```

---

#### 暴力循环的隐式结构：

```
for(i = seg1_end)
    for(j = seg2_end)
        for(k = seg3_end)
            检查四段是否合法
```

三层循环其实就是把搜索树“平铺展开”了。

---

### 4.6 深度分析（基于评论内容）

评论的核心观点非常有价值，总结如下：

---

#### （1）回溯 ≈ 剪枝后的暴力枚举，本质上两者复杂度一致

本题的段数与段长都受到强约束，因此：

* 回溯的最多分支 = 3
* 深度 = 4

暴力循环虽然看起来“更暴力”，但本质上也是在遍历同一棵极小的搜索树。

其时间复杂度几乎是一样的。

---

#### （2）真正耗时的是“输出结果”的字符串构造 —— O(|s|)

不管哪种方法：

* 每找到一个合法 IP，就要执行字符串拼接 `"a.b.c.d"`
* 这是 O(|s|) 的操作

所以无论回溯还是暴力，都无法绕过这个成本。

---

#### （3）整题可以视为“一个半径为 4、度最大为 3 的小图遍历”

* 回溯：深度优先遍历这张小图
* 暴力：用固定嵌套循环遍历同一张图，只是把图结构“手写”了出来

因为图很小，两种方法都足够快。

---

#### （4）回溯的重要性：它是通向更复杂算法的基础思维

尽管此题可以暴力解决，但回溯的价值在于：

* 解决组合、排列、子集问题
* 树形搜索
* DFS → 记忆化搜索 → 动态规划
* 几乎所有搜索类题的基础

它不是为了这道题本身，而是一种算法思维框架。

---

### 4.7 小结

| 项目   | 回溯        | 暴力三层循环           |
| ---- | --------- | ---------------- |
| 可扩展性 | 强（适合变化结构） | 弱（死板，结构固定）       |
| 可读性  | 段与段之间结构清晰 | 需对每段长度手写循环       |
| 性能   | 一样        | 一样               |
| 适用场景 | 通用搜索问题    | 本题这种固定 4 段的小规模问题 |

两者在本题中性能几乎一致，只是写法风格不同。

---
