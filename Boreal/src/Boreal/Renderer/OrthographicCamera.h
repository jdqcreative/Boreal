#pragma once

#include "Camera.h"

namespace Boreal {

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		virtual void SetPosition(const alder::vec3& position) override;
		void SetRotation(float rotation);

		virtual const alder::vec3& GetPosition() const override { return m_Position; }
		float GetRotation() const { return m_Rotation; }

		virtual const alder::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		virtual const alder::mat4& GetViewMatrix() const override { return m_ViewMatrix; }
		virtual const alder::mat4& GetViewProjectionMatrix() const override { return m_viewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		alder::mat4 m_ProjectionMatrix;
		alder::mat4 m_ViewMatrix;
		alder::mat4 m_viewProjectionMatrix;

		alder::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}