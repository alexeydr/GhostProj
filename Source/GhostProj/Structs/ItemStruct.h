// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "ItemStruct.generated.h"


USTRUCT()
struct FItemParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

protected:

	UPROPERTY(EditAnywhere)
		FString Name;
	
	UPROPERTY(EditAnywhere)
		class UTexture2D* Texture;
	
public:
	
	FItemParams(FString NewName = "", class UTexture2D* Texture = nullptr)
	{
		this->Name = NewName;
		this->Texture = Texture;

	}


	void AddTexture(class UTexture2D* Texture2D)
	{
		this->Texture = Texture2D;
	}


	void AddName(FString N)
	{
		this->Name = N;
	}


	FString GetName()
	{
		return this->Name;
	}

	class UTexture2D* GetTexture()
	{
		return this->Texture;
	}

	bool operator ==(FItemParams Param)
	{
		if (this->GetName() == Param.GetName() && 
			this->GetTexture() == Param.GetTexture())
		{
			return true;
		}
		return false;
	}

};
