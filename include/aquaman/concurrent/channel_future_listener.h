#ifndef AQUAMAN_CONCURRENT_CHANNEL_FUTURE_LISTENER
#define AQUAMAN_CONCURRENT_CHANNEL_FUTURE_LISTENER

#include "aquaman/concurrent/generic_future_listener.h"

namespace aquaman
{

template <typename T> class ChannelFutureListener: public GenericFutureListener<T>{

};

}; // namespace aquaman
#endif
