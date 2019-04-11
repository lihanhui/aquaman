#ifndef AQUAMAN_CONCURRENT_RUNNABLE
#define AQUAMAN_CONCURRENT_RUNNABLE
namespace aquaman
{

struct runnable{
	virtual void run() = 0;
};

}; // namespace aquaman
#endif
