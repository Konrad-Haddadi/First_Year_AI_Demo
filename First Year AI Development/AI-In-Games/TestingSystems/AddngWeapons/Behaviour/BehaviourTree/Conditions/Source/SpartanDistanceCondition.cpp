#include "SpartanDistanceCondition.h"
#include "CovenantAgent.h"
#include "Spartan.h"
#include "glm/glm.hpp"
#include "Composite.h"
#include <Azimuth/GameObjects/ATransform.h>

int SpartanDistanceCondition::Update(CovenantAgent* _agent, float _dt)
{
    Spartan* target = _agent->GetSpartanTarget();

    if (!target)
        return Composite::Failure;

    vec2 aPos = _agent->Transform()->Position();
    vec2 bPos = target->Transform()->Position();

    if (glm::distance(aPos, bPos) < 50 * (1 + _agent->GetRank()))
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
