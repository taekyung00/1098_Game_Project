#include "Mode1.h"


Mode1::Mode1() : floor1(floorstatemanager), floor2(floorstatemanager){}

void Mode1::Load(){
	floorstatemanager.AddFloor(floor1);
	floorstatemanager.AddFloor(floor2);
}

void Mode1::Update(double dt){
	floorstatemanager.Update(dt);
}

void Mode1::Unload(){
	
}

void Mode1::Draw()
{
}

