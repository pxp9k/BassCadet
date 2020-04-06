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
	
}

// Called every frame
void ANinJam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	/*
	CurrentBeatTime += DeltaTime;

	// Check if CurrentBeatTime exceeds BeatTime
	if (CurrentBeatTime > NextBeatTime) {

		float TCorr = CurrentBeatTime - NextBeatTime;

		if(bTickCorrection) {
		
			NextBeatTime = BeatTime - TCorr;					// Correct next ticktime

		} else {
			
			NextBeatTime = BeatTime;		// Uncorrected ...
		}

		UE_LOG(LogTemp, Warning, TEXT("NinJam: NextBeatTime = %f (TCorr = %f)"), NextBeatTime, TCorr);

		CurrentBeatTime = 0;

		OnBeat_Implementation();
	} // */
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

	OnBeat();
}

// Set tempo to new BPM
void ANinJam::SetBPM(int NewBPM)
{
	BeatTime = 60.0f / NewBPM;
	NextBeatTime = BeatTime;
}