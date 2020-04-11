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

	//  NAME -> MIDI Look up table for sharp notes
	TMap<FString, int> Name2MidiSharp = {

		{ "A",	0 },
		{ "A#",	1 },
		{ "B",	2 },
		{ "C",	3 },
		{ "C#",	4 },
		{ "D",	5 },
		{ "D#",	6 },
		{ "E",	7 },
		{ "F",	8 },
		{ "F#",	9 },
		{ "G",	10 },
		{ "G#",	11 }
	};

	//  NAME -> MIDI Look up table for flat notes
	TMap<FString, int> Name2MidiFlat = {

		{ "A",	0 },
		{ "Bb",	1 },
		{ "B",	2 },
		{ "C",	3 },
		{ "Db",	4 },
		{ "D",	5 },
		{ "Eb",	6 },
		{ "E",	7 },
		{ "F",	8 },
		{ "Gb",	9 },
		{ "G",	10 },
		{ "Ab",	11 }
	};

	// MIDI -> NAME Look up table for sharp notes
	TMap<int, FString> Midi2NameSharp = {

		{ 0, "A"	},
		{ 1, "A#"	},
		{ 2, "B"	},
		{ 3, "C"	},
		{ 4, "C#"	},
		{ 5, "D"	},
		{ 6, "D#"	},
		{ 7, "E"	},
		{ 8, "F"	},
		{ 9, "F#"	},
		{ 10, "G"	},
		{ 11, "G#"	}
	};

	// MIDI -> NAME Look up table for flat notes
	TMap<int, FString> Midi2NameFlat = {

		{ 0, "A"	},
		{ 1, "Bb"	},
		{ 2, "B"	},
		{ 3, "C"	},
		{ 4, "Db"	},
		{ 5, "D"	},
		{ 6, "Eb"	},
		{ 7, "E"	},
		{ 8, "F"	},
		{ 9, "Gb"	},
		{ 10, "G"	},
		{ 11, "Ab"	}
	};

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
	
	// Convert a Midi Root note (int) to a readable string (sharp/flat)
	UFUNCTION(BlueprintCallable, Category = "NinJam")
	FString MidiRoot2Note(int MidiNote, bool bFlat = false);		// returns a flat note if bFlat = true, else sharps

	UFUNCTION(BlueprintCallable, Category = "NinJam")
	int GetMidiRoot(FString ChordName);

	// Find the notes of a specified chord and return a TArray of FStrings of it
	UFUNCTION(BlueprintCallable, Category = "NinJam")
	TArray<FString> GetChordNotes(FString ChordName);
};