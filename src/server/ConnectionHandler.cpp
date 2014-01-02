#include "ConnectionHandler.h"
#include <boost/foreach.hpp>
//using boost::asio::local::stream_protocol in include

ConnectionHandler::ConnectionHandler(stream_protocol::endpoint ep)
  :acceptor_(ioService_, ep) {
  prepareForNewClient();
}
  
void ConnectionHandler::start() {
  ioServiceThread_ = new std::thread(&ConnectionHandler::run, this);
}

void ConnectionHandler::run(){
  ioService_.run();
}

std::vector<Message> ConnectionHandler::pollClientActions(){
  std::vector<Message> allMsg;
  
  safeAdd_.lock();
  BOOST_FOREACH(ClientCommunicator* client, clients_){
    std::vector<Message> clientActions = client->getClientActions();
    allMsg.insert(allMsg.end(), clientActions.begin(), clientActions.end());
  }
  safeAdd_.unlock();

  return allMsg;
}


void ConnectionHandler::prepareForNewClient(){
  ClientCommunicator* newClient = new ClientCommunicator(ioService_);
  acceptor_.async_accept(newClient->socket_,
			 boost::bind(&ConnectionHandler::acceptClient,
				     this,
				     newClient,
				     boost::asio::placeholders::error)
			 );
}

void ConnectionHandler::acceptClient(ClientCommunicator* newClient, const boost::system::error_code& error){
  std::cout << "A new client has connected." << std::endl;
   newClient->start();


   safeAdd_.lock();
   clients_.push_back( newClient );
   safeAdd_.unlock();

  prepareForNewClient();
}
