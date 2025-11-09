#include "FollowCamera.h"
#include "../Camera.h"

FollowCamera::FollowCamera(const std::shared_ptr<Camera>& camera)
	: _followedCam(camera)
{
}

void FollowCamera::Apply(glm::mat4& m, float dTime)
{
	auto pos = _followedCam.lock()->GetPosition();
	glm::mat4 transMat = glm::translate(glm::mat4(1.f), pos);
	m = transMat;
}
