#include "ItemManager.h"
#include "Omurice.h"
#include "Pizza.h"
#include "Chocolate.h"
#include "Axe.h"
#include "Shield.h"
#include "Spear.h"

void ItemManager::DropItem(Math::ivec2 index)
{
    CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
    std::random_device rd;
    std::mt19937 gen(rd());

    std::discrete_distribution<> dist({ 5, 15, 80 }); // index 0:5% - pizza, 1:15% - omurice , 2:80% - chocolate

    int result = dist(gen);

    Item* new_item;
    switch (result) {
    case 0:
        new_item = new Pizza(index);
        drop_items.push_back(new_item);
        gameobjectmanager->Add(new_item);
        break;
    case 1:
        new_item = new Omurice(index);
        drop_items.push_back(new_item);
        gameobjectmanager->Add(new_item);
        break;
    case 2:
        new_item = new Chocolate(index);
        drop_items.push_back(new_item);
        gameobjectmanager->Add(new_item);
        break;
    }
}

void ItemManager::StoreItem(Math::ivec2 index)
{
    Engine::GetLogger().LogDebug("in the store!");
    CS230::GameObjectManager* gameobjectmanager = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>();
    std::random_device rd;
    std::mt19937 gen(rd());

    std::discrete_distribution<> dist1({33.4 , 33.3, 33.3 }); // index 0:33.4% - common, 1:33.3% - rare , 2:33.3% - unique
    std::discrete_distribution<> dist2({33.4 , 33.3, 33.3 }); // index 0:33.4% - shield, 1:33.3% - spare , 2:33.3% - axe

    int rank_result = dist1(gen);
    int kind_result = dist2(gen);

    UseItemRank rank = UseItemRank::None;
    switch (rank_result)
    {
    case 0:
        rank = UseItemRank::Common;
        break;
    case 1:
        rank = UseItemRank::Rare;
        break;
    case 2:
        rank = UseItemRank::Unique;
        break;
    }

    Item* new_item;
    switch (kind_result)
    {
    case 0:
        new_item = new Shield(index, ItemKind::Use, UseItem::Shield, rank);
        use_items.push_back(new_item);
        gameobjectmanager->Add(new_item);
        break;
    case 1:
        new_item = new Spear(index, ItemKind::Use, UseItem::Spear, rank);
        use_items.push_back(new_item);
        gameobjectmanager->Add(new_item);
        break;
    case 2:
        new_item = new Axe(index, ItemKind::Use, UseItem::Axe, rank);
        use_items.push_back(new_item);
        gameobjectmanager->Add(new_item);
        break;
    }
}

void ItemManager::ClearDropItem()
{
    for (Item* item : drop_items) {
        item->Destroy();
    }
}

void ItemManager::EraseDropItem(Item* item)
{
    item->Destroy();
    drop_items.erase(std::remove(drop_items.begin(), drop_items.end(), item), drop_items.end());
}

void ItemManager::EraseUseItem(Item* item)
{
    item->Destroy();
    use_items.erase(std::remove(use_items.begin(), use_items.end(), item), use_items.end());
}
