// Fill out your copyright notice in the Description page of Project Settings.


#include "NinJam.h"

// Sets default values
ANinJam::ANinJam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANinJam::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("NinJam: BeginPlay() ... BPM = %f"), BPM);

	// Set up our beat timer
	GetWorld()->GetTimerManager().SetTimer(BeatTimerHandle, this, &ANinJam::OnBeat_Implementation, BeatTime, true);

	TArray<FString> CDBSourceTxt = ReadChordDB();
	Chord = ScanForChords(CDBSourceTxt);
}

// Called every frame
void ANinJam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Chord (Reader) Functions
TArray<FString> ANinJam::ReadChordDB()
{
	FString FileName = FPaths::ConvertRelativePathToFull(FPaths::GameDir()) + "/Chords.txt";

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FileName))
	{
		GEngine->AddOnScreenDebugMessage(-1, 21.f, FColor::Red, TEXT("Chord File not found..."));
		return ChordDBTextArray;
	}

	FFileHelper::LoadFileToStringArray(ChordDBTextArray, *FileName);
	return ChordDBTextArray;

}

// Scan a chord formula out of a given chord database text
TArray<FChordData> ANinJam::ScanForChords(TArray<FString> ChordDBText) {

	TArray <FChordData> ChordMap;	// this is what we look for...

	TArray <FString> ScannedChords;
	FString ScnLine;

	// Remove all leading spaces and remarks
	for (int i = 0; i < ChordDBText.Num(); i++) {
		ChordDBText[i].RemoveFromStart(" ");		
	}

	for (int i = 0; i < ChordDBText.Num(); i++) {

		// Scan each line in the chord DB text
		ScnLine = ChordDBText[i];

		// Remove all leading spaces
		ScnLine.RemoveFromStart(" ");

		// If line not starts with "//"
		FString NLine;
		if (ScnLine.Find("//") <= -1 && ScnLine.Len() > 0) {
			
			//UE_LOG(LogTemp, Warning, TEXT("NinJam: Textline %s"), *ChordDBText[i]);

			// Scan Chordnames/Aliases
			FString ChordNames;	// Name of chord
			do {
				ChordNames.Append(ChordDBText[i++]);
				ScnLine = ChordDBText[i];
				ScnLine.RemoveFromStart(" ");
			} while (ScnLine.Right(1).Equals(","));
			
			// Scan MIDI intervals
			FString IntervalStr;
			do {
				IntervalStr.Append(ChordDBText[i++]);
				ScnLine = ChordDBText[i];
				ScnLine.RemoveFromStart(" ");
			} while (ScnLine.Right(1).Equals(","));

			UE_LOG(LogTemp, Warning, TEXT("NinJam: Chord: %s --> %s"), *ChordNames, *IntervalStr);

			TArray<FString> CN;
			ChordNames.ParseIntoArray(CN, TEXT(","));

			TArray<FString> IntStr;
			IntervalStr.ParseIntoArray(IntStr, TEXT(","));

			TArray<int> IntInt;
			for (int i = 0; i < IntStr.Num(); i++) {
				IntInt.Add(FCString::Atoi(*IntStr[i]));
			}

			FChordData CD;
			CD.NameAliases = CN;
			CD.MidiIntervals = IntInt;

			ChordMap.Add(CD);
		}

	}  

	return ChordMap;	// return TArray to blueprint (or caller)
}

// Called every beat
void ANinJam::OnBeat_Implementation()
{

	CurrentBeat++;

	if (CurrentBeat > Nth) {
		CurrentBeat = 1;
		CurrentBar++;
		if (CurrentBar > BPI) {
			CurrentBar = 1;
		}
	}

	OnBeat();	// Call Blueprint code
}

// Set tempo to new BPM
void ANinJam::SetBPM(int NewBPM)
{
	BeatTime = 60.0f / NewBPM;
	NextBeatTime = BeatTime;
}

// Get Interval Array from a given Chord string
TArray<int> ANinJam::GetChordMidiIntervals(FString ChordName)
{
	TArray<int> Intervals;

	UE_LOG(LogTemp, Warning, TEXT("NinJam: ChordNum() = %d"), Chord.Num());

	for (int i = 0; i < Chord.Num(); i++) {

		for (int j = 0; j < Chord[i].NameAliases.Num(); j++) {

			FString NA = Chord[i].NameAliases[j];

			UE_LOG(LogTemp, Warning, TEXT("NinJam: NA = %s"), *NA);

			if (ChordName.Equals(NA)) {
				
				// Found the chord
				return Chord[i].MidiIntervals;
			}
		}
	}	
	return Intervals;
}
