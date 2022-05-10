#include "oapch.h"
#include "OrthographicCameraController.h"
#include "Orca/Core/Input.h"
#include "Orca/Core/KeyCodes.h"
#include "Orca/Core/Core.h"



namespace Orca {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
		: m_AspectRatio(aspectRatio), m_CameraRotation(0), m_Camera(m_AspectRatio * -m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts) {
		OA_PROFILE_FUNCTION();
		if (Input::IsKeyPressed(OA_KEY_W)) 
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(OA_KEY_S)) 
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(OA_KEY_D)) 
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(OA_KEY_A)) 
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;

		if (m_Rotation) {
			if (Input::IsKeyPressed(OA_KEY_Q))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(OA_KEY_E))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel * 3.0f;
		
	
	}

	void OrthographicCameraController::CalculateView() {
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void OrthographicCameraController::OnEvent(Event& e) {
		OA_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(OA_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(OA_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		OA_PROFILE_FUNCTION();
		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.1f);
		m_ZoomLevel = std::min(m_ZoomLevel, 15.0f);
		CalculateView();
		return true;

	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
		OA_PROFILE_FUNCTION();
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		CalculateView();
		return true;
	}


}