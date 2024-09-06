#include "DistanceCondition.h"
#include "Agent.h"
#include "glm/glm.hpp"

bool DistanceCondition::IsTrue(Agent* _agent)
{
    vec2 aPos = { _agent->GetPos().x + 55, _agent->GetPos().y + 55 };
    vec2 bPos = { _agent->GetTarget()->GetPos().x + 55, _agent->GetTarget()->GetPos().y + 55 };

    return (glm::distance( aPos, bPos) < m_distance) == m_lessThan;
}
