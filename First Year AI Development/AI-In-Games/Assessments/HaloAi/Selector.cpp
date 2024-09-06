#include "Selector.h"

Selector::~Selector()
{
	for (int i = 0; i < children.size(); i++)
		delete children[i];

	delete pendingChild;
}

int Selector::Update(Agent* _agent, float _dt)
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
		index++;

		if (index >= children.size())
			index = 0;

		pendingChild = children[index];
		return Failure;
		
	case Success:
		index++;
		return Success;

	case Pending:
		pendingChild = child;
		return Pending;	
	}
	
}

int Selector::Update(CovenantBaseAgent* _agent, float _dt)
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
		index++;

		if (index >= children.size())
			index = 0;

		pendingChild = children[index];
		return Failure;

	case Success:
		index++;
		return Success;

	case Pending:
		pendingChild = child;
		return Pending;
	}

}