// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GhostProjCharacter.h"
#include "GameFramework/Actor.h"
#include "ActorWithTrigger.generated.h"

class AGhostProjCharacter;

UCLASS(Abstract)
class GHOSTPROJ_API AActorWithTrigger : public AActor
{
protected:
	AGhostProjCharacter* MainChar;
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorWithTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UBoxComponent* BoxComp;

	UPROPERTY()
		USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;
	
	
	UFUNCTION()
		void OnBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
		OnBoxBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult); };
	
	UFUNCTION()
	void OnEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) {
		OnBoxEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void OnBoxEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

	virtual void ActionOnInteract() {};
};
