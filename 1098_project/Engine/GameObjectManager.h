/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    April 25, 2025
*/

#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include "GameObject.h"
#include "Matrix.h"
#include "Component.h"

namespace Math { class TransformationMatrix; }

namespace CS230 {
    class GameObjectManager : public CS230::Component{
    public:
        void Add(GameObject* object);
        void Unload();

        void UpdateAll(double dt);
        void SortForDraw();
        void DrawAll(Math::TransformationMatrix camera_matrix);

        void CollisionTest();
        template<typename T>
        T* GetGameObject() {
            for (GameObject* gameobject : objects) {
                T* ptr = dynamic_cast<T*>(gameobject);
                if (ptr != nullptr) {
                    return ptr;
                }
            }
            return nullptr;
        }

        template<typename T>
        void RemoveGameObject() {
            auto it = std::find_if(
                objects.begin(), objects.end(), [](GameObject* element) {
                    return (dynamic_cast<T*>(element) != nullptr);
                }
            );
            delete* it;
            objects.erase(it);
        }
    private:
        std::list<GameObject*> objects;
    };
}
