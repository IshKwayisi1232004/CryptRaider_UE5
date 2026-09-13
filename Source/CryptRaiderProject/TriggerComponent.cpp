// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//b is a prefix for boolean type
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Display, TEXT("Constructing"));

	// ...
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Trigger Component Alive!"));
}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//This line is needed in order to call the parent class's 
	//TickComponent function. In this case, the parent class is 
	//UBoxComponent. If this isn't done, we are bypassing any sort of
	//functionality, leading to crashes.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Mover == nullptr) {
		return; 
	}

	AActor* Actors = GetAcceptableActor();
	if (Actors != nullptr) {
		//Uses compile time parameters
		//
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actors->GetRootComponent());
		if (Component != nullptr) {
			Component->SetSimulatePhysics(false);
		}
		Actors->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else {
		Mover->SetShouldMove(false);
	}

	//Checks if there are any elements within the array
	//if (Actor.Num() > 0) {
	//	FString ActorName = Actor[0]->GetActorNameOrLabel();


	//	UE_LOG(LogTemp, Display, TEXT("Overlapping %s "), *ActorName);
	//}

}

AActor* UTriggerComponent::GetAcceptableActor() const {
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors) {
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (HasAcceptableTag == true && IsGrabbed == false) {
			return Actor; 
		}
	}

	return nullptr; 
}

void UTriggerComponent::SetMover(UMover* NewMover) {
	Mover = NewMover; 
}