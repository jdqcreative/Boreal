#include "bopch.h"
#include "OrthographicCamera.h"

namespace Boreal {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: m_ProjectionMatrix(alder::ortho(left, right, bottom, top, -1.0f, 1.0f)) 
	{
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetPosition(const alder::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		alder::mat4 transform = alder::translate(alder::mat4(1.0f), m_Position) *
			alder::rotate(alder::mat4(1.0f), alder::radians(m_Rotation), alder::vec3(0, 0, 1));

		m_ViewMatrix = alder::inverse(transform);
		m_viewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}