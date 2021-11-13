#include <gtest/gtest.h>

#include "RunnableMock.h"
#include "Runner.h"

#include <memory>

namespace executor {

TEST(RunnerTest, basic) {
    auto runnable1 = std::make_shared<RunnableMock>();
    auto runnable2 = std::make_shared<RunnableMock>();
    Runner runner;
    runner.addRunnable(runnable1);
    runner.addRunnable(runnable2);
    EXPECT_CALL(*runnable1, execute()).Times(1);
    EXPECT_CALL(*runnable2, execute()).Times(1);
    runner.runAll();
    runner.waitAllFinished();
}
} // namespace executor
