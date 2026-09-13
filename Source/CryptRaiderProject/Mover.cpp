// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	OriginalAngle = GetOwner()->GetActorRotation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = OriginalLocation;
	//FRotator TargetRotator = OriginalAngle;

	if (ShouldMove == true) {
		TargetLocation = OriginalLocation + MoveOffset;
		//TargetRotator = OriginalAngle + NewAngle;
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();

	float Speed = MoveOffset.Length() / MoveTime;
	//float RotationSpeed = AngleOffset.Yaw / MoveTime;


	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation); 

	//FRotator NewAngle = FRotator(0.0f, AngleOffset.Roll, 0.0f);
	//GetOwner()->SetActorRotation(NewAngle);


	
	//Pointer to the Owner Actor
	AActor* Owner = GetOwner();
	FString Name = Owner->GetActorNameOrLabel();
	
	FVector OwnerLocation = Owner->GetActorLocation();
	FString OwnerLocationString = OwnerLocation.ToCompactString();

	

	//UE_LOG(LogTemp, Display, TEXT("Mover Owner Name: %s with location %s "), *Name, *OwnerLocationString);

	// ...
}

void UMover::SetShouldMove(bool NewShouldMove) {
	ShouldMove = NewShouldMove; 
}

