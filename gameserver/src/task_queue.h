//-*-c++-*-
#ifndef NOVIA_TASK_QUEUE_H
#define NOVIA_TASK_QUEUE_H

#include <functional>
#include <functional>
#include <queue>


namespace novia {
  class TaskQueue : public std::queue<std::function<void ()>> {
    typedef std::function<void ()> task;
  public:
  };
}

#endif
