#include "Core/Core.h"
#include <boost/algorithm/algorithm.hpp>
#include <boost/atomic/atomic.hpp>

int main()
{
	boost::atomics::atomic_uint64_t value;

	Engine::PrintHelloWorld();
}