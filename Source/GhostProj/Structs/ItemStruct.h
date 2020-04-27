// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "ItemStruct.generated.h"

/**
 * 
 */
UENUM()
enum class EStats : uint8
{
	None 	UMETA(DisplayName = "None"),
	Sleepiness 	UMETA(DisplayName = "Sleepiness"),
	Hunger	UMETA(DisplayName = "Hunger"),
	Thirst	UMETA(DisplayName = "Thirst")
};


USTRUCT(BlueprintType)
struct FItemParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

private:

	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		EStats TypeActor;
	UPROPERTY(EditAnywhere)
		int Value;
	UPROPERTY(EditAnywhere)
		class UTexture2D* Texture;
	UPROPERTY(EditAnywhere)
		UClass* ClassItem;
public:
	
	FItemParams(FString NewName = "", EStats NewTypeActor = EStats::None, int NewValue = 0)
	{
		this->Name = NewName;
		this->TypeActor = NewTypeActor;
		this->Value = NewValue;
	}

	void AddName(FString N)
	{
		this->Name = N;
	}

	void AddType(EStats TA)
	{
		this->TypeActor = TA;
	}

	void AddValue(int V)
	{
		this->Value = V;
	}

	void AddTexture(class UTexture2D* Texture2D)
	{
		this->Texture = Texture2D;
	}

	void AddClass(UClass* NewClass)
	{
		this->ClassItem = NewClass;
	}

	FString GetName()
	{
		return this->Name;
	}

	EStats GetType()
	{
		return this->TypeActor;
	}

	int GetValue()
	{
		return this->Value;
	}

	class UTexture2D* GetTexture()
	{
		return this->Texture;
	}

	UClass* GetClassItem()
	{
		return this->ClassItem;
	}

};
