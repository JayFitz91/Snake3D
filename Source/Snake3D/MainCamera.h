// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MainCamera.generated.h"

/**
 * 
 */
UCLASS()
class SNAKE3D_API AMainCamera : public ACameraActor
{
	GENERATED_BODY()

public:

	AMainCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/// FUNCTIONS ///
	void SpawnFood();

	/// VARIABLES ///
	APlayerController* OurPlayerController = nullptr;

	///Camera Properties
	FVector2D ScreenLocation;
	int32 ScreenWidth = 0;
	int32 ScreenHeight = 0;
	int32 ScreenX;
	int32 ScreenY;

	void GetScreenPosition();

	UPROPERTY(EditAnywhere)
	AActor* Snake;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFood> MyItemBlueprint;

	FTimerHandle MovementDelay;
};
