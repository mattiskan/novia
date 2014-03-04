#include "MessageFactory.h"
#include "TestMessage.h"

MessageFactory::MessageFactory(Player& communicatee)
  :communicatee_(communicatee)
{ }

Message* MessageFactory::createMessage(IO_BUFFER& messageContent){
  return new TestMessage(messageContent);
}
