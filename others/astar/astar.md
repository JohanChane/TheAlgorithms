# AStar

## References

- [A\* Search Algorithm](https://www.geeksforgeeks.org/a-search-algorithm/)

## 说明

closeList 存放已走过的点

openList 存放还没有走过且可以通过的点

h 为当前点到目的点的直线距离

g 为当前点到源点的路程

f = h + g. f 是源点到目的点的估算距离。每次都是先走 f 最小的点。

parent 用于回溯

## AStar 思路

1.  将源点加入 OpenList。
2.  从 openList 中取出 f 最小的点，这个点就是当前点。走到当前点，将当前点加入 colsedList。
3.  处理当前点的相邻点。如果相邻点是目的点，则结束。否则，如果还没有加入 closedList 且是可通过的相邻点 v，计算的 v 的 f，如果 f 比之前小，则将 v 加入 openList（set）。更新 v 的相关数据（parent, f, ...）。
4.  重复步骤 2 直至 openList 为空。
