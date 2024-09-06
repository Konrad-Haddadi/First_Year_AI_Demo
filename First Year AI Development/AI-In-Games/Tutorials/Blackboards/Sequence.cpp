#include "Sequence.h"

Sequence::~Sequence()
{
	for (int i = 0; i < children.size(); i++)
		delete children[i];

	delete pendingChild;
}

int Sequence::Update(Agent* _agent, float _dt)
{
	Behaviour* child = pendingChild;
	pendingChild = nullptr;

	if (!child)
	{
		child = children.front();
		index = 0;
	}

	int result = child->Update(_agent, _dt);

	switch (result)
	{
	case Failure:
		return Failure;

	case Success:
		index++;

		if (index >= children.size())
			return Success;

		pendingChild = children[index];
		return Pending;

	case Pending:
		pendingChild = child;
		return Pending;
	}
}

int Sequence::Update(CovenantBaseAgent* _agent, float _dt)
{
	Behaviour* child = pendingChild;
	pendingChild = nullptr;

	if (!child)
	{
		child = children.front();
		index = 0;
	}

	int result = child->Update(_agent, _dt);

	switch (result)
	{
	case Failure:
		return Failure;

	case Success:
		index++;

		if (index >= children.size())
			return Success;

		pendingChild = children[index];
		return Pending;

	case Pending:
		pendingChild = child;
		return Pending;
	}
}
