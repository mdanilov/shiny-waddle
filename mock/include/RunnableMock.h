#ifndef GUARD_C340396A_0702_49E2_8D84_EFB0F098E776
#define GUARD_C340396A_0702_49E2_8D84_EFB0F098E776

#include <gmock/gmock.h>

#include "IRunnable.h"

namespace executor {

class RunnableMock : public IRunnable {
public:
  MOCK_METHOD0(execute, void());
};
} // namespace executor

#endif /* GUARD_C340396A_0702_49E2_8D84_EFB0F098E776 */
