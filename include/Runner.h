#ifndef GUARD_C7CCA087_8695_49EA_A00D_7CACC29E2818
#define GUARD_C7CCA087_8695_49EA_A00D_7CACC29E2818

#include "IRunnable.h"

#include <list>
#include <memory>
#include <mutex>
#include <thread>

namespace executor {

class Runner {
public:
  Runner() : _running(false) {}

  void addRunnable(std::shared_ptr<IRunnable> runnable) {
    _runnables.push_back(runnable);
  }

  void runAll();

  void waitAllFinished();

  bool isRunning() { return _running; }

private:
  std::list<std::shared_ptr<IRunnable>> _runnables;
  std::list<std::thread> _threads;
  bool _running;
};
} // namespace executor

#endif /* GUARD_C7CCA087_8695_49EA_A00D_7CACC29E2818 */
