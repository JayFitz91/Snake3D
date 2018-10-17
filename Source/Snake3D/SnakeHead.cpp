// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeHead.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Food.h"

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

	//GetWorld()->SpawnActor<AFood>(MyItemBlueprint, FVector(0.0f, 0.f, 0.f), FRotator(0.0f, 0.f, 0.f), FActorSpawnParameters());
	
}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetScreenPosition();
	Movement(DeltaTime);
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

void ASnakeHead::Movement(float DeltaTime)
{
	//if (!CurrentVelocity.IsZero())
	//{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * CurrentDirection) * DeltaTime;
		SetActorLocation(NewLocation);
	//}

}

void ASnakeHead::MoveRight()
{
	CurrentDirection = 1.0f;

	CurrentVelocity.Y = 0.0f;
	CurrentVelocity.X = MoveSpeed;
}
void ASnakeHead::MoveLeft()
{
	CurrentDirection = -1.0f;

	CurrentVelocity.Y = 0.0f;
	CurrentVelocity.X = MoveSpeed;
}

void ASnakeHead::MoveUp()
{
	CurrentDirection = -1.0f;

	CurrentVelocity.Y = MoveSpeed;
	CurrentVelocity.X = 0.0f;
}
void ASnakeHead::MoveDown()
{
	CurrentDirection = 1.0f;

	CurrentVelocity.Y = MoveSpeed;
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

	UE_LOG(LogTemp, Warning, TEXT("ScreenX %d, ScreenY %d"), ScreenX, ScreenY);
	UE_LOG(LogTemp, Warning, TEXT("ScreenWidth: %d"), ScreenWidth);

	FString DebugMessage = FString::Printf(TEXT("ScreenX %d, ScreenY %d"), ScreenX, ScreenY);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, DebugMessage);

	if (GetActorLocation().X > ScreenWidth / 2)
	{
		UE_LOG(LogTemp, Error, TEXT("Out of View"));
		SetActorLocation(FVector(-ScreenWidth / 2, GetActorLocation().Y, 0.0f));
	}
	
	else if (GetActorLocation().X < (-ScreenWidth / 2))
	{
		SetActorLocation(FVector(ScreenWidth / 2, GetActorLocation().Y, 0.0f));
		UE_LOG(LogTemp, Error, TEXT("Out of View"));
	}

	if (GetActorLocation().Y > ScreenHeight / 2)
	{
		SetActorLocation(FVector(GetActorLocation().X, -ScreenHeight / 2, 0.0f));
		UE_LOG(LogTemp, Error, TEXT("Out of View"));
	}

	else if (GetActorLocation().Y < (-ScreenHeight / 2))
	{
		SetActorLocation(FVector(GetActorLocation().X, ScreenHeight / 2, 0.0f));
		UE_LOG(LogTemp, Error, TEXT("Out of View"));
	}

	//UE_LOG(LogTemp, Warning, TEXT("Screen X: %d"), ScreenX);
}

