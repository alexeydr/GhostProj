// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimeComp.h"
#include "BankCardComp.h"
#include "CharacterStats\InteractActor.h"
#include "UI\UI Items In Storage\BaseElementInStorage.h"
#include "UI\ShopUserWidget.h"
#include "GhostProjCharacter.generated.h"


UENUM()
enum class EActionWithItem : uint8
{
	None 	UMETA(DisplayName = "None"),
	Add 	UMETA(DisplayName = "Add"),
	Remove	UMETA(DisplayName = "Remove")
};



UCLASS(config=Game)
class AGhostProjCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AGhostProjCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
	float Sleepiness;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
	float Hunger;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
	float Thirst;

	float MentalCondition;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
	float Money = 100;

	class AActorWithTrigger* ActWithTrig;
	
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateTime(FMyDateTime NewTime);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateUI();

	UPROPERTY()
	UTimeComp* HeroTime;

	UFUNCTION(BlueprintCallable)
		UBankCardComp* GetBankCard() { return BankCard; };


	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UBaseElementInStorage> ClassElementInInventory;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UShopUserWidget> ClassInventory;

	void UpdateInventory(AInteractActor* Act, EActionWithItem Action, int ItemNumber = -1);


	FORCEINLINE TArray<AInteractActor*> GetInventory() { return this->Inventory; };

protected:

	void RemoveItemFromInventory(AInteractActor* Act, int ItemNumber = -1);

	UPROPERTY()
		UBankCardComp* BankCard;

	void ActiveInteractWidget(AActor* InteractActor);

	AActor* InteractActor;

	void ActionWithActor(AActor* Act);

	AActor* LineTrace();
	
	UFUNCTION(BlueprintImplementableEvent)
		void CreateMusicPlayer();

	UShopUserWidget* InventoryWidget;

	bool FlipFlop = false;

	UPROPERTY()
	TArray<AInteractActor*> Inventory;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void ShowWidgetUI();
	
	void Talk();

	UFUNCTION()
		void OpenInventory();

	void Interaction();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void Tick(float DeltaTime) override;
};

