#ifndef AQUAMAN_CONCURRENT_RUNNABLE
#define AQUAMAN_CONCURRENT_RUNNABLE
namespace aquman
{
namespace concurrent
{
struct runnable{
	virtual void run() = 0;
};
}; // namespace concurrent
}; // namespace aquman
#endif
