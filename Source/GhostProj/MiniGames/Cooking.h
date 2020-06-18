// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithTrigger.h"
#include "Structs\CookingMetod.h"
#include "Cooking.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API ACooking : public AActorWithTrigger
{
	GENERATED_BODY()

public:

	virtual void ActionOnInteract();

	/** устанавливает выбранный игроком рецепт */
	void SetCurrentFood(struct FRecipeStruct* Struct);

	/** взять приготовленную еду*/
	void TakeFood(struct FInteractItemStruct* Struct);

protected:

	class UMainCookingWidget* MainWidgetRef;

	struct FRecipeStruct* FoodElement;

	float Timer;

	UFUNCTION()
		void StartCooking();


	/** устанавливает все доступные рецепты */
	void SetRecipeElements();

	UPROPERTY(EditAnywhere)
		TEnumAsByte<ECookingMetods> ThisItemCookingMetod;

	UPROPERTY(EditAnywhere)
		class UDataTable* RecipesDT;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UInteractWithItem> InteractWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ASmallInteractActor> SpawnItemClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UMainCookingWidget> MainWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class URecipeElement> RecipeElem;

};
