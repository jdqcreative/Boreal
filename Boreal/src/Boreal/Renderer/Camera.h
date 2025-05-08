#pragma once

#include "../vendor/alder/alder.h"

namespace Boreal {

	class Camera
	{
	public:
		~Camera() = default;

		virtual const alder::mat4& GetProjectionMatrix() const = 0;
		virtual const alder::mat4& GetViewMatrix() const = 0;
		virtual const alder::mat4& GetViewProjectionMatrix() const = 0;

		virtual void SetPosition(const alder::vec3& position) = 0;
		virtual const alder::vec3& GetPosition() const = 0;
	};

}