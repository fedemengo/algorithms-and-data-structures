# Linked List

## Single Linked List

Usual implementaion with a single pointer to the next node. Implementation of **iterators** and index operator **[]**.

### Operations

- `push_back` - O(1)
- `push_front` - O(1)
- `pop_back` - O(1)
- `pop_front` - O(1)
- `insert(index, elem)` - O(N)
- `remove(index)` - O(N) 
- `find(elem)` - O(N)

## Doubly Linked List

Usual implementaion with pointers to the next and previous node. Implementation of **iterators** and index operator **[]**.

### Operations

- `push_back` - O(1)
- `push_front` - O(1)
- `pop_back` - O(1)
- `pop_front` - O(1)
- `insert(index, elem)` - O(N)
- `remove(index)` - O(N) 
- `find(elem)` - O(N)

## Xor List

Implementaion with a single pointer that holds the value `prevNode ^ nextNode`. Implementation of **iterators**. 

### Operations

- `push_back` - O(1)
- `push_front` - O(1)
- `pop_back` - O(1)
- `pop_front` - O(1)
- `swap` - O(1)

