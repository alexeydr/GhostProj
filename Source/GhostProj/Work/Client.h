// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UI\InteractWithClient.h"
#include "Navigation/PathFollowingComponent.h"
#include "InteractI.h"
#include "FastfoodComp.h"
#include "Client.generated.h"

UENUM()
enum EDestination
{
	None,
	ToSpawnPoint,
	ToOrder
};

UCLASS()
class GHOSTPROJ_API AClient : public ACharacter, public IInteractI
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClient();

	~AClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		UFastfoodComp* FastFoodComp;

	UPROPERTY()
	TArray<FFood> DesiredFood;

	//bool TypeOrder = FMath::RandBool();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UInteractWithClient> WidgetObj;

	float ClientMoney = 0;

	UInteractWithClient* WidgetRef;

	bool CreateInteractWidget();

	void SetWidgetProperty();

	void ChangeClientBalance();

	//class AClientAIController* AiController;

	TScriptDelegate<FWeakObjectPtr> MovementCompleteDelegate;

	bool ReadyToGo = false;

	void GoToNewPoint(EDestination Dest);

	void ActionOnMoveComplete();

	EDestination CurrentDest = EDestination::None;

	void BeforeDestroy();

public:	
	
	UFUNCTION()
		void Test(struct FAIRequestID RequestID, EPathFollowingResult::Type Result);

	void SetFoodPreferences();

	void CompleteOrder(bool Result);

	FORCEINLINE float GetClientMoney() { return ClientMoney; };

	FORCEINLINE float GetReallyPrice() {

		float Amount = 0;

		for (FFood Elem: DesiredFood)
		{
			Amount += Elem.GetFoodCost();
		}

		return Amount;
	};

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE TArray<FFood> GetDesiredFood() { return DesiredFood;  };

	void ActionOnInteract();

};
