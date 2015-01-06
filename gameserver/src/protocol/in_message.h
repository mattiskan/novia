//-*-c++-*-
#ifndef NOVIA_IN_MESSAGE_H
#define NOVIA_IN_MESSAGE_H

#include "out_message.h"
#include "../controllers.h"
#include <jsoncpp/json.h>

namespace novia {

  class InMessage {

  public:
    /*
     * Used to copy contents of messages into fields.
     *
     * Throw std::domain_error if message is invalid.
     */
    virtual void read(const Json::Value& data) = 0;

    /**
     * Usable for messages requesting "read only" information.
     *
     * Called right after read(), giving some messages the ability to
     * reply without getting executed on the server thread.
     */
    virtual void instant_reply(const Controllers& c, ClientConnection& owner) const = 0;

    /**
     * Called on server thread, this is where messages that change the game are
     * expected to do so.
     */
    virtual void on_invoke(Controllers& c, ClientConnection& owner) const = 0;

  };
}

#endif
