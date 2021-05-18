# DataStructure
C++로 구현해보는 자료구조🤠

- [DataStructure](#datastructure)
  - [Trees](#trees)
    - [Binary Search Trees](#binary-search-trees)
  - [Balanced Trees](#balanced-trees)
    - [Heap](#heap)
    - [B-Trees](#b-trees)
  - [Graph](#graph)
    - [Graph Traversals](#graph-traversals)
      - [DFS](#dfs)
      - [BFS](#bfs)
    - [Path Algorithn](#path-algorithn)

## Trees
### Binary Search Trees
- 이진 탐색 트리 저장 규칙
  - 규칙 1.<br>
    특정 노드의 Entry값은 그 노드의 왼쪽 서브 트리의 모든 값들 보다 크거나 같다.
  - 규칙 2.<br>
    특정 노드의 Entry값은 그 노드의 오른쪽 서브 트리의 모든 값들 보다 작다.
<br>

## Balanced Trees
### Heap
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

<br>

## Graph

### Graph Traversals
#### DFS
#### BFS

### Path Algorithn