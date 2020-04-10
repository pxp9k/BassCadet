// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/UnrealString.h"
#include "Components/ActorComponent.h"
#include "ChordDBReader.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NINSESSION_API UChordDBReader : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UChordDBReader();

	// Chord DB as a simple string array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	TArray<FString> ChordDBTextArray;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Load chord database from textfile in the app directory
	UFUNCTION(BlueprintCallable, Category = "ChordDB")
	TArray<FString> ReadChordDB();

	// Scan a loaded chord textfile split into a TArray for chords and store it 
	// in another TArray as "formulas" (each chord = 1 string)
	UFUNCTION(BlueprintCallable, Category = "ChordDB")
	TArray<FString> ScanForChords(TArray<FString> ChordDBText);
};