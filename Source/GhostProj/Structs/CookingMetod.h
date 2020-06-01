// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"


UENUM(BlueprintType)
enum ECookingMetods
{
	METOD_None	UMETA(DisplayName = "None"),
	METOD_Fry	UMETA(DisplayName = "Fry"),
	METOD_Boil	UMETA(DisplayName = "Boil"),
	METOD_Slice	UMETA(DisplayName = "Slice")
};