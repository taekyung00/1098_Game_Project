#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
class GameObject {
public:
	virtual void Load() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Unload() = 0;

};
#endif // !GAMEOBJECT_H

