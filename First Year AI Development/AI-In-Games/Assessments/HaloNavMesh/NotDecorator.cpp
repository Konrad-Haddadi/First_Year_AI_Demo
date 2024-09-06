#include "NotDecorator.h"
#include "Composite.h"

int NotDecorator::Update(CovenantAgent* _agent, float _dt)
{
	int result = m_condition->Update(_agent, _dt);

	switch (result)
	{
	case Composite::Failure:
		return Composite::Success;

	case Composite::Success:
		return Composite::Failure;
	}
}

int NotDecorator::Update(Agent* _agent, float _dt)
{
	return 0;
}
