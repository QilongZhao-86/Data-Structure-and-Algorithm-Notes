# 刷题笔记
---

## 1. 滑动窗口（Sliding Window）

### 1.1 核心思想

滑动窗口是一种高效解决**连续区间问题**的算法技巧。
本质思想：使用两个指针 `left` 和 `right` 维护一个动态区间 `[left, right)`，
在遍历过程中根据条件扩张或收缩窗口。

**典型应用：**

* 最短/最长子数组长度
* 子数组和、平均值、乘积问题
* 符合条件的子串（如最小覆盖子串）

滑动窗口可看作“双指针”技巧的特化，用于处理**连续区间问题**。
而“双指针”更广泛，用于排序数组、链表遍历、快慢指针等。

---

### 1.2 标准逻辑结构

```cpp
int left = 0, right = 0;
while (right < n) {
    // Step 1: 扩大窗口
    更新窗口状态;
    right++;

    // Step 2: 收缩窗口（满足条件时）
    while (窗口满足条件) {
        更新答案;
        移出 nums[left];
        left++;
    }
}
```

**特征总结：**

* `right` 扩展窗口；
* `left` 收缩窗口；
* 两指针只向右移动；
* 每个元素最多被访问两次 → 时间复杂度 O(n)。

---

### 1.3 例题：LeetCode 209 – Minimum Size Subarray Sum

📎 [LeetCode 209. Minimum Size Subarray Sum](https://leetcode.cn/problems/minimum-size-subarray-sum/)

#### 1.3.1 题目描述

给定一个正整数数组 `nums` 和一个目标值 `target`，
找出其和 **≥ target** 的最短连续子数组长度。
若不存在，返回 `0`。

**示例输入：**

```cpp
target = 7
nums = [2,3,1,2,4,3]
```

**输出：**

```
2   // 对应子数组 [4,3]
```

---

### 1.4 代码实例对比

#### 1.4.1 我的原始写法（非标准版本）

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = 0;
        int result = n + 1;
        int sum = 0;
        while (left < n && right < n) {
            while (sum < target && right < n) {
                sum += nums[right];
                right++;
            }
            while (sum >= target && left < right) {
                result = ((right - left) < result) ? (right - left) : result;
                sum -= nums[left];
                left++;
            }
        }
        if (result == n + 1)
            return 0;
        return result;
    }
};
```

**存在问题：**

* 外层条件 `left < n && right < n` 多余；
* 可能导致右指针停滞、陷入死循环；
* 窗口长度少计算了 `+1`；
* 内外层循环逻辑不对称，可读性差。

---

#### 1.4.2 官方标准写法（正确版本）

```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int ans = INT_MAX;
        int start = 0, end = 0;
        int sum = 0;

        while (end < n) {
            sum += nums[end];
            while (sum >= s) {
                ans = min(ans, end - start + 1);
                sum -= nums[start];
                start++;
            }
            end++;
        }
        return ans == INT_MAX ? 0 : ans;
    }
};
```

**逻辑要点：**

* 外层循环移动 `end`；
* 内层循环收缩 `start`；
* 每个元素仅被加入与移出各一次；
* 时间复杂度 O(n)，空间复杂度 O(1)。

---

### 1.5 执行过程可视化

|  步骤 | 窗口 `[start, end]` | 元素        | 当前和 | ≥7? | 最短长度 |
| :-: | :---------------- | :-------- | :-: | :-: | :--: |
|  1  | [0,0]             | [2]       |  2  |  否  |   -  |
|  2  | [0,1]             | [2,3]     |  5  |  否  |   -  |
|  3  | [0,2]             | [2,3,1]   |  6  |  否  |   -  |
|  4  | [0,3]             | [2,3,1,2] |  8  |  ✅  |   4  |
|  5  | [1,3]             | [3,1,2]   |  6  |  否  |   -  |
|  6  | [1,4]             | [3,1,2,4] |  10 |  ✅  |   4  |
|  7  | [2,4]             | [1,2,4]   |  7  |  ✅  |   3  |
|  8  | [3,4]             | [2,4]     |  6  |  否  |   -  |
|  9  | [3,5]             | [2,4,3]   |  9  |  ✅  |   3  |
|  10 | [4,5]             | [4,3]     |  7  |  ✅  |   2  |

✅ **最终答案：2**

---

### 1.6 常见陷阱与注意点

| 错误点      | 原因                                 | 修正方法                   |
| :------- | :--------------------------------- | :--------------------- |
| 指针更新方向错误 | `right` 回退破坏单调性                    | 只增不退                   |
| 外层条件错误   | 使用 `left < n && right < n` 导致右指针停滞 | 用 `while (right < n)`  |
| 窗口长度计算错误 | 忘记 `+1`                            | 长度 = `end - start + 1` |
| sum 溢出问题 | 未及时收缩                              | 满足条件后立即进入收缩循环          |
| 结果初始化不当  | 没用 INT_MAX                         | 应初始化为极大值并最终判断          |

---

### 1.7 复杂度分析

* **时间复杂度：** O(n)
  每个元素最多进入与离开窗口各一次。
* **空间复杂度：** O(1)

---

### 1.8 思维口诀

> “滑动窗口的本质是：**扩展直到满足，收缩直到不满足**。”

* 对于“最小长度”问题：满足条件时收缩；
* 对于“最大长度”问题：不满足条件时扩展。

---

### 1.9 模板记忆表

| 阶段 | 操作               | 条件           | 目的     |
| :- | :--------------- | :----------- | :----- |
| 1  | 扩展窗口 (`right++`) | 未满足条件        | 包含更多元素 |
| 2  | 收缩窗口 (`left++`)  | 已满足条件        | 寻找最优解  |
| 3  | 更新结果             | 满足条件时        | 记录最优值  |
| 4  | 结束循环             | `right == n` | 遍历完毕   |

---

### 1.10 拓展题型建议

| 题目方向            | 示例           |
| :-------------- | :----------- |
| 最短子数组和 ≥ target | LeetCode 209 |
| 含K个不同字符的最长子串    | LeetCode 340 |
| 无重复字符的最长子串      | LeetCode 3   |
| 最小覆盖子串          | LeetCode 76  |
| 固定窗口最大/最小值      | LeetCode 239 |
---

## 2. 递归（Recursion）

### 2.1 核心思想  

**递归（Recursion）** 是一种“让函数调用自身”的算法思想，用于解决可以分解为相似子问题的任务。  
递归包含三个关键步骤：  

1. **终止条件（Base Case）**：当问题足够小，可以直接返回结果。  
2. **递归调用（Recurrence）**：将大问题分解为更小的子问题。  
3. **结果合并（Return / Combine）**：将子问题结果向上传递。

链表是天然适合递归的结构，因为每个节点都指向下一个节点，整个链表就像一个“从头到尾的嵌套结构”。  
因此，许多链表题（如删除节点、反转链表、合并链表）都能用递归 elegantly 地实现。

---

### 2.2 移除链表元素（Remove Linked List Elements）

题号：LeetCode 203  
题意：删除链表中所有值等于 `val` 的节点，并返回新的头节点。

---

#### 2.2.1 递归法  

**思路分析：**  
- 对除头节点外的部分递归删除目标节点；
- 回溯时根据当前节点的值决定是否保留；
- 空链表为递归终止条件。

**关键逻辑：**
```cpp
head->next = removeElements(head->next, val);
return head->val == val ? head->next : head;
```

**代码实现：**

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr)
            return head;                        // 递归终止条件
        head->next = removeElements(head->next, val); // 递归处理子链表
        return head->val == val ? head->next : head;  // 回溯阶段决定是否删除当前节点
    }
};
```

**复杂度分析：**

* 时间复杂度：O(n)
* 空间复杂度：O(n)（递归调用栈）

---

#### 2.2.2 迭代法（官方写法）

**思路分析：**

* 创建一个哑节点 `dummyHead` 连接原链表；
* 使用指针 `temp` 遍历；
* 若 `temp->next->val == val`，则跳过下一个节点；
* 否则向后移动。

**代码实现：**

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0, head);
        ListNode* temp = dummyHead;
        while (temp->next != nullptr) {
            if (temp->next->val == val)
                temp->next = temp->next->next;
            else
                temp = temp->next;
        }
        return dummyHead->next;
    }
};
```

**复杂度分析：**

* 时间复杂度：O(n)
* 空间复杂度：O(1)

---

#### 2.2.3 我的版本（手动跳过头节点法）

**思路分析：**

* 若头节点等于目标值，需要不断前移；
* 之后用两个指针 `behind` 与 `temp` 维护链表；
* 若中间节点值为 `val`，跳过它，否则两指针同时前移；
* 最后处理尾节点是否删除。

**代码实现：**

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr)
            return nullptr;

        // 跳过前导等于 val 的节点
        while (head->val == val) {
            head = head->next;
            if (head == nullptr)
                return nullptr;
        }

        ListNode* temp = head->next;
        ListNode* behind = head;
        if (temp == nullptr)
            return head;

        // 删除中间节点
        while (temp->next != nullptr) {
            if (temp->val == val) {
                temp = temp->next;
                behind->next = temp;
            } else {
                temp = temp->next;
                behind = behind->next;
            }
        }

        // 处理最后一个节点
        if (temp->val == val)
            behind->next = nullptr;

        return head;
    }
};
```

**复杂度分析：**

* 时间复杂度：O(n)
* 空间复杂度：O(1)

---

#### 2.2.4 三种写法比较

| 对比维度    | 递归法    | 官方迭代法     | 我的实现    |
| ------- | ------ | --------- | ------- |
| 删除头节点方式 | 递归自然处理 | 使用哑节点简化   | 手动前移跳过  |
| 删除逻辑实现  | 通过回溯判断 | 指针修改 next | 双指针跳过节点 |
| 可读性     | 简洁优雅   | 清晰易维护     | 较繁琐但直观  |
| 时间复杂度   | O(n)   | O(n)      | O(n)    |
| 空间复杂度   | O(n)   | O(1)      | O(1)    |

---

#### 2.2.5 思维总结

1. 递归的魅力在于：**你不需要同时考虑所有节点，只要相信“子问题已解决”**。
2. 每一层递归仅需思考“当前节点是否保留”，这让复杂指针操作变得逻辑简单。
3. 但递归也有局限——在极长链表中可能导致栈溢出，因此面试中常用迭代法。
4. 理解这道题的递归思想，是进入链表高阶递归题（如反转、合并）的基础。

---

### 2.3 递归的通用模板

```cpp
返回类型 函数名(参数) {
    // 1. 终止条件
    if (终止条件)
        return 基础结果;

    // 2. 递归调用
    子问题结果 = 函数名(子问题参数);

    // 3. 合并结果
    return 当前结果与子结果的组合;
}
```

---

### 2.4 递归的常见应用方向（预留）

| 模块       | 示例题目                  | 说明       |
| -------- | --------------------- | -------- |
| **链表**   | 203. 移除链表元素、206. 反转链表 | 操作天然递归结构 |
| **树结构**  | 二叉树遍历、求最大深度           | 天生递归定义   |
| **分治法**  | 快速排序、归并排序             | 拆分子区间    |
| **回溯法**  | 全排列、组合总和              | 枚举搜索空间   |
| **数学递推** | 斐波那契数列、汉诺塔问题          | 自然数学定义   |

---

### 2.5 小结

* **递归思想本质：** “用函数调用自身”以简化问题。
* **链表递归精华：** 利用回溯阶段自然修改指针。
* **学习建议：** 先从“移除链表元素”“反转链表”等入手，再扩展到二叉树递归。
递归的魅力在于抽象思维：你不需要知道“下一步怎么走”，只需相信“子问题已经被解决”。
这是算法思维中最接近“自我复制逻辑”的一环——一种逻辑上的递归优雅。

---