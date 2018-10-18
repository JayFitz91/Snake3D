// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeHead.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"


// Sets default values
ASnakeHead::ASnakeHead()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set this pawn to be controlled by the lowest number player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	_collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	_collider->SetHiddenInGame(false);
	_collider->OnComponentBeginOverlap.AddDynamic(this, &ASnakeHead::OnOverlapBegin);

	RootComponent = _collider;

	SnakeHead = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SnakeHead"));
	SnakeHead->SetupAttachment(RootComponent);

	//OnActorBeginOverlap.AddDynamic(this, &ASnakeHead::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GetScreenPosition();
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

void ASnakeHead::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PICKED UP!")));

	if (OtherActor && (OtherActor != this))
	{
		OtherActor->Destroy();
	}
}


