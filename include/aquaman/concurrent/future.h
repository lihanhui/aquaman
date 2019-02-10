#ifndef AQUAMAN_CONCURRENT_FUTURE
#define AQUAMAN_CONCURRENT_FUTURE

#include <exception>

#include <aquaman/concurrent/generic_future_listener.h>

template<class T> class future: public std::enable_shared_from_this<future<T>> {
 public:
 /**
     * Returns {@code true} if and only if the I/O operation was completed
     * successfully.
     */
    virtual bool success() = 0;

    /**
     * Returns the cause of the failed I/O operation if the I/O operation has
     * failed.
     *
     * @return the cause of the failure.
     *         {@code null} if succeeded or this future is not
     *         completed yet.
     */
    virtual std::exception_ptr cause() = 0;

    /**
     * Adds the specified listener to this future.  The
     * specified listener is notified when this future is
     * {@linkplain #isDone() done}.  If this future is already
     * completed, the specified listener is notified immediately.
     */
    virtual void add_listener(std::shared_ptr<generic_future_listener<T>> listener) = 0;

    /**
     * Return the result without blocking. If the future is not done yet this will return {@code null}.
     *
     * As it is possible that a {@code null} value is used to mark the future as successful you also need to check
     * if the future is really done with {@link #isDone()} and not relay on the returned {@code null} value.
     */
    virtual T get() = 0;

};
#endif