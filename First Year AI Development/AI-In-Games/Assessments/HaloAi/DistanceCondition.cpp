#include "DistanceCondition.h"
#include "CovenantBaseAgent.h"
#include "glm/glm.hpp"
#include "Composite.h"

int DistanceCondition::Update(CovenantBaseAgent* _agent, float _dt)
{
    CovenantBaseAgent* target = _agent->GetTarget();

    if (!target)
        return Composite::Failure;

    vec2 aPos = _agent->GetPos();
    vec2 bPos = target->GetPos();

    if (glm::distance(aPos, bPos) < _agent->GetRange() || _agent->GetCurrentQuad() == target->GetCurrentQuad())
        return Composite::Success;
    else
    {
        target->RemoveFromSquad(_agent);
        _agent->SetTarget(nullptr);
        return Composite::Failure;    
    }
    
}

int DistanceCondition::Update(Agent* _agent, float _dt)
{
    return 0;
}
