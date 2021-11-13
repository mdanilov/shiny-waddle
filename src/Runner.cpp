#include "Runner.h"

namespace executor {

void Runner::runAll() {
  if (_running) {
    return;
  }

  _running = true;
  for (auto it = _runnables.begin(); it != _runnables.end(); ++it) {
    auto t = std::thread(&IRunnable::execute, *it);
    _threads.push_back(std::move(t));
  }
}

void Runner::waitAllFinished() {
  for (auto it = _threads.begin(); it != _threads.end(); ++it) {
    it->join();
  }
  _running = false;
}

} // namespace executor
