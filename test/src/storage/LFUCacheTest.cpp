#include <gtest/gtest.h>

#include "storage/LFUCache.h"
#include "storage/StorageMock.h"

using namespace ::testing;

namespace storage {

TEST(LFUCacheTest, read) {
  static const uint32_t CACHE_SIZE = 3;
  StorageMock storageMock;
  LFUCache cache(storageMock, CACHE_SIZE);

  EXPECT_CALL(storageMock, readByIndex(_))
      .WillRepeatedly(Return(ReadResult{"test", true}));
  for (size_t i = 0; i < 15; ++i) {
    cache.readByIndex(1);
  }
  for (size_t i = 0; i < 10; ++i) {
    cache.readByIndex(2);
  }
  for (size_t i = 0; i < 5; ++i) {
    cache.readByIndex(3);
  }

  ReadResult result = cache.readByIndex(4);
  EXPECT_EQ(result.value, "test");
  EXPECT_EQ(result.cache_miss, true);

  result = cache.readByIndex(4);
  EXPECT_EQ(result.value, "test");
  EXPECT_EQ(result.cache_miss, false);

  for (size_t i = 0; i < 20; ++i) {
    cache.readByIndex(4);
  }

  result = cache.readByIndex(4);
  EXPECT_EQ(result.value, "test");
  EXPECT_EQ(result.cache_miss, false);

  result = cache.readByIndex(3);
  EXPECT_EQ(result.value, "test");
  EXPECT_EQ(result.cache_miss, true);

  result = cache.readByIndex(3);
  EXPECT_EQ(result.value, "test");
  EXPECT_EQ(result.cache_miss, false);

  for (size_t i = 0; i < 20; ++i) {
    cache.readByIndex(3);
  }

  result = cache.readByIndex(4);
  EXPECT_EQ(result.value, "test");
  EXPECT_EQ(result.cache_miss, false);

  result = cache.readByIndex(3);
  EXPECT_EQ(result.value, "test");
  EXPECT_EQ(result.cache_miss, false);

  result = cache.readByIndex(2);
  EXPECT_EQ(result.value, "test");
  EXPECT_EQ(result.cache_miss, true);
}

TEST(LFUCacheTest, write) {
  static const uint32_t CACHE_SIZE = 3;
  StorageMock storageMock;
  LFUCache cache(storageMock, CACHE_SIZE);

  EXPECT_CALL(storageMock, writeByIndex(1, "100")).Times(1);
  cache.writeByIndex(1, "100");
}

TEST(LFUCacheTest, write_and_read) {
  static const uint32_t CACHE_SIZE = 3;
  StorageMock storageMock;
  LFUCache cache(storageMock, CACHE_SIZE);

  EXPECT_CALL(storageMock, readByIndex(1))
      .WillOnce(Return(ReadResult{"1", true}));
  ReadResult result = cache.readByIndex(1);
  EXPECT_EQ(result.value, "1");
  EXPECT_EQ(result.cache_miss, true);

  EXPECT_CALL(storageMock, writeByIndex(1, "100")).Times(1);
  cache.writeByIndex(1, "100");

  EXPECT_CALL(storageMock, readByIndex(_)).Times(0);
  result = cache.readByIndex(1);
  EXPECT_EQ(result.value, "100");
  EXPECT_EQ(result.cache_miss, false);
}
} // namespace storage
