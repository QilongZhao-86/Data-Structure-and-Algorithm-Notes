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
