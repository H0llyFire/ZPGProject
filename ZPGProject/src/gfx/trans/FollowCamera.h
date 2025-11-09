#pragma once
#include <memory>

#include "TransformComponent.h"

class Camera;

class FollowCamera :
    public PeriodicalTransformComponent
{
	std::weak_ptr<Camera> _followedCam;
public:
	FollowCamera(const std::shared_ptr<Camera>& camera);
	void Apply(glm::mat4& m, float dTime) override;
};
