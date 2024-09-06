#include "FSMSurroundingCondition.h"


#include "..\Agent.h"
#include "..\CovenantAgent.h"

#include <glm/glm.hpp>
#include <Azimuth/GameObjects/ATransform.h>
#include <list>

using std::list;

bool FSMSurroundingCondition::IsTrue(Agent* _agent)
{
    vec2 aPos = _agent->Transform()->Position();
    list<CovenantAgent*> covenant = *_agent->GetHashTable()->GetCovenant(_agent->GetCurrentQuad());

    for (auto c : covenant)
    {
        vec2 bPos = c->Transform()->Position();

        if((glm::distance(aPos, bPos) < m_distance) == m_lessThan);
            return true;
    }   

    return (false == m_lessThan);
}
