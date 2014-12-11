//-*-c++-*-
#ifndef NOVIA_IN_MESSAGE_H
#define NOVIA_IN_MESSAGE_H

namespace novia {

  class InMessage {

  public:
    InMessage(const Json::Value& data) {
      read(data);
    }

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
    virtual const OutMessage instant_reply(const Map& map) const = 0;

    /**
     * Called by the server thread, this is where messages that change the
     * game are expected do do so, using map-controller.
     */
    virtual void modify_map(Map& map) const = 0;

  };
}

#endif
