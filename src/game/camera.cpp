#include "game/camera.h"

#include <glm/ext/matrix_transform.hpp>

namespace solunar
{

TYPEINFO_IMPLEMENTATION(CameraComponent, Component);

CameraComponent::CameraComponent() :
	m_eye(0.0f),
	m_center(0.0f),
	m_up(0.0f, 1.0f, 0.0f)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::onEntitySet(Entity* entity)
{
	Component::onEntitySet(entity);
}

void CameraComponent::onEntityRemove()
{
	Component::onEntityRemove();
}

void CameraComponent::setLookAt(const glm::vec3& targetLocation)
{
	m_center = targetLocation;
}

glm::mat4 CameraComponent::getViewMatrix()
{
	return glm::lookAt(m_eye, m_eye + m_center, m_up);
}

}