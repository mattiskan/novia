#ifndef CLIENT_COMMUNICATOR_H
#define CLIENT_COMMUNICATOR_H
#include <vector>
#include <thread>
#include <array>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/bind.hpp>


using boost::asio::local::stream_protocol;

class ClientCommunicator {

 public:
  stream_protocol::socket socket_;
  //constructors
  ClientCommunicator(boost::asio::io_service&);
  ClientCommunicator(ClientCommunicator&&) = delete;

  void start();
  std::vector<int> getClientActions();

 private:
  std::mutex readLock_;
  std::array<int, 2> readBuffer_;
  std::vector<int> actionQueue_;
  std::thread readThread_;

  void startRead();
  void read(const boost::system::error_code&, std::size_t);
};


#endif
