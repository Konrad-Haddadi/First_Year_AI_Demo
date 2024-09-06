#include "SpartanDistanceCondition.h"
#include "CovenantBaseAgent.h"
#include "SpartanAgent.h"
#include "glm/glm.hpp"
#include "Composite.h"

int SpartanDistanceCondition::Update(CovenantBaseAgent* _agent, float _dt)
{
    SpartanAgent* target = _agent->GetTargetEnemy();

    if (!target)
        return Composite::Failure;

    vec2 aPos = _agent->GetPos();
    vec2 bPos = target->GetPos();

    if (glm::distance(aPos, bPos) < _agent->GetRange() || _agent->GetCurrentQuad() == target->GetCurrentQuad())
        return Composite::Success;
    else
    {        
        _agent->SetTargetEnemy(nullptr);
        return Composite::Failure;
    }

}

int SpartanDistanceCondition::Update(Agent* _agent, float _dt)
{
    return 0;
}
