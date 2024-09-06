#include "Sequence.h"

void Sequence::Enter(Agent* _agent)
{
	for (auto c : children)
		c->Enter(_agent);		
}

int Sequence::Update(Agent* _agent, float _dt)
{
	Behaviour* child = pendingChild;

	if (!child)
	{
		child = children.front();
		index = 0;
	}
	
	int result = child->Update(_agent, _dt);

	switch (result)
	{
	case Failure:
		index = 0;

		child->Exit(_agent);
		pendingChild = children[index];
		return Failure;

	case Success:
		child->Enter(_agent);
		index++;

		if (index >= children.size())
			index = 0;

		child->Exit(_agent);

		pendingChild = children[index];
		return Success;

	case Pending:

		pendingChild = child;
		return Pending;

	default:
		break;
	}

}

void Sequence::Exit(Agent* _agent)
{
	for (auto c : children)
		c->Exit(_agent);	
}
