// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInInventory.h"
#include "CharacterStats\InteractActor.h"
#include "Components\Button.h"

void UItemInInventory::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Use && Drop)
	{
		Drop->OnClicked.AddDynamic(this, &UItemInInventory::ClickDropButton);
		Use->OnClicked.AddDynamic(this, &UItemInInventory::ClickUseButton);
	}
}

void UItemInInventory::ClickDropButton()
{
	if (ActForInteract)
	{
		ActForInteract->CreateItem();
	}
}

void UItemInInventory::ClickUseButton()
{
	if (ActForInteract)
	{
		ActForInteract->UseItem();
	}

}
