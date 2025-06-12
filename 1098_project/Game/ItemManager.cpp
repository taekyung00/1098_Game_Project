#include "ItemManager.h"
#include "Omurice.h"
#include "Pizza.h"
#include "Chocolate.h"
#include "Axe.h"
#include "Shield.h"
#include "Spear.h"
#include "Boots.h"

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

    std::discrete_distribution<> dist1({55 , 30, 10, 5 }); // index 0:55% - common, 1:30% - rare , 2:10% - unique, 3: 5% - legendary
    std::discrete_distribution<> dist2({25 , 25, 25, 25 }); // index 0:25% - shield, 1:25% - spare , 2:25% - axe , 3 : 25% - boots

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
    case 3:
        rank = UseItemRank::Legendary;
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

    case 3:
        new_item = new Boots(index, ItemKind::Use, UseItem::Axe, rank);
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

void ItemManager::ClearUseItem()
{
    Player* player = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>();
    
    for (Item* use_item : use_items) {
        bool is_in_player = false;
        for (Item* player_use_item : player->GetUseItem()) {
            if (use_item == player_use_item) {
                is_in_player = true;
                break;
            }
        }

        if (is_in_player == false) {
            EraseUseItem(use_item);
        }
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

void ItemManager::PushUseItemToPlayer(Item* item)
{
    std::vector<Item*>& player_use_item = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGameObject<Player>()->SetUseItem();
    //spear or axe
    if (item->Type() == GameObjectTypes::Axe || item->Type() == GameObjectTypes::Spear) {
        std::vector<Item*>::iterator iter = std::find_if(player_use_item.begin(), player_use_item.end(), [](Item* find_item) {
            return find_item->Type() == GameObjectTypes::Axe || find_item->Type() == GameObjectTypes::Spear;
            });
        if (iter != player_use_item.end()) {
            EraseUseItem(*iter);
            player_use_item.erase(std::remove(player_use_item.begin(), player_use_item.end(), *iter), player_use_item.end());
        }
        player_use_item.push_back(item);
    }
    

    //shield
    else if (item->Type() == GameObjectTypes::Shield ) {
        std::vector<Item*>::iterator iter = std::find_if(player_use_item.begin(), player_use_item.end(), [](Item* find_item) {
            return find_item->Type() == GameObjectTypes::Shield ;
            });
        if (iter != player_use_item.end()) {
            EraseUseItem(*iter);
            player_use_item.erase(std::remove(player_use_item.begin(), player_use_item.end(), *iter), player_use_item.end());
        }
        player_use_item.push_back(item);
    }
    
    //boots
    else if (item->Type() == GameObjectTypes::Boots) {
        std::vector<Item*>::iterator iter = std::find_if(player_use_item.begin(), player_use_item.end(), [](Item* find_item) {
            return find_item->Type() == GameObjectTypes::Boots;
            });
        if (iter != player_use_item.end()) {
            EraseUseItem(*iter);
            player_use_item.erase(std::remove(player_use_item.begin(), player_use_item.end(), *iter), player_use_item.end());
        }
        player_use_item.push_back(item);
    }
}
