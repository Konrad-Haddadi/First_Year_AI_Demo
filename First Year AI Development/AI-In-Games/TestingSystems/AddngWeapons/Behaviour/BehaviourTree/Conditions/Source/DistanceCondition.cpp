#include "../DistanceCondition.h"
#include "../../TestingSystems/AddngWeapons/Agents/Spartan.h"
#include "../../TestingSystems/AddngWeapons/Agents/CovenantAgent.h"
#include <glm/glm.hpp>
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Composite/Composite.h"
#include "Azimuth/GameObjects/ATransform.h"

int DistanceCondition::Update(CovenantAgent* _agent, float _dt)
{
    CovenantAgent* target = _agent->GetCovenantTarget();

    if (!target)
        return Composite::Failure;

    vec2 aPos = _agent->Transform()->Position();
    vec2 bPos = target->Transform()->Position();

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
    Spartan* target = _agent->GetSpartanTarget();

    if (!target)
        return Composite::Failure;

    vec2 aPos = _agent->Transform()->Position();
    vec2 bPos = target->Transform()->Position();

    if (glm::distance(aPos, bPos) < 200)
        return Composite::Success;
    else
    {
        _agent->SetTarget(nullptr);
        return Composite::Failure;
    }
}
