// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseElementInStorage.h"
#include "Kismet\GameplayStatics.h"
#include "Components\TextBlock.h"
#include "Components\Image.h"
#include "GhostProjCharacter.h"

void UBaseElementInStorage::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MainChar = Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UBaseElementInStorage::SetParams(FItemParams Param)
{
	if (ItemImage && ItemName)
	{
		ItemImage->SetBrushFromTexture(Param.GetTexture());
		ItemName->SetText(FText::FromString(Param.GetName()));

	}

}
