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

glm::mat4 CameraComponent::getViewMatrix()
{
	return glm::identity<glm::mat4>();
}

}