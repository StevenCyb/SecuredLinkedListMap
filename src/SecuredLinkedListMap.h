// Created by Steven Cybinski
// GitHub: https://github.com/StevenCyb/SecuredLinkedListMap

#ifndef SecuredLinkedListMap_h
#define SecuredLinkedListMap_h
#endif
#include <mutex>

template<typename T1, typename T2> 
struct SecuredLinkedListMapNode {
	T1 key;
	T2 value;
	SecuredLinkedListMapNode<T1, T2> *next;
};
template<typename T1, typename T2> 
struct SecuredLinkedListMapElement {
	T1 key;
	T2 value;
};

template<typename T1, typename T2> 
class SecuredLinkedListMap {
	private:
		std::mutex *mtx;
		int bucketSize;
		SecuredLinkedListMapNode<T1, T2> *bucketRoot;
		virtual int sizeUnsecured();
		virtual void putUnsecured(T1 key, T2 value);
		virtual bool hasUnsecured(T1 key);
		virtual void getAllUnsecured(SecuredLinkedListMapElement<T1, T2>* copies);
		virtual T2 getUnsecured(T1 key);
		virtual void removeUnsecured(T1 key);
		virtual void clearUnsecured();
	public:
		SecuredLinkedListMap(void);
		~SecuredLinkedListMap(void);
		virtual int size();
		virtual void put(T1 key, T2 value);
		virtual bool has(T1 key);
		virtual void getAll(SecuredLinkedListMapElement<T1, T2>* copies);
		virtual T2 get(T1 key);
		virtual void remove(T1 key);
		virtual void clear();
};

template<typename T1, typename T2> 
SecuredLinkedListMap<T1, T2>::SecuredLinkedListMap() {
	bucketSize = 0;
	mtx = new std::mutex();
}

template<typename T1, typename T2> 
SecuredLinkedListMap<T1, T2>::~SecuredLinkedListMap() {
	bucketSize = 0;
	delete mtx;
	delete bucketRoot;
}

template<typename T1, typename T2> 
int SecuredLinkedListMap<T1, T2>::size() {
	std::lock_guard<std::mutex> locker (*mtx);
	return sizeUnsecured();
}
template<typename T1, typename T2> 
int SecuredLinkedListMap<T1, T2>::sizeUnsecured() {
	return bucketSize;
}

template<typename T1, typename T2> 
void SecuredLinkedListMap<T1, T2>::put(T1 key, T2 value) {
	std::lock_guard<std::mutex> locker (*mtx);
	putUnsecured(key, value);
}
template<typename T1, typename T2> 
void SecuredLinkedListMap<T1, T2>::putUnsecured(T1 key, T2 value) {
	if(bucketSize <= 0) {
		SecuredLinkedListMapNode<T1, T2> *cache = new SecuredLinkedListMapNode<T1, T2>();
		cache->key = key;
		cache->value = value;
		bucketRoot = cache;
		bucketSize += 1;
	} else {
		SecuredLinkedListMapNode<T1, T2> *current = bucketRoot;
		if(current->key == key) {
			current->value = value;
			return;
		}
		while(current->next != NULL) {
			current = current->next;
			if(current->key == key) {
				current->value = value;
				return;
			}
		}
		SecuredLinkedListMapNode<T1, T2> *cache = new SecuredLinkedListMapNode<T1, T2>();
		cache->key = key;
		cache->value = value;
		current->next = cache;
		bucketSize += 1;
	}
}

template<typename T1, typename T2> 
bool SecuredLinkedListMap<T1, T2>::has(T1 key) {
	std::lock_guard<std::mutex> locker (*mtx);
	return hasUnsecured(key);
}
template<typename T1, typename T2> 
bool SecuredLinkedListMap<T1, T2>::hasUnsecured(T1 key) {
	SecuredLinkedListMapNode<T1, T2> *current = bucketRoot;
	while(current != NULL) {
		if(current->key == key) {
			return true;
		}
		current = current->next;
	}
	return false;
}

template<typename T1, typename T2> 
void SecuredLinkedListMap<T1, T2>::getAll(SecuredLinkedListMapElement<T1, T2>* copies) {
	std::lock_guard<std::mutex> locker (*mtx);
	getAllUnsecured(copies);
}
template<typename T1, typename T2> 
void SecuredLinkedListMap<T1, T2>::getAllUnsecured(SecuredLinkedListMapElement<T1, T2>* copies) {
	int counter = 0;
	SecuredLinkedListMapNode<T1, T2> *current = bucketRoot;
	while(current != NULL) {
		SecuredLinkedListMapElement<T1, T2> copy = SecuredLinkedListMapElement<T1, T2>();
		copy.key = current->key;
		copy.value = current->value;
		copies[counter] = copy;
		current = current->next;
		counter ++;
	}
}

template<typename T1, typename T2> 
T2 SecuredLinkedListMap<T1, T2>::get(T1 key) {
	std::lock_guard<std::mutex> locker (*mtx);
	return getUnsecured(key);
}
template<typename T1, typename T2> 
T2 SecuredLinkedListMap<T1, T2>::getUnsecured(T1 key) {
	SecuredLinkedListMapNode<T1, T2> *current = bucketRoot;
	if(current->key == key) {
		return current->value;
	}
	while(current->next != NULL) {
		current = current->next;
		if(current->key == key) {
			return current->value;
		}
	}
	return T2();
}

template<typename T1, typename T2> 
void SecuredLinkedListMap<T1, T2>::remove(T1 key) {
	std::lock_guard<std::mutex> locker (*mtx);
	removeUnsecured(key);
}
template<typename T1, typename T2> 
void SecuredLinkedListMap<T1, T2>::removeUnsecured(T1 key) {
	SecuredLinkedListMapNode<T1, T2> *current = bucketRoot;
	if(current->key == key) {
		bucketRoot = current->next;
		bucketSize -= 1;
		return;
	}
	while(current->next != NULL) {
		if(current->next->key == key) {
			current->next = current->next->next;
			bucketSize -= 1;
			return;
		}
		current = current->next;
	}
}

template<typename T1, typename T2> 
void SecuredLinkedListMap<T1, T2>::clear() {
	std::lock_guard<std::mutex> locker (*mtx);
	clearUnsecured();
}
template<typename T1, typename T2> 
void SecuredLinkedListMap<T1, T2>::clearUnsecured() {
	while(bucketRoot != NULL) {
		bucketRoot = bucketRoot->next;
	}
	bucketSize = 0;
}