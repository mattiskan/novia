//-*-c++-*-
#ifndef NOVIA_TASK_QUEUE_H
#define NOVIA_TASK_QUEUE_H

#include <functional>
#include <functional>
#include <queue>


namespace novia {
  class TaskQueue {
    typedef std::function<void ()> task;
    std::queue<task> tasks;

  public:
    void invoke_all();
  };
}

#endif
