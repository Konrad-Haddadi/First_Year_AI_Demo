#include "Spartan.h"
#include "Agent.h"
#include "Behaviour.h"
#include "INavigatable.h"
#include "SteeringAgent.h"
#include "HashTable.h"
#include <Azimuth/GameObjects/GameObject.h>
#include <Azimuth/GameObjects/ATransform.h>

Spartan::Spartan(const char* _name, INavigatable* _map, HashTable* _table, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(_name, _map, _table, _behaviour, _speed, _color, _gsMan, _goMan), seen(false), timer(10), m_spreadMax(30), m_spreadMin(5)
{
	m_texture = Resources::Find<Texture2D, TextureResource>("textures/Player");
	Transform()->TRS({0,0}, 0, {1,1});
}

Spartan::~Spartan()
{
	m_table->RemoveFromQuad(this);

	delete m_current;
	delete m_next;

	m_current = nullptr;
	m_next = nullptr;
	m_table = nullptr;
	m_map = nullptr;
	m_spartan = nullptr;
}

void Spartan::Load()
{
	m_table->AddToQuad(0, this);
	m_steeringAgent.currentQuad = m_currentQuad;
	Transform()->SetPosition(m_pathAgent.GetPos());
}

void Spartan::Update(float _dt)
{
	m_current->Update(this, _dt);
	m_pathAgent.Update(_dt);
	m_steeringAgent.Update(_dt);

	Controls(_dt);
	SeenTimer(_dt);	
	CalculateRot();
	
	CheckNext();
	HashTableCheck();
}

void Spartan::Draw()
{
	m_pathAgent.Draw();
	
	//DrawVeiw();
	DrawName();

	if (IsKeyUp(KEY_GRAVE))
	{
		DrawTextureEx(*m_texture, { Transform()->Position().x + 10, Transform()->Position().y + 10 }, 0, 0.45f, WHITE);
		return;
	}	

	m_steeringAgent.Draw();	
}

void Spartan::Controls(float _dt)
{
	if (m_spread > m_spreadMin)
		m_spread -=  (m_spread - m_spreadMin) * 2 * _dt;
	else
		m_spread = m_spreadMin;

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		if(m_spread <= m_spreadMax)
			m_spread += 5;
	}
	
}

void Spartan::HashTableCheck()
{
	if (m_table->HasMoved(m_currentQuad, this))
	{
		m_currentQuad = m_table->UpdateQuad(this);
		m_steeringAgent.currentQuad = m_currentQuad;
	}
}

void Spartan::CheckNext()
{
	if (m_next)
	{
		delete m_current;
		m_current = m_next;
		m_next = nullptr;
	}
}

void Spartan::CalculateRot()
{
	vec2 mousePos = { GetMousePosition().x, GetMousePosition().y };
	vec2 dir = glm::normalize(mousePos - Transform()->Position());
	float rot = glm::atan(dir.y, dir.x);

	Transform()->SetRotation(rot);
}

void Spartan::DrawVeiw()
{
	vector<vec2> tri = m_steeringAgent.GetTrianglePoints(m_spread);

	vector<Vector2> triVector;

	for (int i = 0; i < 3; i++)
		triVector.push_back({ tri[i].x, tri[i].y });
	

	for (int i = 1; i < 3; i++)
		DrawLine(tri[0].x, tri[0].y, tri[i].x, tri[i].y, BLACK);
	

	DrawTriangle(triVector[0], triVector[2], triVector[1], {RED.r, RED.g, RED.b, 100});
}

void Spartan::DrawName()
{
	DrawText(GetName(), Transform()->Position().x - TextLength(GetName()) + 1, Transform()->Position().y - 19, 15, BLACK);
	DrawText(GetName(), Transform()->Position().x - TextLength(GetName()) + 1, Transform()->Position().y - 20, 15, m_pathAgent.color);
}

void Spartan::SeenTimer(float _dt)
{
	if (seen)
		timer -= _dt;
	else
		timer = 10;

	if (timer <= 0)
		timer = 0;
}
