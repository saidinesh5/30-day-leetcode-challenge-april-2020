#pragma once

/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/

class LRUCache {
    struct Bucket {
        // Bucket owns the next bucket and links to the previous bucket
        int key, value;
        Bucket *next;
        Bucket *prev;

        Bucket(): next(nullptr), prev(nullptr) { }
        Bucket(int k, int v): key(k), value(v), next(nullptr), prev(nullptr) { }
    };

    std::vector<Bucket> mBuckets;
    std::unordered_map<int, Bucket*> mIndex;
    Bucket *mHead;
    Bucket *mTail;
    int mCapacity;
    int mCount;

    void moveToFront(Bucket* bucket) {
        if (mHead == bucket) {
            return;
        }

        if (bucket->prev) {
            bucket->prev->next = bucket->next;
        }

        if (bucket->next) {
            bucket->next->prev = bucket->prev;
        }

        if (mTail == bucket) {
            mTail = bucket->prev ? bucket->prev
                                 : bucket;
            mTail->next = nullptr;
        }

        bucket->next = mHead;
        bucket->next->prev = bucket;
        bucket->prev = nullptr;

        mHead = bucket;
    }


public:
    LRUCache(int capacity):
      mBuckets(capacity),
      mCapacity(capacity),
      mCount(0),
      mHead(nullptr),
      mTail(nullptr){
        __builtin_prefetch(&(mBuckets[0]), 0, 3);
      }

    int get(int key) {
        auto it = mIndex.find(key);

        if (it == mIndex.end()) {
            return -1;
        }

        moveToFront(it->second);
        return it->second->value;
    }

    void put(int key, int value) {
        if (mCapacity < 1) {
            return;
        }

        auto it = mIndex.find(key);

        // If key not found in the index, insert a new key
        if (it == mIndex.end()) {
            // By replacing the last element
            if (mCount == mCapacity)  {
                auto bucketIt = mIndex.find(mTail->key);
                auto bucket = bucketIt->second;
                mIndex.erase(bucketIt);
                bucket->key = key;
                bucket->value = value;
                mIndex[key] = bucket;
                moveToFront(bucket);
            } else {
                // Or inserting a fresh one
                auto bucket = &(mBuckets[mCount]);
                bucket->key = key;
                bucket->value = value;
                mIndex[key] = bucket;
                bucket->next = mHead;
                mHead = bucket;

                if (bucket->next) {
                    bucket->next->prev = bucket;
                }

                if (mCount == 0) {
                    mTail = bucket;
                }

                mCount++;
            }

        } else {
            it->second->value = value;
            moveToFront(it->second);
        }
    }
};
