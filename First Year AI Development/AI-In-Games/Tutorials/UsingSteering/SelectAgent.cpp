#include "SelectAgent.h"

#include "Agent.h"
#include "State.h"
#include "NodeMap.h"
#include "Behaviour.h"
#include "Composite.h"
#include "VisionCondition.h"
#include "WanderBehaviour.h"
#include "FollowBehavoiur.h"
#include "Selector.h"
#include "Sequence.h"

SelectAgent::SelectAgent(NodeMap* _nodeMap, Color _color, int _speed)
	:	Agent(_nodeMap, nullptr, _color, _speed)
{
	m_behaviours =
		(new Selector())
		->Add((new Sequence())
			->Add(new VisionCondition(true))
			->Add(new FollowBehavoiur))
		->Add((new Sequence())
			->Add(new VisionCondition(false))
			->Add(new WanderBehaviour));

	
}

void SelectAgent::Load()
{
	
}

void SelectAgent::Update(float _dt)
{
	GetPathAgent()->Update(_dt);
	m_behaviours->Update(this, _dt);
}

void SelectAgent::Draw()
{
	GetPathAgent()->Draw();
}
