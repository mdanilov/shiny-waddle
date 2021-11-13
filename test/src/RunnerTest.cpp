#include <gtest/gtest.h>

#include "RunnableMock.h"
#include "Runner.h"

#include <chrono>
#include <memory>
#include <thread>

using namespace ::testing;

namespace executor {

TEST(RunnerTest, basic) {
  auto runnable1 = std::make_shared<RunnableMock>();
  auto runnable2 = std::make_shared<RunnableMock>();
  Runner runner;
  runner.addRunnable(runnable1);
  runner.addRunnable(runnable2);
  auto cb = []() { std::this_thread::sleep_for(std::chrono::seconds(1)); };
  EXPECT_CALL(*runnable1, execute()).WillOnce(Invoke(cb));
  EXPECT_CALL(*runnable2, execute()).Times(1);
  runner.runAll();
  EXPECT_EQ(runner.isRunning(), true);
  runner.waitAllFinished();
  EXPECT_EQ(runner.isRunning(), false);
}
} // namespace executor
