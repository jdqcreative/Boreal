#include "bopch.h"
#include "Time.h"

namespace Boreal {

	float Time::GetTime()
	{
		static auto start = std::chrono::high_resolution_clock::now();
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration<float>(now - start);
		return duration.count();
	}

}