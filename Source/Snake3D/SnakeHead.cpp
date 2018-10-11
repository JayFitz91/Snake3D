// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeHead.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set this pawn to be controlled by the lowest number player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentVelocity.X = 50.0f * CurrentDirection;

	//GetWorld()->GetTimerManager().SetTimer(5.0f, this, &ASnakeHead::MoveRight, 5.0f, false);
	GetWorld()->GetTimerManager().SetTimer(MovementDelay, this, &ASnakeHead::Movement, 0.2f, true);
}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ASnakeHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Respond every frame to the values of our two movement axis, "MoveX" and "MoveY"
	//InputComponent->BindAxis("MoveX", this, &ASnakeHead::Move_XAxis);
	//InputComponent->BindAxis("MoveY", this, &ASnakeHead::Move_YAxis);

	InputComponent->BindAction("MoveRight", IE_Pressed, this, &ASnakeHead::MoveRight);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &ASnakeHead::MoveLeft);
	InputComponent->BindAction("MoveUp", IE_Pressed, this, &ASnakeHead::MoveUp);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &ASnakeHead::MoveDown);

}

//void ASnakeHead::MoveRight(float AxisValue)
//{
//	//move at 100 units per second forward or backward
//	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
//}
//
//void ASnakeHead::MoveLeft(float AxisValue)
//{
//	//Move at 00 units per second right or left
//	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
//}


void ASnakeHead::Movement()
{
	//if (!CurrentVelocity.IsZero())
	//{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * CurrentDirection);
		SetActorLocation(NewLocation);
	//}

	UE_LOG(LogTemp, Warning, TEXT("Move Right function executed"));
}

void ASnakeHead::MoveRight()
{
	CurrentDirection = 1.0f;

	CurrentVelocity.Y = 0.0f;
	CurrentVelocity.X = 50.0f;

}
void ASnakeHead::MoveLeft()
{
	CurrentDirection = -1.0f;

	CurrentVelocity.Y = 0.0f;
	CurrentVelocity.X = 50.0f;
}

void ASnakeHead::MoveUp()
{
	CurrentDirection = -1.0f;

	CurrentVelocity.Y = 50.0f;
	CurrentVelocity.X = 0.0f;
}
void ASnakeHead::MoveDown()
{
	CurrentDirection = 1.0f;

	CurrentVelocity.Y = 50.0f;
	CurrentVelocity.X = 0.0f;
}

