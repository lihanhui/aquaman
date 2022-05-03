#ifndef AQUAMAN_UTIL_UTIL
#define AQUAMAN_UTIL_UTIL

#include <functional>
#include <string>
namespace aquaman
{

struct Util {
	static size_t hash(const std::string & key) {
		std::hash<std::string> hash_fn;
    	return hash_fn(key);
	}
};

}; // namespace aquaman
#endif
