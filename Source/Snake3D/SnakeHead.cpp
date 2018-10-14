// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeHead.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set this pawn to be controlled by the lowest number player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SnakeHead = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SnakeHead"));
	SnakeHead->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();
	
	//CurrentVelocity.X = 50.0f * CurrentDirection;

	//GetWorld()->GetTimerManager().SetTimer(MovementDelay, this, &ASnakeHead::Movement, 0.1f, true);
	GetScreenPosition();
	
}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetScreenPosition();
	Movement();
}

// Called to bind functionality to input
void ASnakeHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Respond every frame to the values of our two movement axis, "MoveX" and "MoveY"
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &ASnakeHead::MoveRight);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &ASnakeHead::MoveLeft);
	InputComponent->BindAction("MoveUp", IE_Pressed, this, &ASnakeHead::MoveUp);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &ASnakeHead::MoveDown);
	InputComponent->BindAction("GetScreenPosition", IE_Pressed, this, &ASnakeHead::GetScreenPosition);

}

void ASnakeHead::Movement()
{
	//if (!CurrentVelocity.IsZero())
	//{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * CurrentDirection);
		SetActorLocation(NewLocation);
	//}

}

void ASnakeHead::MoveRight()
{
	CurrentDirection = 1.0f;

	CurrentVelocity.Y = 0.0f;
	CurrentVelocity.X = 10.0f;
}
void ASnakeHead::MoveLeft()
{
	CurrentDirection = -1.0f;

	CurrentVelocity.Y = 0.0f;
	CurrentVelocity.X = 10.0f;
}

void ASnakeHead::MoveUp()
{
	CurrentDirection = -1.0f;

	CurrentVelocity.Y = 10.0f;
	CurrentVelocity.X = 0.0f;
}
void ASnakeHead::MoveDown()
{
	CurrentDirection = 1.0f;

	CurrentVelocity.Y = 10.0f;
	CurrentVelocity.X = 0.0f;
}

void ASnakeHead::GetScreenPosition()
{
	OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	//Makes sure the Player Controller is not null
	if (!OurPlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Controler attached"));
		return;
	}

	OurPlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenLocation);
	OurPlayerController->GetViewportSize(ScreenWidth, ScreenHeight);

	UE_LOG(LogTemp, Error, TEXT("Screen Width: %d, Screen Height: %d"), ScreenWidth, ScreenHeight);

	ScreenX = (int32)ScreenLocation.X;
	ScreenY = (int32)ScreenLocation.Y;

	UE_LOG(LogTemp, Warning, TEXT("ScreenX %d"), ScreenX);
	UE_LOG(LogTemp, Warning, TEXT("ScreenWidth: %d"), ScreenWidth);

	if (ScreenX > ScreenWidth)
	{
		SetActorLocation(FVector(-ScreenWidth, 0.0f, 0.0f));
	}
	
	if (ScreenX < 0)
	{
		SetActorLocation(FVector(ScreenWidth, 0.0f, 0.0f));
	}

	

	//UE_LOG(LogTemp, Warning, TEXT("Screen X: %d"), ScreenX);
}

