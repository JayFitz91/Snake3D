// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "SnakeHead.generated.h"

UCLASS()
class SNAKE3D_API ASnakeHead : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakeHead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	//UStaticMeshComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SnakeHead = nullptr;

	void Movement(float DeltaTime);

	///Input Functions
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	
	//Input Variables
	UPROPERTY(VisibleAnywhere)
	FVector CurrentVelocity;

	//Value between 1.0f and -1.0f that tracks direction
	UPROPERTY(VisibleAnywhere)
	float CurrentDirection = 1.0f;

	//Movement speed of the snake
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 100.0f;
};
