#ifndef AQUAMAN_CONCURRENT_PROMISE
#define AQUAMAN_CONCURRENT_PROMISE

#include <future>
namespace aquaman
{

template <typename T> class promise: public std::promise<T>{
public:
     /**
     * Marks this future as a success and notifies all
     * listeners.
     *
     * If it is success or failed already it will throw an {@link IllegalStateException}.
     */
    virtual bool success(T v) = 0;

    /**
     * Marks this future as a success and notifies all
     * listeners.
     *
     * @return {@code true} if and only if successfully marked this future as
     *         a success. Otherwise {@code false} because this future is
     *         already marked as either a success or a failure.
     */
    virtual bool try_success(T v) = 0;

    /**
     * Marks this future as a failure and notifies all
     * listeners.
     *
     * If it is success or failed already it will throw an {@link IllegalStateException}.
     */
    virtual bool failure(std::exception_ptr cause) = 0;

    /**
     * Marks this future as a failure and notifies all
     * listeners.
     *
     * @return {@code true} if and only if successfully marked this future as
     *         a failure. Otherwise {@code false} because this future is
     *         already marked as either a success or a failure.
     */
    virtual bool try_failure(std::exception_ptr cause) = 0;

    virtual bool done() = 0;
};

}; // namespace aquaman
#endif
