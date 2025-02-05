#include "GameObject.hpp"

GameObject::GameObject(std::string name, Transform transform, int zindex){
	this->name = name;
	this->transform = transform;
	this->zindex = zindex;
}