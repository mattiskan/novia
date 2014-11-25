#include "connection_reciever.h"

ConnectionReceiver::ConnectionReceiver()
 : next_unassigned_id_(0) {
}

void ConnectionReceiver::initiate(){
  socket_server_.set_message_handler(bind(&ConnectionReceiver::on_message, this, ::_1, ::_2));
  socket_server_.set_open_handler(bind(&ConnectionReceiver::on_connect, this, ::_1));
  
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
  for(auto client : clients){
    socket_server_.send(client.first, msg, websocketpp::frame::opcode::text);
  }
}


void ConnectionReceiver::on_connect(websocketpp::connection_hdl hdl){
  std::cout << "Client connected." << std::endl;

  clients[hdl] = new ClientConnection(next_unassigned_id_++);
}

void ConnectionReceiver::on_message(websocketpp::connection_hdl hdl, WebsocketServer::message_ptr msg){
  ClientConnection* client_ptr = clients.find(hdl)->second;

  std::cout << "Client"<< client_ptr->session_id_ <<" sent: \""<< msg->get_payload() <<'"'<< std::endl;

  if( msg->get_payload() == "exit")
    terminate();

  client_ptr->interpret_msg(msg->get_payload());
}
