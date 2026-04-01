#include <Cache/LRUCache.h>
#include <gtest/gtest.h>

TEST(LRUCacheTest, BasicPutGet) {
		LRUCache<int, int> lru(2);

		lru.put(1, 1);
		EXPECT_EQ(lru.get(1), 1);

		EXPECT_EQ(lru.get(2), std::nullopt);
}

TEST(LRUCacheTest, EvictsLRU) {
		LRUCache<int, int> lru(2);

		lru.put(1, 1);
		lru.put(2, 2);
		lru.put(3, 3);

		EXPECT_EQ(lru.get(1), std::nullopt);
		EXPECT_EQ(lru.get(2), 2);
		EXPECT_EQ(lru.get(3), 3);
}

TEST(LRUCacheTest, GetUpdatesRecency) {
		LRUCache<int, int> lru(2);

		lru.put(1, 1);
		lru.put(2, 2);

		lru.get(1);       // 1 becomes most recently used
		lru.put(3, 3);    // should evict key 2

		EXPECT_EQ(lru.get(2), std::nullopt);
		EXPECT_EQ(lru.get(1), 1);
}

TEST(LRUCacheTest, PutUpdatesExistingKey) {
		LRUCache<int, int> lru(2);

		lru.put(1, 1);
		lru.put(1, 10);

		EXPECT_EQ(lru.get(1), 10);
}
TEST(LRUCacheTest, UpdateRefreshesRecency) {
		LRUCache<int, int> lru(2);

		lru.put(1, 1);
		lru.put(2, 2);

		lru.put(1, 10);   // should move 1 to MRU
		lru.put(3, 3);    // should evict key 2

		EXPECT_EQ(lru.get(2), std::nullopt);
		EXPECT_EQ(lru.get(1), 10);
}

TEST(LRUCacheTest, CapacityOne) {
		LRUCache<int, int> lru(1);

		lru.put(1, 1);
		lru.put(2, 2); // evicts 1

		EXPECT_EQ(lru.get(1), std::nullopt);
		EXPECT_EQ(lru.get(2), 2);
}

TEST(LRUCacheTest, SameValueDifferentKeys) {
		LRUCache<int, int> lru(2);

		lru.put(1, 100);
		lru.put(2, 100);

		lru.put(3, 300); // should evict key 1

		EXPECT_EQ(lru.get(1), std::nullopt);
		EXPECT_EQ(lru.get(2), 100);
}
TEST(LRUCacheTest, ComplexSequence) {
		LRUCache<int, int> lru(2);

		lru.put(1, 1);
		lru.put(2, 2);
		EXPECT_EQ(lru.get(1), 1);

		lru.put(3, 3); // evict 2
		EXPECT_EQ(lru.get(2), std::nullopt);

		lru.put(4, 4); // evict 1
		EXPECT_EQ(lru.get(1), std::nullopt);
		EXPECT_EQ(lru.get(3), 3);
		EXPECT_EQ(lru.get(4), 4);
}

