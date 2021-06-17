# DataStructure
C++로 구현해보는 자료구조🤠

- [DataStructure](#datastructure)
  - [Trees](#trees)
    - [Binary Search Trees](#binary-search-trees)
  - [Balanced Trees](#balanced-trees)
    - [Heap](#heap)
    - [B-Trees](#b-trees)
  - [Graph](#graph)
    - [Graph Implementations](#graph-implementations)
      - [Adjacency Matrix](#adjacency-matrix)
      - [Linked List](#linked-list)
      - [Set](#set)
    - [Graph Traversals](#graph-traversals)
      - [DFS(using a stack)](#dfsusing-a-stack)
      - [BFS(using a queue)](#bfsusing-a-queue)
    - [Path Algorithn](#path-algorithn)

## Trees
### Binary Search Trees
- 이진 탐색 트리 저장 규칙
  - 규칙 1.<br>
    특정 노드의 Entry값은 그 노드의 왼쪽 서브 트리의 모든 값들 보다 크거나 같다.
  - 규칙 2.<br>
    특정 노드의 Entry값은 그 노드의 오른쪽 서브 트리의 모든 값들 보다 작다.

- 이진 탐색 트리를 활용한 Bag 클래스 구현<br>
  [해당 페이지 참조](https://github.com/junhaeng90/DataStructure/tree/main/Bag/bag6.h)
<br>

## Balanced Trees
### Heap
Heap은 strict weak ordering의 less-than 연산자(<)를 통해 비교가 가능한 노드들로 이루어진 이진 트리이며, 아래 2가지 규칙을 따른다.
- 규칙 1.<br>
  특정 노드의 Entry 값은 자식 노드의 Entry 값보다는 항상 크다.
- 규칙 2.<br>
  Heap은 완전 이진 트리이며, 그렇기 때문에 가장 깊은 레벨을 제외한 모든 레벨은 가능한 많은 노드를 포함하고 있어야한다.
  그리고 가장 깊은 레벨에서 노드들은 왼쪽에서부터 채워져 나간다.

> strict weak ordering 이란? <br>
> 어떤 이항연산 R에 대해서, 다음의 4가지 조건을 만족하면 strict weak ordering을 만족하는 관계라고 할 수 있다. <br>
> 1. 비반사성(irreflexivity): 모든 x에 대해 R(x, x)는 거짓
> 2. 비대칭성(asymmetry): 모든 x, y에 대해 R(x, y)가 참이면 R(y, x)는 거짓
> 3. 추이성(transitivity): 모든 x, y, z에 대해 R(x, y)와 R(y, z)가 참이면 R(x, z)는 참
> 4. 비비교성의 추이성(transitivity of incomparability): 모든 x, y, z에 대해 R(x, y)와 R(y, x)가 거짓이고 R(y, z)와 R(z, y)가 거짓이면 R(x, z)와 R(z, x)는 거짓
<br>

### B-Trees
B-tree는 Unbalanced Tree 문제를 해결하기 위한 하나의 방안이며 이진 트리와 비슷하지만 *2개 이상의 자식 노드를 가질 수 있다*는 점과 각각의 *노드가 한 개 이상의 Entry를 가질 수 있다*는데 차이가 있다.

- B-tree 규칙
  - 규칙 1.<br>
    루트에는 Entry가 하나 이상 있을 수 있으며(자식 노드가 없는 경우에는 Entry가 없을 수도 있음), 루트를 제외한 다른 모든 노드는 최소 MINIMIM개의 Entry를 갖는다.

  - 규칙 2.<br>
    노드가 가질 수 있는 최대 Entry 개수는 MINIMUM의 2배이다.

  - 규칙 3.<br>
    각각의 노드에 있는 Entry들은 작은 값에서부터 큰값으로 정렬된 배열에 저장된다.

  - 규칙 4.<br>
    leaf가 아닌 노드의 subtree 개수는 현재 노드가 가진 Entry의 개수보다 한 개 더 많다.

  - 규칙 5.<br>
    leaf가 아닌 모든 노드에 대하여 (a) 인덱스가 i인 Entry는 해당 노드의 i 번째 subtree의 모든 Entry보다 크고, i+1 번째 subtree의 모든 Entry보다 작다.

  - 규칙 6.<br>
    모든 leaf 노드의 depth는 동일하다.

- B-tree를 활용한 Set 클래스 구현<br>
  [해당 페이지 참조](https://github.com/junhaeng90/DataStructure/tree/main/BalancedTrees/set.h)

<br>

## Graph

### Graph Implementations
#### Adjacency Matrix
![](resources/images/graph_adjacency_matrix.PNG)
인접 행렬은 그래프의 edge들을 true/false라는 값으로 표현하는 정사각형의 격자이다. 만약 그래프가 n개의 vertex들을 포함하고 있다면, 이 인접행렬은 n개의 열과 행을 갖는다. i와 j 2개의 vertex에 대해 vertext i에서 vertex j로 가는 edge가 존재한다면 (i, j) 항목의 값이 true이고, 그렇지 않다면 false이다.<br>

#### Linked List
![](resources/images/graph_linked_list.PNG)

#### Set

### Graph Traversals
![](resources/images/graph_traversal.PNG)
#### DFS(using a stack)

#### BFS(using a queue)

### Path Algorithn