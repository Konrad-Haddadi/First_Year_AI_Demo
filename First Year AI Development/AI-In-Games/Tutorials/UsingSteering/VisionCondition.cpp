#include "VisionCondition.h"
#include "Agent.h"
#include "glm/glm.hpp"
#include "Composite.h"

int VisionCondition::Update(Agent* _agent, float _dt)
{
    if (_agent->GetMap()->IsVisibleFrom(_agent->GetPos(), _agent->GetTarget()->GetPos()) == m_isTrue)
        return Composite::Success;
    else
        return Composite::Failure;

}