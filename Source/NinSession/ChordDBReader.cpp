// Fill out your copyright notice in the Description page of Project Settings.

#include "ChordDBReader.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
UChordDBReader::UChordDBReader()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UChordDBReader::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UChordDBReader::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FString> UChordDBReader::ReadChordDB()
{
	TArray<FString> ChordDBTextArray;

	FString FileName = FPaths::ConvertRelativePathToFull(FPaths::GameDir()) + "/Chords.txt";
	
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FileName))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("File not found..."));
		return ChordDBTextArray;
	}

	FFileHelper::LoadFileToStringArray(ChordDBTextArray, *FileName);
	return ChordDBTextArray;
 
}

// Scan a chord formula out of a given chord database text
TArray<FString> UChordDBReader::ScanForChords(TArray<FString> ChordDBText) {

	TArray<FString> ScannedChords;
	FString ScnLine;

	for (int i = 0; i < ChordDBText.Num(); i++) {

		// Scan each line in the chord DB text
		ScnLine = ChordDBText[i];

		// Remove all leading spaces
		ScnLine.RemoveFromStart(" ");

		// Keep only the left side starting from "//" (remove remarks)
		FString NLine;
		if (ScnLine.Find("//") > -1) {
			NLine = ScnLine.Left(ScnLine.Find("//"));
		}
		else {
			NLine = ScnLine;
			if (NLine.Len() > 1) {
				ScannedChords.Add(NLine);
				UE_LOG(LogTemp, Warning, TEXT("ScanChordFormula %s"), *NLine);
			}
		}
	}
	return ScannedChords;
}