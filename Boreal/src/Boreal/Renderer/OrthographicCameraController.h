#pragma once
#include "OrthographicCamera.h"
#include "Boreal/Timestep.h"

namespace Boreal {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController()
			: m_AspectRatio(16.9), m_EnableRotation(false), m_Camera(-m_AspectRatio, m_AspectRatio, -1.0f, 1.0f) {}


		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		OrthographicCamera m_Camera;

		alder::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 2.5f;
		float m_CameraRotationSpeed = 180.0f;

		bool m_EnableRotation;
	};

}