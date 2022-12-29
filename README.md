# ft_containers

## 과제 설명
- C++ Standard Template Library내에 있는 Vector, Stack, Map, Set, Iterator등에 대해서 C++언어로 직접 구현.

## 주요 구현 내용
### Vector
- Vector의 경우 Capacity가 자동적으로 힙 메모리 재할당을 통해 조절 되는 동적 배열.
- 최상 index에서 insert, delete시 시간복잡도를 Amortization Cost O(1)으로 하기 위해 
메모리 재할당 이 발생하면 메모리 공간이 부족하면 기본적으로 2배로 크기를 늘림.
- 선형적으로 크기를 늘릴 경우 재할당이 빈번하게 발생하여 수학적으로 최상 index에서 insert, delete가 O(1)이 되지 못함.

### Map, Set
- Tree 자료 구조로 Key의 크기에 따라 정렬되어 인접한 노드에 저장됨.
- Insert, Delete, 조회 시 모두 트리의 깊이에 비례한 시간 복잡도를 가짐. 균형 트리라면 O(logn)
- 기본적으로 Binary Search Tree는 균형이 맞지 않을 수 있기 때문에 이를 해결하기 위해 AVL Tree, Red-Black-Tree, B트리등을 고려
- 최종적으로 프로그래밍 언어에서는 주로 Red-Black-Tree구현이 많기 때문에 이를 선택함으로서 O(logn)의 시간복잡도로 구현할 수 있었음.
[Red-Black-Tree개념 정리](https://velog.io/@xogml951/Red-Black-Tree-%EA%B5%AC%ED%98%84)
