#include "DistanceCondition.h"
#include "Agent.h"
#include "glm/glm.hpp"
#include "Composite.h"

int DistanceCondition::Update(Agent* _agent, float _dt)
{
    vec2 aPos = { _agent->GetPos().x + 55, _agent->GetPos().y + 55 };
    vec2 bPos = { _agent->GetTarget()->GetPos().x + 55, _agent->GetTarget()->GetPos().y + 55 };

    if ((glm::distance(aPos, bPos) < m_distance) == m_isTrue)
        return Composite::Success;
    else
        return Composite::Failure;
    
}
