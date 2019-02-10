#ifndef AQUAMAN_EVENT_EVENT
#define AQUAMAN_EVENT_EVENT

#include <exception>

class event {
public: 
    virtual void handle_event() = 0;
    virtual bool failure(std::exception_ptr cause) = 0;
};
#endif
