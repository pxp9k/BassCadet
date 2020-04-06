// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimerManager.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PulseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NINSESSION_API UPulseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPulseComponent();

	// Beats Per Interval
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pulse)
	float BPI = 16;

	// Determines the type of beat (3rd... 4th... etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pulse)
	float Nth = 4;

	// Beat Per Minute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pulse)
	float BPM = 120.0f;

	// Number of Grains per bar (default = 48)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pulse)
	float Granularity = 48;

	FTimerHandle BeatTimerHandle;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pulse")
	void OnBeat();
};
