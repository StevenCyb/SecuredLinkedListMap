# Secured Linked List Map
The `SecuredLinkedList` is a library that provides the functionality of a Hashmap, without using hash.
Basically it is a linked list with key referencing.
A small demo is given in `demo.ino`. A detailed description of the functions can be found below.
# Functions
[SecuredLinkedListMap()](#SecuredLinkedListMap)
[void put(T1 key, T2 value)](#put)
[bool has(T1 key)](#has)
[void getAll(SecuredLinkedListMapElement<T1, T2>* copies)](#getAll)
[T2 get(T1 key)](#get)
[void remove(T1 key)](#remove)
[int size()](#size)
[void clear()](#clear)
<a name="SecuredLinkedListMap"></a>
## SecuredLinkedListMap()
The `SecuredLinkedListMap` can be instantiated as follows.
```
SecuredLinkedListMap<String, String> mapA = SecuredLinkedListMap<String, String>();
SecuredLinkedListMap<int, int> *mapB = new SecuredLinkedListMap<int, int>();
```
<a name="put"></a>
## void put(T1 key, T2 value)
Put a new key-value pair.
```
mapA.put("test", "hallo");
mapB->put(1, -1);
```
<a name="has"></a>
## bool has(T1 key)
Check whether the key exists.
```
Serial.println(mapA.has("hallo"));
Serial.println(mapB->has(-12));
```
<a name="getAll"></a>
## void getAll(SecuredLinkedListMapElement<T1, T2>* copies)
Get a copy of all the elements in the map.
```
SecuredLinkedListMapElement<String, String> mapAcopy[mapA.size()];
mapA.getAll(mapAcopy);

SecuredLinkedListMapElement<int, int> mapBcopy[mapB->size()];
mapB->getAll(mapBcopy);
```
<a name="get"></a>
## T2 get(T1 key)
Get element by the key.
```
Serial.println(mapA.get("test"));
Serial.println(mapB->get(1));
```
<a name="remove"></a>
## void remove(T1 key)
Remove element with key.
```
mapA.remove("test");
mapB->remove(1);
```
<a name="size"></a>
## int size()
Returns the number of elements in map.
```
Serial.println(mapA.size());
Serial.println(mapB->size());
```
<a name="clear"></a>
## void clear() 
Deletes all items from the list map.
```
mapA.clear();
mapB->clear();
```