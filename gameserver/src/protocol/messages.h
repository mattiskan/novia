//-*-c++-*-
#ifndef NOVIA_MESSAGES_H
#define NOVIA_MESSAGES_H

#include <string>
#include "in_message.h"

namespace novia {
  namespace messages {

    std::shared_ptr<InMessage> in_message(const std::string& payload);
  }
}
#endif
