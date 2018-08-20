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
- `insert(index, elem)` - O(N)
- `remove(index)` - O(N) 
- `find(elem)` - O(N)

## Skip List
![skip list](https://upload.wikimedia.org/wikipedia/commons/thumb/2/2c/Skip_list_add_element-en.gif/800px-Skip_list_add_element-en.gif)

Implementation with fixed number of levels, currently `MAX_LEVEL = 16`. In general the structure is suitable for storing `2^MAX_LEVEL` items. Implementation of **iterators** and index operator **[]**. A comparison function passed to the constructor determine the relative order between elements.

### Operations

- `insert` - O(log N)
- `remove` - O(log N)
- `remove_at(index)` - O(log N)
- `find` - O(log N)
- `top` - O(1)
- `operator[]` - O(log N)

