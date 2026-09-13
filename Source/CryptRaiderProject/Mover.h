// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

//This is Unreal Engine specified syntax
//Unreal Header Tool sees these lines of code and say 
//"I need to go and add a bunch of features to the project" such
//as functions
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDERPROJECT_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool NewShouldMove);

private: 
	//Defines the moveOffset
	UPROPERTY(EditAnywhere);
	FVector MoveOffset; 

	//UPROPERTY(EditAnywhere);
	//FRotator AngleOffset;

	//Defines the time it takes for the target
	UPROPERTY(EditAnywhere);
	float MoveTime = 4;

	//Boolean for whether an object should move
	bool ShouldMove = false; 

	FVector OriginalLocation;
	FRotator OriginalAngle;
};
