// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACamera::ACamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	/*Camera = CreateDefaultSubobject<AActor>(TEXT("CameraComponent"));
	Camera->SetupAttachment(RootComponent);*/
	
	//OurPlayerController->SetViewTarget(Camera);

}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UE_LOG(LogTemp, Error, TEXT("Player Controller: %d"), *OurPlayerController->GetName());*/
}

