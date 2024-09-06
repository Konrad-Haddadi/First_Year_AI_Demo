#include "DistanceCondition.h"
#include "CovenantBaseAgent.h"
#include "glm/glm.hpp"
#include "Composite.h"

bool InRange(CovenantBaseAgent* _agent1, CovenantBaseAgent* _agent2);

int DistanceCondition::Update(CovenantBaseAgent* _agent, float _dt)
{
    CovenantBaseAgent* target = _agent->GetTarget();

    if (!target)
        return Composite::Failure;

    vec2 aPos = _agent->GetPos();
    vec2 bPos = target->GetPos();

    if (glm::distance(aPos, bPos) < _agent->GetRange() || InRange(_agent, target))
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

bool InRange(CovenantBaseAgent* _agent1, CovenantBaseAgent* _agent2)
{
    if (_agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() ||
        _agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() - 8 ||
        _agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() + 8 ||
        _agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() - 1 ||
        _agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() + 1)
        return true;

    return false;
}
