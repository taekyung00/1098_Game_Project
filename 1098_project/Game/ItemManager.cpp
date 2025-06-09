#include "ItemManager.h"
#include "Omurice.h"
#include "Pizza.h"
#include "Chocolate.h"

void ItemManager::DropItem(Math::ivec2 index)
{
    CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
    std::random_device rd;
    std::mt19937 gen(rd());

    //std::discrete_distribution<> dist({ 5, 15, 80 }); // index 0:5% - pizza, 1:15% - omurice , 2:80% - chocolate
    std::discrete_distribution<> dist({ 0, 0, 100 });
    int result = dist(gen);

    Item* new_item;
    switch (result) {
    case 0:
        new_item = new Pizza(index);
        items.push_back(new_item);
        gameobjectmanager->Add(new_item);
        break;
    case 1:
        new_item = new Omurice(index);
        items.push_back(new_item);
        gameobjectmanager->Add(new_item);
        break;
    case 2:
        new_item = new Chocolate(index);
        items.push_back(new_item);
        gameobjectmanager->Add(new_item);
        break;
    }
}

void ItemManager::ClearItem()
{
    for (Item* item : items) {
        item->Destroy();
    }
}
