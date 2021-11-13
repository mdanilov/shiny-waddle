#include <gtest/gtest.h>

#include "storage/LRUCache.h"
#include "storage/StorageMock.h"

using namespace ::testing;

namespace storage {

TEST(LRUCacheTest, read) {
  static const uint32_t CACHE_SIZE = 3;
  StorageMock storageMock;
  LRUCache cache(storageMock, CACHE_SIZE);

  EXPECT_CALL(storageMock, readByIndex(1))
      .WillOnce(Return(ReadResult{"1", true}));
  ReadResult result = cache.readByIndex(1);
  EXPECT_EQ(result.value, "1");
  EXPECT_EQ(result.cache_miss, true);

  EXPECT_CALL(storageMock, readByIndex(_)).Times(0);
  result = cache.readByIndex(1);
  EXPECT_EQ(result.value, "1");
  EXPECT_EQ(result.cache_miss, false);

  EXPECT_CALL(storageMock, readByIndex(2))
      .WillOnce(Return(ReadResult{"2", true}));
  result = cache.readByIndex(2);
  EXPECT_EQ(result.value, "2");
  EXPECT_EQ(result.cache_miss, true);

  EXPECT_CALL(storageMock, readByIndex(_)).Times(0);
  result = cache.readByIndex(2);
  EXPECT_EQ(result.value, "2");
  EXPECT_EQ(result.cache_miss, false);

  EXPECT_CALL(storageMock, readByIndex(3))
      .WillOnce(Return(ReadResult{"3", true}));
  result = cache.readByIndex(3);
  EXPECT_EQ(result.value, "3");
  EXPECT_EQ(result.cache_miss, true);

  EXPECT_CALL(storageMock, readByIndex(_)).Times(0);
  result = cache.readByIndex(3);
  EXPECT_EQ(result.value, "3");
  EXPECT_EQ(result.cache_miss, false);

  EXPECT_CALL(storageMock, readByIndex(_)).Times(0);
  result = cache.readByIndex(2);
  EXPECT_EQ(result.value, "2");
  EXPECT_EQ(result.cache_miss, false);

  EXPECT_CALL(storageMock, readByIndex(4))
      .WillOnce(Return(ReadResult{"4", true}));
  result = cache.readByIndex(4);
  EXPECT_EQ(result.value, "4");
  EXPECT_EQ(result.cache_miss, true);

  EXPECT_CALL(storageMock, readByIndex(_)).Times(0);
  result = cache.readByIndex(4);
  EXPECT_EQ(result.value, "4");
  EXPECT_EQ(result.cache_miss, false);

  EXPECT_CALL(storageMock, readByIndex(1))
      .WillOnce(Return(ReadResult{"1", true}));
  result = cache.readByIndex(1);
  EXPECT_EQ(result.value, "1");
  EXPECT_EQ(result.cache_miss, true);
}

TEST(LRUCacheTest, write) {
  static const uint32_t CACHE_SIZE = 3;
  StorageMock storageMock;
  LRUCache cache(storageMock, CACHE_SIZE);

  EXPECT_CALL(storageMock, writeByIndex(1, "100")).Times(1);
  cache.writeByIndex(1, "100");
}

TEST(LRUCacheTest, write_and_read) {
  static const uint32_t CACHE_SIZE = 3;
  StorageMock storageMock;
  LRUCache cache(storageMock, CACHE_SIZE);

  EXPECT_CALL(storageMock, writeByIndex(1, "100")).Times(1);
  cache.writeByIndex(1, "100");

  EXPECT_CALL(storageMock, readByIndex(_)).Times(0);
  ReadResult result = cache.readByIndex(1);
  EXPECT_EQ(result.value, "100");
  EXPECT_EQ(result.cache_miss, false);
}
} // namespace storage
