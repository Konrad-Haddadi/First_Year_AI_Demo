#include "SpartanDistanceCondition.h"
#include "CovenantBaseAgent.h"
#include "SpartanAgent.h"
#include "glm/glm.hpp"
#include "Composite.h"

bool InRange(CovenantBaseAgent* _agent1, SpartanAgent* _agent2);

int SpartanDistanceCondition::Update(CovenantBaseAgent* _agent, float _dt)
{
    SpartanAgent* target = _agent->GetTargetEnemy();

    if (!target)
        return Composite::Failure;

    vec2 aPos = _agent->GetPos();
    vec2 bPos = target->GetPos();

    if (glm::distance(aPos, bPos) < _agent->GetRange() || InRange(_agent, target))
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

bool InRange(CovenantBaseAgent* _agent1, SpartanAgent* _agent2)
{
    if (_agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() ||
        _agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() - 8 || 
        _agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() + 8|| 
        _agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() - 1 ||
        _agent1->GetCurrentQuad() == _agent2->GetCurrentQuad() + 1)
        return true;

    return false;
}