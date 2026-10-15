// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "MyAssetAction.generated.h"

/**
 * For objects that are not in game but in memory
 */
UCLASS()
class TOOLING_API UMyAssetAction : public UAssetActionUtility
{
	GENERATED_BODY()
private:
	TMap<UClass*, FString> PrefixMap;
	void InitPrefixMap();
public:
	UFUNCTION(CallInEditor, Category="My Tools")
	void PrintAssetInfo();
	UFUNCTION(CallInEditor, Category="My Tools")
	void AddPrefix();
	UFUNCTION(CallInEditor, Category="My Tools")
	void DuplicateSelected();
	
};
