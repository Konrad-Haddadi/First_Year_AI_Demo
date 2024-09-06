#pragma once

#include "Azimuth/Azimuth.h"

#include <functional>
#include <list>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

using std::function;
using std::list;

using glm::mat4;
using glm::vec2;

class ATransform
{
public:
		DLL ATransform*& Parent();
	DLL void SetParent(ATransform* _parent);

	DLL float Rotation() const;
	DLL float LocalRotation() const;

	DLL void SetRotation(const float& _newRot);

	DLL void UpdateRotation(const float& _amount);

	DLL void Position(float& _x, float& _y) const;
	DLL vec2 Position() const;;

	DLL void LocalPosition(float& _x, float& _y) const;
	DLL vec2 LocalPosition() const;;

	DLL void SetPosition(const float& _newX, const float& _newY);
	DLL void SetPosition(const vec2& _newPos);

	DLL void UpdatePosition(const float& _newX, const float& _newY);
	DLL void UpdatePosition(const vec2& _newPos);

	DLL void Scale(float& _x, float& _y) const;
	DLL vec2 Scale() const;

	DLL void LocalScale(float& _x, float& _y) const;
	DLL vec2 LocalScale() const;

	DLL void SetScale(const float& _newX, const float& _newY);
	DLL void SetScale(const vec2& _newScale);

	DLL void UpdateScale(const float& _newX, const float& _newY);
	DLL void UpdateScale(const vec2& _newScale);

	DLL void TRS(const vec2& _pos, const float& _angle, const vec2& _scale);

private:
	friend class GameObject;
	friend class GameObjectManager;

	mat4 m_transform;
	ATransform* m_parent;
	list<ATransform*> m_children;
	list<function<void()>> m_listUpdates;

private:
	ATransform() : m_transform(mat4(1.f)), m_parent(nullptr) {}

	DLL mat4 GlobalTransform() const;

	DLL void AddChild(ATransform* _child);
	DLL void RemoveChild(ATransform* _child);
	DLL void Update();
};

