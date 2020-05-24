// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithTrigger.h"
#include "FastfoodComp.h"
#include "Work.generated.h"

UCLASS()
class GHOSTPROJ_API AWork : public AActorWithTrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWork();

	FORCEINLINE void AddMoney(float Val)
	{
		Money += Val;
	};

	FORCEINLINE float GetMoney()
	{
		return Money;
	};

	FORCEINLINE void SetMoney(float NewVal)
	{
		if (NewVal >= 0)
		{
			Money = NewVal;
		}
	};

	FORCEINLINE void SubstractMoney(float Val)
	{
		Money -= Val;
		if (Money < 0)
		{
			Money = 0;
		}
	};

	UFUNCTION(BlueprintImplementableEvent)
		void CreateInfoWidget(const FString &Text);

	FORCEINLINE FVector GetSpawnpoint() { return Spawnpoint; };

	FORCEINLINE FVector GetOrderPoint() { return OrderPoint; };

	bool CheckWorkTime();

	void SpawnClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ActionOnInteract();
	

	UPROPERTY(EditAnywhere)
		FVector Workplacepoint;

	UPROPERTY(EditAnywhere)
		FVector Spawnpoint;

	UPROPERTY(EditAnywhere)
		FVector OrderPoint;

	float Money = 500;

	UPROPERTY(EditDefaultsOnly)
		UFastfoodComp* FFComp;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AClient> ClientClass;

};
