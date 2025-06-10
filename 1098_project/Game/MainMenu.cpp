/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  MainMenu.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 6, 2025
*/

#include "MainMenu.h"
#include "States.h"

MainMenu::MainMenu() : 
	current_option(Option::InGame),
	title_texture(Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("10..9..8", title_color))
{
	InGame_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("INGAME", ingame_color);
	Tutorial_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("TUTORIAL", tutorial_color);
	exit_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("EXIT", exit_color);
	update_textures();
}

void MainMenu::Load()
{
	update_textures();
}

void MainMenu::Update([[maybe_unused]] double dt)
{
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down)) {
		switch (current_option)
		{
		case Option::InGame:
			current_option = Option::Tutorial;
			break;
		case Option::Tutorial:
			current_option = Option::exit;
			break;
		case Option::exit:
			current_option = Option::InGame;
			break;
		}
	}

	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
		switch (current_option)
		{
		case MainMenu::Option::InGame:
			current_option = Option::exit;
			break;
		case Option::Tutorial:
			current_option = Option::InGame;
			break;
		case MainMenu::Option::exit:
			current_option = Option::Tutorial;
			break;
		}
	}
	update_textures();
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Enter)) {
		switch (current_option)
		{
		case Option::InGame:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::InGame));
			break;
		case Option::Tutorial:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Tutorial));
			break;
		case Option::exit:
			Engine::GetGameStateManager().ClearNextGameState();
			break;
		}
	}
}

void MainMenu::Unload()
{
}

void MainMenu::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	title_texture->Draw(Math::TranslationMatrix(Math::ivec2{ 
		Engine::GetWindow().GetSize().x/2  - title_texture->GetSize().x/2, 
		Engine::GetWindow().GetSize().y - title_texture->GetSize().y - 10 }));


	InGame_texture->Draw(Math::TranslationMatrix(Math::ivec2{
		Engine::GetWindow().GetSize().x / 2 - InGame_texture->GetSize().x / 2,
		Engine::GetWindow().GetSize().y - InGame_texture->GetSize().y - 280 }));

	Tutorial_texture->Draw(Math::TranslationMatrix(Math::ivec2{
		Engine::GetWindow().GetSize().x / 2 - Tutorial_texture->GetSize().x / 2,
		Engine::GetWindow().GetSize().y - Tutorial_texture->GetSize().y - 350 }));

	exit_texture->Draw(Math::TranslationMatrix(Math::ivec2{
		Engine::GetWindow().GetSize().x / 2 - 10 - exit_texture->GetSize().x / 2,
		Engine::GetWindow().GetSize().y - exit_texture->GetSize().y - 420 }));

}


void MainMenu::update_textures()
{
	delete InGame_texture;
	delete Tutorial_texture;
	delete exit_texture;
	switch (current_option)
	{
	case Option::InGame:
		ingame_color = seleted_color;
		tutorial_color = non_seleted_color;
		exit_color = non_seleted_color;
		break;
	case Option::Tutorial:
		ingame_color = non_seleted_color;
		tutorial_color = seleted_color;
		exit_color = non_seleted_color;
		break;
	case Option::exit:
		ingame_color = non_seleted_color;
		tutorial_color = non_seleted_color;
		exit_color = seleted_color;
		break;
	}
	InGame_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("INGAME", ingame_color);
	Tutorial_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("TUTORIAL", tutorial_color);
	exit_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("EXIT", exit_color);

}
