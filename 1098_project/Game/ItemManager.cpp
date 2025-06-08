#include "ItemManager.h"
#include "Omurice.h"
#include "Pizza.h"
#include "Chocolate.h"

void ItemManager::DropItem(Math::ivec2 index)
{
    CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
    std::random_device rd;
    std::mt19937 gen(rd());

    std::discrete_distribution<> dist({ 5, 15, 80 }); // index 0:5% - pizza, 1:15% - omurice , 2:80% - chocolate

    int result = dist(gen);

    switch (result) {
    case 0:
        gameobjectmanager->Add(new Pizza(index));
        break;
    case 1:
        gameobjectmanager->Add(new Omurice(index));
        break;
    case 2:
        gameobjectmanager->Add(new Chocolate(index));
        break;
    }
}
