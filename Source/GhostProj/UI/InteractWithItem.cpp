// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWithItem.h"
#include "CharacterStats\InteractActor.h"
#include "Kismet\GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components\Button.h"

void UInteractWithItem::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Use && Take)
	{
		Use->OnClicked.AddDynamic(this, &UInteractWithItem::OnClickUse);
		Take->OnClicked.AddDynamic(this, &UInteractWithItem::OnClickTake);
	}
}

void UInteractWithItem::OnClickUse()
{
	if (ItemForInteract)
	{
		ItemForInteract->UseItem();
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
		this->RemoveFromParent();
	}

}

void UInteractWithItem::OnClickTake()
{
	if (ItemForInteract)
	{
		ItemForInteract->TakeItem();
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
		this->RemoveFromParent();
	}

}
