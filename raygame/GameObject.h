#pragma once

class GameObject
{
	virtual void OnUpdate(float DeltaTime) {};
	virtual void OnDraw() {};
public:
	void Update(float DeltaTime) { OnUpdate(DeltaTime); }
	void Draw() { OnDraw(); };
};
