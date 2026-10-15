// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetAction.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "EditorUtilityBlueprint.h"
void UMyAssetAction::InitPrefixMap()
{
	PrefixMap.Add(UStaticMesh::StaticClass(), TEXT("SM_"));
	PrefixMap.Add(USkeletalMesh::StaticClass(), TEXT("SKM_"));
	PrefixMap.Add(UTexture2D::StaticClass(), TEXT("T_"));
	PrefixMap.Add(UMaterial::StaticClass(), TEXT("M_"));
	PrefixMap.Add(UMaterialInstance::StaticClass(), TEXT("MI_"));
	PrefixMap.Add(UBlueprint::StaticClass(), TEXT("BP_"));
	PrefixMap.Add(UEditorUtilityBlueprint::StaticClass(), TEXT("EUB_"));
}

void UMyAssetAction::PrintAssetInfo()
{
	TArray<UObject*> selectedAssets = UEditorUtilityLibrary::GetSelectedAssets();
	for(UObject* asset : selectedAssets)
	{
		if (!asset) continue; // IF POINTER NULL SKIP

		UE_LOG(LogTemp, Warning, TEXT("Asset: %s | Classe: %s | Path: %s")
			, *asset->GetName()
			, *asset->GetClass()->GetName()
			, *asset->GetPathName());
	}
	UE_LOG(LogTemp, Warning, TEXT("Total selected assets: %d"), selectedAssets.Num());
}

void UMyAssetAction::AddPrefix()
{
	InitPrefixMap();
	TArray<UObject*> selectedAssets = UEditorUtilityLibrary::GetSelectedAssets();
	for (UObject* asset : selectedAssets)
	{
		if (!asset) continue; // IF POINTER NULL SKIP
		FString* prefix = PrefixMap.Find(asset->GetClass());
		if (!prefix) 
		{
			UE_LOG(LogTemp, Warning, TEXT("No prefix found in map for: %s"), *asset->GetClass()->GetName());
			continue;
		}
			
		FString currentName = asset->GetName();
		if (currentName.StartsWith(*prefix)) continue;
		FString newName = *prefix + currentName;
		FString packagePath = FPackageName::GetLongPackagePath(asset->GetOutermost()->GetName());
		UEditorAssetLibrary::RenameAsset(asset->GetPathName(), packagePath + TEXT("/") + newName);
	}
}

void UMyAssetAction::DuplicateSelected() 
{
	TArray<UObject*> selectedAssets = UEditorUtilityLibrary::GetSelectedAssets();
	if (selectedAssets.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("No asset have been selected"));
		return;
	}
	for (UObject* asset : selectedAssets)
	{
		if (!asset) continue; // IF POINTER NULL SKIP

		FString packagePath = FPackageName::GetLongPackagePath(asset->GetOutermost()->GetName());
		FString currentName = asset->GetName();
		FString newName = currentName + TEXT("_Copy");
		FString newPath = packagePath + TEXT("/") + newName;

		UObject* duplicatedOBJ = UEditorAssetLibrary::DuplicateAsset(asset->GetPathName(), newPath);
		if (duplicatedOBJ) {
			UEditorAssetLibrary::SaveAsset(newPath, false);
			UE_LOG(LogTemp, Log, TEXT("The asset '%s' has been duplicated into '%s'"), *asset->GetName(), *duplicatedOBJ->GetName());
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Impossible to duplicated asset '%s'"), *asset->GetName());

	}

}
