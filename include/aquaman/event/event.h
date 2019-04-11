#ifndef AQUAMAN_EVENT_EVENT
#define AQUAMAN_EVENT_EVENT

#include <exception>
namespace aquman
{
namespace event
{
class event {
public: 
    virtual void handle_event() = 0;
    virtual bool failure(std::exception_ptr cause) = 0;
    virtual bool aborted() = 0;
};
}; // namespace event
}; // namespace aquman
#endif
