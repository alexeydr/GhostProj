// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"
#include "Components\StaticMeshComponent.h"
#include "Engine\World.h"
#include "Components\StaticMeshComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components\SceneComponent.h"
#include "GhostProjCharacter.h"
#include "Kismet\GameplayStatics.h"

AInteractActor::AInteractActor()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	RootComponent = Root;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));
	StaticMesh->AttachTo(Root);
}

void AInteractActor::BeginPlay()
{
	Super::BeginPlay();

	MainChar = Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	
}

void AInteractActor::CreateInteractWidget()
{
	APlayerController* PC = Cast<APlayerController>(MainChar->GetController());
	if (PC && InteractWidget)
	{

		UInteractWithItem* WidgetRef = CreateWidget<UInteractWithItem>(GetWorld(), InteractWidget);

		if (WidgetRef)
			WidgetRef->AddToViewport();
		else
			return;

		WidgetRef->SetItem(this);
		PC->bShowMouseCursor = true;
		UWidgetBlueprintLibrary::SetInputMode_UIOnly(PC,WidgetRef);
	}

}

void AInteractActor::ActionOnInteract()
{
	this->CreateInteractWidget();
}
