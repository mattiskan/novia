#include "ConnectionHandler.h"
//using boost::asio::local::stream_protocol in include

ConnectionHandler::ConnectionHandler(stream_protocol::endpoint ep)
  :acceptor_(ioService_, ep) {
  prepareForNewClient();
}
  
void ConnectionHandler::start() {
  ioServiceThread_ = new std::thread(&ConnectionHandler::run, this);
}

void ConnectionHandler::run(){
  while(true)
    ioService_.run();
}

std::vector<int> ConnectionHandler::pollClientActions(){
  std::vector<int> allMsg;

   for(auto it=clients_.begin(); it!=clients_.end(); ++it){
     std::vector<int> clientActions = (*it)->getClientActions();
     allMsg.insert(allMsg.end(), clientActions.begin(), clientActions.end());
   }

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
   clients_.push_back( newClient );

  prepareForNewClient();
}
