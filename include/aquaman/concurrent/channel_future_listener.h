#ifndef AQUAMAN_CONCURRENT_CHANNEL_FUTURE_LISTENER
#define AQUAMAN_CONCURRENT_CHANNEL_FUTURE_LISTENER

#include <aquaman/concurrent/generic_future_listener.h>

namespace aquman
{
namespace concurrent
{
template <typename T> class channel_future_listener: public generic_future_listener<T>{

};
}; // namespace concurrent
}; // namespace aquman
#endif
