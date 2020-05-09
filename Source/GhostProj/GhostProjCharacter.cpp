// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GhostProjCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet\GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Engine\Engine.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "ActorWithTrigger.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStats\InteractActor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AGhostProjCharacter

AGhostProjCharacter::AGhostProjCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	HeroTime = CreateDefaultSubobject<UTimeComp>(FName("TimeComp"));
	Sleepiness = Thirst = MentalCondition = Hunger = 50;
 	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGhostProjCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent); 
	PlayerInputComponent->BindAction("Talk", IE_Pressed, this, &AGhostProjCharacter::Talk);
	PlayerInputComponent->BindAction("OpenInventory", IE_Pressed, this, &AGhostProjCharacter::OpenInventory);
	PlayerInputComponent->BindAction("Music", IE_Pressed, this, &AGhostProjCharacter::CreateMusicPlayer);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AGhostProjCharacter::Interaction);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGhostProjCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGhostProjCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGhostProjCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGhostProjCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AGhostProjCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AGhostProjCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AGhostProjCharacter::OnResetVR);
}

void AGhostProjCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateTime(HeroTime->GetTime());
}


void AGhostProjCharacter::BeginPlay()
{	
	Super::BeginPlay();
	

	this->ShowWidgetUI();
	this->UpdateUI();
}

void AGhostProjCharacter::Talk()
{
	FHitResult OutHit;
	FVector Start = this->GetActorLocation();

	FVector ForwardVector = this->GetFollowCamera()->GetForwardVector();
	FVector End = ((ForwardVector * 1000.f) + Start);
	FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			if (GEngine) {

				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));

			}
		}
	}

}

void AGhostProjCharacter::OpenInventory()
{
	if (FlipFlop)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
		InventoryWidget->RemoveFromParent();
		FlipFlop = false;
		return;
	}


	if (ClassInventory)
	{
		InventoryWidget = CreateWidget<UShopUserWidget>(GetWorld(), ClassInventory);

		if (InventoryWidget)
		{
		
			FlipFlop = true;
			InventoryWidget->AddToViewport();
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
			for (auto Elem : Inventory)
			{
				InventoryWidget->CreateElements(Elem, ClassElementInInventory);
			}
			
		}
		
	}
}

void AGhostProjCharacter::Interaction()
{
	if (InteractActor)
	{
		InteractActor->ActionOnInteract();
	}
}

void AGhostProjCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AGhostProjCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	
	Jump();
}

void AGhostProjCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AGhostProjCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGhostProjCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGhostProjCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGhostProjCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
