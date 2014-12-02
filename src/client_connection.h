#ifndef NOVIA_CLIENT_CONNECTION_H
#define NOVIA_CLIENT_CONNECTION_H

#include <string>

namespace Novia {

  class ClientConnection {
  public:
    const int session_id_;

    ClientConnection(int assigned_id);

    void interpret_msg(std::string payload);
  };

}

#endif
 
