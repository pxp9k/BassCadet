// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimerManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NinJam.generated.h"

USTRUCT(Blueprintable)
struct FChordData{

	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TArray <FString> NameAliases;		// ptr on alias (names) array
	
	UPROPERTY(BlueprintReadWrite)
	TArray <int> MidiIntervals;		// intervals in miditones relative to root

};

UCLASS()
class NINSESSION_API ANinJam : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ANinJam();

	// Beats Per Interval
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	int BPI = 8;

	// Determines the type of beat (3rd... 4th... etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	int Nth = 4;

	// Beat Per Minute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	float BPM = 60.0f;

	float BeatTime = 60.0f / BPM;
	float NextBeatTime = BeatTime;
	float CurrentBeatTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	int CurrentBar = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	int CurrentBeat = 0;

	// Tick Correction Flag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	bool bTickCorrection = true;

	// Number of Grains per bar (default = 48)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	float Granularity = 48;

	FTimerHandle BeatTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	bool bClick = true;

	// *** CHORDS ***

	// Chords TArray (holds all known chords and their invtervals)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	TArray<FChordData> Chord;

	// Chord DB as a simple string array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NinJam)
	TArray<FString> ChordDBTextArray;

	// Load chord database from textfile in the app directory
	UFUNCTION(BlueprintCallable, Category = "ChordDB")
	TArray<FString> ReadChordDB();

	// Scan a loaded chord textfile split into a TArray for chords and 
	// return it as a Chord TMap (Key = chordname)
	UFUNCTION(BlueprintCallable, Category = "ChordDB")
	TArray<FChordData> ScanForChords(TArray<FString> ChordDBText);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "NinJam")
	void OnBeat();

	UFUNCTION(BlueprintCallable, Category = "NinJam")
	void SetBPM(int NewBPM);

	UFUNCTION(BlueprintCallable, Category = "NinJam")
	TArray<int> GetChordMidiIntervals(FString ChordName);
};