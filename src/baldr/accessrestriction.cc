#include "baldr/accessrestriction.h"
#include <string.h>

namespace valhalla {
namespace baldr {

// Constructor with arguments
AccessRestriction::AccessRestriction(const uint32_t edgeindex,
                                     const AccessType type,
                                     const uint32_t modes,
                                     const uint32_t lanes,
                                     const uint64_t value)
    : edgeindex_(edgeindex), type_(static_cast<uint32_t>(type)), modes_(modes), lanes_(lanes),
      value_(value), spare_(0) {
}

// Get the internal edge Id.
uint32_t AccessRestriction::edgeindex() const {
  return edgeindex_;
}

// Set the internal edge index to which this access restriction applies.
void AccessRestriction::set_edgeindex(const uint32_t edgeindex) {
  edgeindex_ = edgeindex;
}

// Get the type
AccessType AccessRestriction::type() const {
  return static_cast<AccessType>(type_);
}

// Get the modes impacted by access restriction.
uint32_t AccessRestriction::modes() const {
  return modes_;
}

// Get the lames impacted by access restriction.
uint32_t AccessRestriction::lanes() const {
  return lanes_;
}

// Get the value
uint64_t AccessRestriction::value() const {
  return value_;
}

// Set the value
void AccessRestriction::set_value(const uint64_t v) {
  value_ = v;
}

// operator < - for sorting. Sort by route Id.
bool AccessRestriction::operator<(const AccessRestriction& other) const {
  if (edgeindex() == other.edgeindex()) {
    if (modes() == other.modes()) {
      if (lanes() == other.lanes()) {
        return value() < other.value();
      } else {
        return lanes() < other.lanes();
      }
    } else {
      return modes() < other.modes();
    }
  } else {
    return edgeindex() < other.edgeindex();
  }
}

} // namespace baldr
} // namespace valhalla
