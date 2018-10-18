// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Food.h"

// Sets default values
AMainCamera::AMainCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	//Finds the first player controller (player 0)
	OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UE_LOG(LogTemp, Error, TEXT("Player Controller: %d"), *OurPlayerController->GetName());

	//Makes sure the Player Controller is not null
	if (!OurPlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Controler attached"));
		return;
	}

	//Return the viewport size
	OurPlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
	UE_LOG(LogTemp, Error, TEXT("Screen Width: %d, Screen Height: %d"), ScreenWidth, ScreenHeight);

	OurPlayerController->ProjectWorldLocationToScreen(Snake->GetActorLocation(), ScreenLocation);

	//Invoke the method for spawning food into the scene
	GetWorld()->GetTimerManager().SetTimer(MovementDelay, this, &AMainCamera::SpawnFood, 1.0f, true);
}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetScreenPosition();

}

void AMainCamera::GetScreenPosition()
{
	
	
	ScreenX = (int32)ScreenLocation.X;
	ScreenY = (int32)ScreenLocation.Y;

	UE_LOG(LogTemp, Warning, TEXT("ScreenX %d, ScreenY %d"), ScreenX, ScreenY);
	UE_LOG(LogTemp, Warning, TEXT("ScreenWidth: %d"), ScreenWidth);

	/*FString DebugMessage = FString::Printf(TEXT("ScreenX %d, ScreenY %d"), ScreenX, ScreenY);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, DebugMessage);*/

	if (Snake->GetActorLocation().X > ScreenWidth / 2)
	{
		//UE_LOG(LogTemp, Error, TEXT("Out of View"));
		Snake->SetActorLocation(FVector(-ScreenWidth / 2, Snake->GetActorLocation().Y, 0.0f));
	}

	else if (Snake->GetActorLocation().X < (-ScreenWidth / 2))
	{
		Snake->SetActorLocation(FVector(ScreenWidth / 2, Snake->GetActorLocation().Y, 0.0f));
		//UE_LOG(LogTemp, Error, TEXT("Out of View"));
	}

	if (Snake->GetActorLocation().Y > ScreenHeight / 2)
	{
		Snake->SetActorLocation(FVector(Snake->GetActorLocation().X, -ScreenHeight / 2, 0.0f));
		//UE_LOG(LogTemp, Error, TEXT("Out of View"));
	}

	else if (Snake->GetActorLocation().Y < (-ScreenHeight / 2))
	{
		Snake->SetActorLocation(FVector(Snake->GetActorLocation().X, ScreenHeight / 2, 0.0f));
		//UE_LOG(LogTemp, Error, TEXT("Out of View"));
	}

	//UE_LOG(LogTemp, Warning, TEXT("Screen X: %d"), ScreenX);
}

void AMainCamera::SpawnFood()
{
	/*FVector WorldLocation;
	FVector WorldDirection;

	OurPlayerController->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);*/

	GetWorld()->SpawnActor<AFood>(MyItemBlueprint, FVector(FMath::RandRange(-(int32)ScreenLocation.X, (int32)ScreenLocation.X), FMath::RandRange(-(int32)ScreenLocation.Y, (int32)ScreenLocation.Y), 0.f), FRotator(0.0f, 0.f, 0.f), FActorSpawnParameters());
}
