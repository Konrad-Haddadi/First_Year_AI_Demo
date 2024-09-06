#include "AvoidingBehaviour.h"
#include "SteeringAgent.h"
#include <list>
#include <vector>

using std::list;
using std::vector;

int AvoidingBehaviour::Update(SteeringAgent* _agent, float _dt)
{
    bool collision = false;
    list<Rectangle> objPoints = *_agent->GetTable()->GetObjects(_agent->GetCurrentQuad());
    vector<Rectangle> quad = *_agent->GetTable()->GetAllQuads();
    vector<vec2> ray = _agent->GetRays();
    Vector2 futhest = { _agent->GetFurthestPoint().x, _agent->GetFurthestPoint().y };
    
    vec2 velocity = { 0,0 };

    for (int i = 0; i < quad.size(); i++)
    {
        if (CheckCollisionPointRec(futhest, quad[i]))
        {
            for (Rectangle rect : *_agent->GetTable()->GetObjects(i))
            {
                for (int i = 1; i < ray.size(); i++)
                {
                    if (CheckCollisionPointRec({ ray[i].x,ray[i].y }, rect))
                    {
                        velocity += vec2{ _agent->GetTransform()->Position() - vec2{ rect.x + rect.width / 2, rect.y + rect.height / 2} };
                        collision = true;
                    }
                }
                _agent->SetVelocity(velocity);
            }
        }        
    }

    for (Rectangle rect : objPoints)
    {
        for (int i = 1; i < ray.size(); i++)
        {
            if (CheckCollisionPointRec({ ray[i].x,ray[i].y }, rect))
            {
                velocity += vec2{ _agent->GetTransform()->Position() - vec2{ rect.x + rect.width / 2, rect.y + rect.height / 2} };
                collision = true;
            }
        } 
        _agent->SetVelocity(velocity);
    }

    if(!collision)
        _agent->SetVelocity({0,0});

    return 0;
}
