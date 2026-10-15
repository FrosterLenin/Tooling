// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorActionUtility.h"
#include "MyActorActionUtility.generated.h"

/**
 * For objects that are in the field of the game
 */
UCLASS()
class TOOLING_API UMyActorActionUtility : public UActorActionUtility
{
	GENERATED_BODY()

public:
	UFUNCTION(CallInEditor, Category = "My Tools | Transform")
	void SnapRotationToZero();
	UFUNCTION(CallInEditor, Category = "My Tools | Transform")
	void SnapLocationZToGround();
	UFUNCTION(CallInEditor, Category = "My Tools | Transform")
	void DuplicateActorWithXOffset();
	UFUNCTION(CallInEditor, Category = "My Tools | Transform")
	void AlignToXOfFirstSelection();
	UFUNCTION(CallInEditor, Category = "My Tools | Transform")
	void PrintComponentList();
	UFUNCTION(CallInEditor, Category = "My Tools | Transform")
	void ScatterOnGrid();

};
