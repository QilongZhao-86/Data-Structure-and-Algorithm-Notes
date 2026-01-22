
# C++ STL 完整笔记（代码 + 精准语义注释版）
---

## 1️⃣ `vector<T>`

### 构造

```cpp
vector<int> v;                 
// 创建一个空 vector，不分配或只分配极小的初始空间

vector<int> v(n);              
// 创建一个大小为 n 的 vector，元素默认初始化为 0（int）

vector<int> v(n, x);           
// 创建一个大小为 n 的 vector，所有元素初始化为 x

vector<int> v = {1,2,3};       
// 使用初始化列表构造 vector，等价于 push_back 1,2,3

vector<int> v2(v.begin(), v.end());
// 使用迭代器区间构造 v2，复制 v 中的所有元素
```

---

### 访问

```cpp
v[i];          
// O(1) 随机访问，不检查越界，越界是未定义行为（可能直接炸）

v.at(i);       
// O(1) 随机访问，会检查越界，越界抛 std::out_of_range 异常

v.front();     
// 返回第一个元素的引用，vector 不能为空

v.back();      
// 返回最后一个元素的引用，vector 不能为空

v.data();      
// 返回指向底层连续内存的指针，可用于与 C API 交互
```

---

### 容量相关

```cpp
v.size();      
// 当前元素个数

v.capacity();  
// 当前已分配但未必使用的容量（>= size）

v.empty();     
// 判断 size 是否为 0

v.reserve(n);  
// 预分配至少 n 个元素的空间，不改变 size，用于避免多次扩容

v.resize(n);   
// 修改 size：
// 如果变大，新增元素会被默认初始化
// 如果变小，尾部元素被删除

v.shrink_to_fit();  
// 请求释放多余容量（非强制，取决于实现）
```

---

### 修改

```cpp
v.push_back(x);    
// 在末尾插入元素，均摊 O(1)，可能触发扩容导致迭代器全部失效

v.pop_back();     
// 删除末尾元素，O(1)

v.insert(pos, x); 
// 在 pos 前插入一个 x，pos 及其之后的迭代器失效

v.insert(pos, k, x); 
// 在 pos 前插入 k 个 x

v.insert(pos, first, last); 
// 在 pos 前插入一个区间 [first, last)

v.erase(pos);     
// 删除 pos 位置的元素，pos 及其之后的迭代器失效

v.erase(first, last); 
// 删除区间 [first, last)

v.clear();        
// 删除所有元素，size 变 0，capacity 不变

v.swap(v2);       
// 交换两个 vector 的内容，O(1)，常用于释放内存
```

---

### 迭代器

```cpp
v.begin(), v.end();    
// 正向迭代器，指向第一个元素和“尾后”位置

v.cbegin(), v.cend();  
// const 版本迭代器，不能通过它修改元素

v.rbegin(), v.rend();  
// 反向迭代器，从最后一个元素向前遍历
```

---

### 失效规则（极其重要）

```text
push_back：
- 如果发生扩容：所有指针 / 引用 / 迭代器全部失效
- 如果未扩容：原有迭代器有效

erase：
- 被删除位置及其之后的迭代器全部失效
```

---

## 2️⃣ `deque<T>`

```cpp
deque<int> dq;           
// 创建双端队列，分段连续存储

dq.push_front(x);        
// 在头部插入，O(1)

dq.push_back(x);         
// 在尾部插入，O(1)

dq.pop_front();          
// 删除头部元素

dq.pop_back();           
// 删除尾部元素

dq.front();              
// 返回头部元素

dq.back();               
// 返回尾部元素

dq[i];                   
// 支持随机访问，但比 vector 慢
```

> ⚠️ deque 的 **迭代器稳定性很差**，插入删除可能导致全部失效

---

## 3️⃣ `list<T>`（双向链表）

```cpp
list<int> lst;           
// 双向链表，非连续存储

lst.push_front(x);       
// 头插，O(1)

lst.push_back(x);        
// 尾插，O(1)

lst.pop_front();         
// 删除头节点

lst.pop_back();          
// 删除尾节点

lst.insert(pos, x);      
// 在 pos 前插入 x，不会使其他迭代器失效

lst.erase(pos);          
// 删除 pos，仅 pos 失效
```

---

### LRU 核心操作

```cpp
lst.splice(pos, lst, it); 
// 将 it 指向的节点 O(1) 移动到 pos 前
// 不拷贝、不删除、不分配内存

lst.remove(x);           
// 删除所有值等于 x 的节点，O(n)

lst.unique();            
// 删除相邻重复元素（必须先排序才有全局去重效果）

lst.sort();              
// 链表专用排序，归并排序，O(n log n)

lst.reverse();           
// 原地反转链表
```

---

## 4️⃣ `forward_list<T>`

```cpp
forward_list<int> fl;    
// 单向链表，比 list 更省空间

fl.push_front(x);        
// 只能头插

fl.insert_after(it, x);  
// 在 it 后插入

fl.erase_after(it);      
// 删除 it 后的节点
```

---

## 5️⃣ `set<T>`

```cpp
set<int> s;              
// 有序集合，元素唯一，红黑树实现

s.insert(x);             
// 插入元素，O(log n)

s.erase(x);              
// 删除所有值为 x 的元素（set 中至多一个）

s.erase(it);             
// 删除迭代器 it 指向的元素

s.find(x);               
// 返回指向 x 的迭代器，找不到返回 end()

s.count(x);              
// 返回 x 出现次数（set 中只可能是 0 或 1）
```

---

### 区间查找

```cpp
s.lower_bound(x);        
// 返回第一个 >= x 的迭代器

s.upper_bound(x);        
// 返回第一个 > x 的迭代器

s.equal_range(x);        
// 返回 {lower_bound(x), upper_bound(x)}
```

---

## 6️⃣ `map<Key, Value>`

```cpp
map<int,int> mp;         
// 有序键值对，key 唯一，红黑树

mp[key];                
// 若 key 不存在：插入 key 并默认构造 value
// 若存在：返回 value 的引用

mp.at(key);             
// key 不存在会抛异常

mp.insert({k,v});       
// 插入键值对

mp.erase(k);            
// 删除 key 对应的元素

mp.find(k);             
// 查找 key，返回迭代器

mp.count(k);            
// 判断 key 是否存在（0 或 1）
```

---

### 遍历

```cpp
for (auto &[k,v] : mp) { 
    // k 是 const Key，v 是 Value 的引用
}
```

---

## 7️⃣ 无序容器（Hash）

```cpp
unordered_map<int,int> ump; 
// 哈希表，平均 O(1)，最坏 O(n)

ump[k] = v;                
// 插入或修改

ump.find(k);               
// 查找

ump.count(k);              
// 判断是否存在
```

> ⚠️ **rehash 会使所有迭代器失效**

---

## 8️⃣ 容器适配器

### `stack`

```cpp
stack<int> st;         
// 默认基于 deque

st.push(x);            
// 入栈

st.pop();              
// 出栈

st.top();              
// 查看栈顶元素

st.empty();            
// 是否为空

st.size();             
// 元素数量
```

---

### `queue`

```cpp
queue<int> q;          
// FIFO 队列

q.push(x);             
// 入队

q.pop();               
// 出队

q.front();             
// 队首

q.back();              
// 队尾
```

---

### `priority_queue`

```cpp
priority_queue<int> pq; 
// 默认大根堆（最大值优先）

priority_queue<int, vector<int>, greater<int>> pq;
// 小根堆（最小值优先）

pq.push(x);             
// 插入元素

pq.pop();               
// 删除堆顶

pq.top();               
// 访问堆顶元素
```

---

## 9️⃣ `<algorithm>`

```cpp
sort(first, last);      
// 快速排序 + 插排 + 堆排混合，O(n log n)

stable_sort(first,last);
// 稳定排序（归并排序）

nth_element(first,nth,last);
// 保证 nth 在最终位置，左小右大，O(n)
```

---

## 🔟 lambda

```cpp
auto cmp = [](int a, int b){
    return a > b;       
    // 返回 true 表示 a 排在 b 前面
};

sort(v.begin(), v.end(), cmp);
```
