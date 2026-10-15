// Fill out your copyright notice in the Description page of Project Settings.



#include "MyActorActionUtility.h"
#include "Subsystems/EditorActorSubsystem.h"
#include "Editor.h"
#include "Selection.h"

void UMyActorActionUtility::SnapRotationToZero()
{
	// GEditor is a global pointer to the editor
	UEditorActorSubsystem* actorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	TArray<AActor*> selectedActors = actorSubsystem->GetSelectedLevelActors();

	// This is only another way to retrieve the selected actors in game editor
	USelection* selection = GEditor->GetSelectedActors();
	TArray<AActor*> selectedActorsWithSelection;
	selection->GetSelectedObjects<AActor>(selectedActorsWithSelection);

	// We need to save the operation in a transaction so we know the history
	// of the operations and we can do undo/redo (ctrl z, ctrl y)
	GEditor->BeginTransaction(FText::FromString("Snap rotation to zero"));
	for (AActor* actor : selectedActors) {
		if (!actor) continue;
		actor->Modify(); // Log an update into the actor on the editor transaction
		actor->SetActorRotation(FRotator::ZeroRotator);
	}
	GEditor->EndTransaction();
	UE_LOG(LogTemp, Warning, TEXT("Rotation to Zero on %d actor"), selectedActors.Num());

}

void UMyActorActionUtility::SnapLocationZToGround()
{
	UEditorActorSubsystem* actorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	TArray<AActor*> selectedActors = actorSubsystem->GetSelectedLevelActors();

	GEditor->BeginTransaction(FText::FromString("Snap Z location to ground"));
	for (AActor* actor : selectedActors) {
		if (!actor) continue;
		actor->Modify(); // Log an update into the actor on the editor transaction
		FVector currentLocation = actor->GetActorLocation();
		currentLocation.Z = 0.0;
		actor->SetActorLocation(currentLocation);
		// this is another way
		// actor->GetActorLocation().Set(currentLocation.X, currentLocation.Y, 0.0);
	}
	GEditor->EndTransaction();
	UE_LOG(LogTemp, Warning, TEXT("Location Z to ground on %d actor"), selectedActors.Num());
} 

void UMyActorActionUtility::DuplicateActorWithXOffset()
{
	UEditorActorSubsystem* actorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	TArray<AActor*> selectedActors = actorSubsystem->GetSelectedLevelActors();

	GEditor->BeginTransaction(FText::FromString("Snap with X offset"));
	for (AActor* actor : selectedActors) {
		if (!actor) continue;
		
		AActor* duplicatedActor = actorSubsystem->DuplicateActor(actor);
		if (!duplicatedActor) continue;

		FVector newLocation = actor->GetActorLocation() + FVector(100.0, 0.0, 0.0);
		duplicatedActor->SetActorLocation(newLocation);
	}
	GEditor->EndTransaction();
	UE_LOG(LogTemp, Warning, TEXT("Duplicated %d actors with X Offset"), selectedActors.Num());
}

void UMyActorActionUtility::AlignToXOfFirstSelection()
{
	UEditorActorSubsystem* actorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	TArray<AActor*> selectedActors = actorSubsystem->GetSelectedLevelActors();
	if (selectedActors.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("Nothing have been selected"));
		return;
	}
	if (selectedActors.Num() < 2) {
		UE_LOG(LogTemp, Warning, TEXT("Need at least 2 actors to be selected"));
		return;
	}
	AActor* firstActor = MoveTemp(selectedActors[0]);
	if (!firstActor) {
		UE_LOG(LogTemp, Warning, TEXT("Problem retrieving the first actor"));
		return;
	}
	selectedActors.RemoveAt(0);
	GEditor->BeginTransaction(FText::FromString("Snap with X offset"));
	for (AActor* actor : selectedActors) {
		if (!actor) continue;

		FVector newLocation = actor->GetActorLocation();
		newLocation.X = firstActor->GetActorLocation().X;
		actor->SetActorLocation(newLocation);
	}
	GEditor->EndTransaction();
	UE_LOG(LogTemp, Warning, TEXT("Aligned %d actors to the X of the first"), selectedActors.Num() - 1);
}

void UMyActorActionUtility::PrintComponentList()
{
	UEditorActorSubsystem* actorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	TArray<AActor*> selectedActors = actorSubsystem->GetSelectedLevelActors();

	for (AActor* actor : selectedActors) {
		if (!actor) continue;

		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *actor->GetName());
		for (UActorComponent* component : actor->GetComponents()) {
			if (!component) continue;
			UE_LOG(LogTemp, Warning, TEXT("Component: %s (type = %s)"), *component->GetName(), *component->GetClass()->GetName());
		}
	}
}

void UMyActorActionUtility::ScatterOnGrid()
{
	UEditorActorSubsystem* actorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	TArray<AActor*> selectedActors = actorSubsystem->GetSelectedLevelActors();
	if (selectedActors.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("Nothing have been selected"));
		return;
	}
	int32 totalSelected = selectedActors.Num();
	int32 columns = FMath::CeilToInt(FMath::Sqrt(static_cast<float>(totalSelected)));
	int32 rows = FMath::CeilToInt(static_cast<float>(totalSelected) / columns);
	float gridSpacing = 200.f;

	GEditor->BeginTransaction(FText::FromString("Align to grid"));
	FVector origin = selectedActors[0]->GetActorLocation();
	for (int32 i = 0; i < totalSelected; ++i) {
		AActor* actor = selectedActors[i];
		if (!actor) continue;
		actor->Modify();
		int32 currentRow = i / columns;
		int32 currentColumns = i % columns;

		FVector newLocation = origin + FVector(currentColumns * gridSpacing, currentRow * gridSpacing, 0.f);
		actor->SetActorLocation(newLocation);
	}

	GEditor->EndTransaction();
	UE_LOG(LogTemp, Warning, TEXT("Aligned %d actors to the grid"), selectedActors.Num());

}
