#ifndef RESOURCE_HANDLING_ERROR_H
#define RESOURCE_HANDLING_ERROR_H

#include <stdexcept>
#include <string>

class ResourceHandlingError: public std::runtime_error {
 public:
 ResourceHandlingError(std::string message) : std::runtime_error(message)
  {}
};

#endif
