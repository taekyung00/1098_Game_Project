/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    April 25, 2025
*/
#include "GameObjectManager.h"

void CS230::GameObjectManager::Add(GameObject* object){
	objects.push_back(object);
}

void CS230::GameObjectManager::Unload(){
	for (GameObject* object : objects) {
		delete object;
	}
	objects.clear();
}

void CS230::GameObjectManager::UpdateAll(double dt){
	std::vector<GameObject*> destroy_objects;
	for (GameObject* object : objects) {
		object->Update(dt);
		if (object->Destroyed() == true) {
			destroy_objects.push_back(object);
		}
	}
	for (GameObject* destroy_object : destroy_objects) {
		objects.remove(destroy_object);
		delete destroy_object;
	}
}

//void CS230::GameObjectManager::SortForDraw()
//{
//	if (objects.empty()) {
//		return;
//	}
//	std::stable_sort(objects.begin(), objects.end(),
//		[](GameObject* a, GameObject* b) {
//			return a->DrawPriority() < b->DrawPriority();
//		});
//	std::list<CS230::GameObject*>::iterator max_it = std::max_element(objects.begin(), objects.end(),
//		[](GameObject* a, GameObject* b) {
//			return a->DrawPriority() < b->DrawPriority();
//		});
//	if (max_it != objects.end() && std::next(max_it) != objects.end()) {
//		GameObject* highest = *max_it;
//		objects.erase(max_it);               
//		objects.push_back(highest);         
//	}
//}

void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix){
	for (GameObject* object : objects) {
		object->Draw(camera_matrix);		
	}
}

void CS230::GameObjectManager::CollisionTest()
{
	for (GameObject* object1 : objects) {
		for (GameObject* object2 : objects) {
			if (object1 != object2 && object1->CanCollideWith(object2->Type())) {
				if (object1->IsCollidingWith(object2)) {
					Engine::GetLogger().LogEvent("Collision Detected: " + object1->TypeName() + " and " + object2->TypeName());
					object1->ResolveCollision(object2);
				}
			}
		}
	}
}
