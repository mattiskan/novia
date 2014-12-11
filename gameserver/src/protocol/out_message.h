//-*-c++-*-
#ifndef NOVIA_OUT_MESSAGE_H
#define NOVIA_OUT_MESSAGE_H

#include <jsoncpp/json.h>

namespace novia {

  class OutMessage {
  public:

    /**
     * Returns a Json::Value containing a message to be sent.
     */
    virtual const Json::Value get_message() = 0;
  };
}

#endif
