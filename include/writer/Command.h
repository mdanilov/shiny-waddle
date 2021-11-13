#ifndef GUARD_E84EACA0_883E_4EFA_92BC_0D7EC4CB5FBB
#define GUARD_E84EACA0_883E_4EFA_92BC_0D7EC4CB5FBB

#include <cstdint>
#include <string>

namespace writer {
/**
 * \brief Writer command. Contains instructions for the writer.
 *
 */
struct Command {
  uint32_t index;
  std::string value;
};
} // namespace writer

#endif /* GUARD_E84EACA0_883E_4EFA_92BC_0D7EC4CB5FBB */
