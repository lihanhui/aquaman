#ifndef AQUAMAN_CONCURRENT_CHANNEL_FUTURE
#define AQUAMAN_CONCURRENT_CHANNEL_FUTURE
#include <aquaman/concurrent/future.h>
#include <aquaman/concurrent/generic_future_listener.h>
#include <aquaman/event/result.h>

namespace aquman
{
namespace concurrent
{
template <typename T> class channel_future: public future<T> {
public:
    

};
}; // namespace concurrent
}; // namespace aquman
#endif