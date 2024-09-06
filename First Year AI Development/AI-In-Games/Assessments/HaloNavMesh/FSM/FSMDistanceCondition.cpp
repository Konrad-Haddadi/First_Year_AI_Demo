#include "FSMDistanceCondition.h"

#include "..\Agent.h"
#include "..\Spartan.h"

#include <glm/glm.hpp>
#include <Azimuth/GameObjects/ATransform.h>

bool FSMDistanceCondition::IsTrue(Agent* _agent)
{
    vec2 aPos = _agent->Transform()->Position();
    vec2 bPos =  _agent->GetSpartanTarget()->Transform()->Position();

    return (glm::distance( aPos, bPos) < m_distance) == m_lessThan;
}
