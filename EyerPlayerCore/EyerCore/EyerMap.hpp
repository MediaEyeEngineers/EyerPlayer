#ifndef	EYER_MAP_H
#define	EYER_MAP_H
#include "EyerMapEle.hpp"

namespace Eyer {

	template<typename K, typename V>
	class EyerMap
	{	
	public:
		EyerMap();
		~EyerMap();
		int insert(const K& key, const V& value);
		int find(const K& key, V & value) const;
		int circleEle(EyerMapEle<K, V>* ele, const K& key, V& value, int& flag) const;
		int getSize() const;
		int clear();

		EyerMapEle<K, V>* head;

	private:
		int size = 0;
        int insertInner(const K & key, const V & value, EyerMapEle<K,V> * & ele);
		int clearInner(EyerMapEle<K, V> * & ele);

	};

	template<typename K, typename V>
	int EyerMap<K, V>::insertInner(const K& key, const V& value, EyerMapEle<K, V> * & ele)
	{
		if (size == 0) {
			head->key = key;
			head->value = value;
			size++;
			return 0;
		}

		if (nullptr == ele) {
			ele = new EyerMapEle<K, V>(key, value);
			size++;
		}else if (key > ele->key) {
			insertInner(key, value, ele->rightMapEle);
		}else if (key < ele->key) {
			insertInner(key, value, ele->leftMapEle);
		}
	}


	template<typename K, typename V>
	EyerMap<K, V>::EyerMap()
	{
		head = new EyerMapEle<K, V>(0, 0);
	}

	template<typename K, typename V>
	EyerMap<K, V>::~EyerMap()
	{
		clearInner(head);
	}

	template<typename K, typename V>
	int EyerMap<K, V>::getSize() const
	{
		return size;
	}

	template<typename K, typename V>
	int EyerMap<K, V>::circleEle(EyerMapEle<K, V>* ele, const K& key, V& value, int & flag) const
	{
		if (nullptr != ele) {
			//printf("key:%d,vaule:%d \n", ele->key, ele->value);
			if (key == ele->key) {
				value = ele->value;
				flag = 1;
				return 0;
			}
			circleEle(ele->leftMapEle, key, value, flag);
			circleEle(ele->rightMapEle, key, value, flag);
		}
		return 0;
	}

	template<typename K, typename V>
	int EyerMap<K, V>::insert(const K& key, const V& value)
	{
		return insertInner(key, value, head);
	}

	template<typename K, typename V>
	int EyerMap<K, V>::find(const K& key, V& value) const
	{
		int flag = 0;
		circleEle(head, key, value, flag);
		if (flag) {
			return 0;
		}else{
			return -1;
		}
	}

	template<typename K, typename V>
	int EyerMap<K, V>::clearInner(EyerMapEle<K, V> * & ele)
	{
		if (nullptr != ele) {
			clearInner(ele->leftMapEle);
			clearInner(ele->rightMapEle);
			//printf("clear-----key:%d,vaule:%d \n", ele->key, ele->value);
			delete ele;
			ele = nullptr;
			size--;
		}
		return 0;
	}

	template<typename K, typename V>
	int EyerMap<K, V>::clear()
	{
		if(size == 0){
			return 0;
		}
		clearInner(head);
		if (nullptr == head) {
			head = new EyerMapEle<K, V>(0, 0);
		}
		return 0;
	}
}

#endif