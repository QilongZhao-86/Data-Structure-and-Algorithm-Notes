# 数据结构与算法-笔记
## 图
## 基本知识
简单路径：同一个点只包含一次  

简单环：简单路径的情况下围成一个圈，删去最后一个重复的节点。  

连通图：任意两个点之间都有路径链接  

子图：不可以使用同一条边两次及以上  

连通分量：在一个无向图里，如果你从某个顶点出发，沿着边一直走下去，能到达的所有顶点（以及这些顶点之间的边）共同组成一个**连通分量**（**每个连通图仅仅有一个连通分量**）。  
无环图（acyclic graph）是指不包含任何回路的图。 

树（tree）是无环且连通的图。  

若若干棵树互不相交（彼此没有公共顶点），它们的集合称为森林（forest）。 

连通图的**生成树**（spanning tree）是一个包含该图所有顶点、并且本身是一棵树的子图。 

一个图的**生成森林**（spanning forest）是该图各个连通分量的生成树的并集。

生成树：一个包含这个图所有顶点的子树。（边=顶点-1，连通图的生成树不唯一）  

共享点的边相邻（adjacent），共享边的点相邻；
### 无向图的特殊性质
每条边的形式为 (u, v)，其中 u ≠ v。  

在一个含有 n 个顶点的图中，可能的顶点对共有 n×(n−1) 个。  

由于在无向图中，(u, v) 与 (v, u) 表示的是同一条边，因此无向图中最多有 n×(n−1)/2 条边。  

换句话说，无向图的边数不超过 n×(n−1)/2。

### 有向图的特殊性质 
每条边的形式为 (u, v)，其中 u ≠ v。  

在一个具有 n 个顶点的图中，可能的顶点对共有 n×(n−1) 个。

由于在有向图中，(u, v) 与 (v, u) 表示的是不同的两条边，  因此有向图中最多可以有 n×(n−1) 条边。  

换句话说，有向图的边数不超过 n×(n−1)。  

indegree（入度） outdegree（出度） 总和相等

```
class Graph{  //图的ADT
	public:	               
 	int VerticesNum(); //返回图的顶点个数  
 	int EdgesNum();    //返回图的边数  
 	//返回与顶点oneVertex相关联的第一条边  
 	Edge FirstEdge(int oneVertex);  
 	//返回与边PreEdge有相同关联顶点oneVertex的下一条边  
 	Edge NextEdge(Edge preEdge);   
    //添加一条边
    bool setEdge(int fromVertex,int toVertex,int weight);  
    //删一条边
    bool delEdge(int fromVertex,int toVertex);
    //如果oneEdge是边则返回TRUE，否则返回FALSE
    bool IsEdge(Edge oneEdge); 
    //返回边oneEdge的始点
    int FromVertex(Edge oneEdge);  
    //返回边oneEdge的终点
    int ToVertex(Edge oneEdge);    
    //返回边oneEdge的权
    int Weight(Edge oneEdge);	
    }; 
```
binary-relation list  
example: {(1, 2), (1, 4), (3, 5), (4, 2), (4, 5), (5, 2), (5, 3), (5, 8), (6, 9), (7, 9), (8, 4)}  
Adjacency Matrix  有向图的纵坐标是出，横坐标是入；
example:   
![alt text](image.png)  
if for a weight graph（边上带权）  
![alt text](image-1.png)  
表示邻接矩阵需要n^2个字节的存储空间。对于无向图，可以只存储矩阵的下三角或上三角部分（不包括对角线）  
在邻接矩阵中，求某个顶点的度数或找出与该顶点相邻的顶点，所需时间复杂度为 O(n)。  

邻接表结构：

![alt text](image-2.png)
**space = a*V + b*E**
![alt text](image-3.png)
**space = a*V + 2*b*E**  
a是数组占用，b是链表占用  

正交表结构：  
1️⃣ 顶点结点（Head node）

每个顶点有一个头节点，包含三部分：

vexinfo：存放顶点本身的信息（比如名字或编号）

firstin：指向以该顶点为终点（入边）的第一条边

firstout：指向以该顶点为起点（出边）的第一条边

2️⃣ 边结点（List node）

每一条边在图中是一个独立的结点，包含六个字段：

tailvex：该边的起点

headvex：该边的终点

arcinfo：该边的额外信息（如权重）

tnext：指向具有相同起点的下一条边（下一条出边）

hnext：指向具有相同终点的下一条边（下一条入边）  

