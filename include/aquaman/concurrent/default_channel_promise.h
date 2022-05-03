#ifndef AQUAMAN_CONCURRENT_DEFAULT_CHANNEL_PROMISE
#define AQUAMAN_CONCURRENT_DEFAULT_CHANNEL_PROMISE

#include "aquaman/concurrent/channel_promise.h"
namespace aquaman
{

template<typename T> class DefaultChannelPromise: public ChannelPromise<T> {

};

}; // namespace aquaman
#endif
