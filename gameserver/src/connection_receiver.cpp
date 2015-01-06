#include "connection_receiver.h"

namespace novia {

  ConnectionReceiver::ConnectionReceiver()
    : next_unassigned_id_(0) {
    
  }

  void ConnectionReceiver::initiate(){
    socket_server_.set_message_handler(bind(&ConnectionReceiver::on_message, this, ::_1, ::_2));
    socket_server_.set_open_handler(bind(&ConnectionReceiver::on_connect, this, ::_1));

    socket_server_.set_fail_handler(bind(&ConnectionReceiver::on_fail, this, ::_1));

    socket_server_.set_close_handler(bind(&ConnectionReceiver::on_close, this, ::_1));

  
    socket_server_.init_asio();
    socket_server_.listen(9002);
    socket_server_.start_accept();

    acceptor_thread_ptr_ = new std::thread(std::bind(&WebsocketServer::run, &socket_server_));
  }

  void ConnectionReceiver::terminate(){
    socket_server_.stop();
    acceptor_thread_ptr_->join();
  }


  int ConnectionReceiver::connected_client_count() const {
    return clients.size();
  }


  void ConnectionReceiver::broadcast(std::string msg){
    for(auto session : sessions_)
      send_to(session.first, msg);
  }

  void ConnectionReceiver::send_to(int session_id, const std::string& msg){
    auto hdl = sessions_[session_id];
    socket_server_.send(hdl, msg, websocketpp::frame::opcode::text);
  }
  

  TaskQueue& ConnectionReceiver::task_queue_ref() {
    return controllers_.task_queue;
  }

  
  /*
   * Note: The below event mathods will be executed on acceptor_thread.
   * This means that all methods called from these methods must be
   * independent of acceptor_thread to avoid deadlocks.
   */
  void ConnectionReceiver::on_connect(websocketpp::connection_hdl hdl){
    int id = next_unassigned_id_++;
    std::cout << "Client "<< id << " connected." << std::endl;

    ClientConnection::SendFn send_fn = std::bind(&ConnectionReceiver::send_to, this, ::_1, ::_2);
    clients[hdl] = new ClientConnection(id, send_fn);
    sessions_[id] = hdl;
  }

  void ConnectionReceiver::on_message(websocketpp::connection_hdl hdl, WebsocketServer::message_ptr msg){

    ClientConnection& client = *clients.find(hdl)->second;

    std::cout << "Client"<< client.session_id() <<" sent: \""<< msg->get_payload() <<'"'<< std::endl;

    client.interpret_msg(msg->get_payload());
  }


  void ConnectionReceiver::on_fail(websocketpp::connection_hdl hdl){
    std::cout << "failed!!" << std::endl;
    on_close(hdl);
  }

  void ConnectionReceiver::on_close(websocketpp::connection_hdl hdl){
    ClientConnection* client = clients.find(hdl)->second;
    std::cout << "closed: " << client->session_id() << std::endl;
    clients.erase(hdl);
    delete client;
  }

}
