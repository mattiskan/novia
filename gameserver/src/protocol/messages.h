//-*-c++-*-
#ifndef NOVIA_MESSAGES_H
#define NOVIA_MESSAGES_H

#include <string>
#include "in_message.h"

namespace novia {
  namespace messages {

    InMessage* in_message(std::string payload);
  }
}
#endif
