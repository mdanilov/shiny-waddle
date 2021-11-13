#ifndef GUARD_C7CCA087_8695_49EA_A00D_7CACC29E2818
#define GUARD_C7CCA087_8695_49EA_A00D_7CACC29E2818

#include "IRunnable.h"

#include <list>
#include <memory>
#include <mutex>
#include <thread>

namespace executor {

/**
 * \brief Responsible for runnables execution and thread management.
 *
 */
class Runner {
public:
  Runner() : _running(false) {}

  /**
   * \brief Add new runnable to the list of the runnables that will be executed
   * by calling the runAll method.
   *
   * @param runnable pointer to the runnable object
   */
  void addRunnable(std::shared_ptr<IRunnable> runnable) {
    _runnables.push_back(runnable);
  }

  /**
   * \brief Executes all runnables in parallel. New thread is created for each
   * runnable. Change the state to the running.
   *
   */
  void runAll();

  /**
   * \brief Wait until all runnables are finished their execution. Basically
   * joins on created threads. The state switched to not running at the end.
   *
   */
  void waitAllFinished();

  /**
   * \brief Returns current state
   *
   * @return true already running
   * @return false not running
   */
  bool isRunning() { return _running; }

private:
  std::list<std::shared_ptr<IRunnable>> _runnables;
  std::list<std::thread> _threads;
  bool _running;
};
} // namespace executor

#endif /* GUARD_C7CCA087_8695_49EA_A00D_7CACC29E2818 */
