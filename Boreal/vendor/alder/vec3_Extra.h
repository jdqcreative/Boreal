#pragma once

#include "vec3.h"
#include "vec4.h"

namespace alder {

	inline vec3::vec3(const vec4& v4)
		: x(v4.x), y(v4.y), z(v4.z) {}

}