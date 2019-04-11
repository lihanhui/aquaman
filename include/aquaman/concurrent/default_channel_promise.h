#ifndef AQUAMAN_CONCURRENT_DEFAULT_CHANNEL_PROMISE
#define AQUAMAN_CONCURRENT_DEFAULT_CHANNEL_PROMISE

#include <aquaman/concurrent/channel_promise.h>
namespace aquman
{
namespace concurrent
{
templte<typename T> class default_channel_promise: public channel_promise<T> {

};
}; // namespace concurrent
}; // namespace aquman
#endif