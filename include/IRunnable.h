#ifndef GUARD_D385B242_0502_480C_BB25_C47EB741DA20
#define GUARD_D385B242_0502_480C_BB25_C47EB741DA20

namespace executor {

/**
 * \brief Simple runnable interface. The class has to implement this interafce
 * if wants to be added as runnable to the Runner.
 *
 */
class IRunnable {
public:
  /**
   * \brief Can be called by the runner when scheduled
   *
   */
  virtual void execute() = 0;
};
} // namespace executor

#endif /* GUARD_D385B242_0502_480C_BB25_C47EB741DA20 */
