//This is a .cpp file that has defines the funcitonality of the palyer grabbable objects


#include "Grabber.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	//We need to return no value here in order to 
	//protect the program from crashing if the
	//PhysicsHandle variable is a nullptr
	//To not set the target location in tick
	//if we are not currently grabbing anything
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent()) {
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
		return;
	}

	//float Damage = 0; 
	//float& DamageRef = Damage;
	//DamageRef = 5;
	//UE_LOG(LogTemp, Display, TEXT("DamageRef: %f , Damage: %f"), DamageRef, Damage);

	//Memory has been created here in the TickComponent
	//float Damage = 5;
	//The Damage address is being stored into the function
	//if (HasDamage(Damage)) {
	//	PrintDamage(Damage);
	//}

	//FRotator CameraRotation = GetComponentRotation();
	//FString RotationString = CameraRotation.ToCompactString();

	//UE_LOG(LogTemp, Display, TEXT("Camera Rotation: %s "), *RotationString);

	//float Time = GetWorld()->TimeSeconds;
	//UE_LOG(LogTemp, Display, TEXT("Current Time: %f "), Time);

}

void UGrabber::Release() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle(); 

	//Return nothing if PhysicsHandle is null
	if (PhysicsHandle == nullptr) {
		return;
	}
	
	//Checks if there is currently anything holding onto the PhysicsHandle
	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Grabber() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	//We need to return no value here in order to 
	//protect the program from crashing if the
	//PhysicsHandle variable is a nullptr
	if (PhysicsHandle == nullptr) {
		return;
	}

	FHitResult HitResult; 
	bool HasHit = GetGrabbableInReach(HitResult);

	if (HasHit) {
		//Grabbing With Physics Logic
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None, 
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

		//Debug Sphere Code
		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Red, false, 5);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Blue, false, 5);
		UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s "), *HitActor->GetActorNameOrLabel());
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No Actor Hit!"));
	}
}


UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const {
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Grabber requires UPhysicsHandleComponent!"));
	}

	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const {
	//Code for the sweep
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Green, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity,
		ECC_GameTraceChannel2, Sphere);
}

/*
void UGrabber :: PrintDamage(const float& Damage) {
	//Damage = 2;
	UE_LOG(LogTemp, Display, TEXT("Damage: %f"), Damage);
}

bool UGrabber::HasDamage(float& OutDamage) {
	OutDamage = 5; 
	return true; 
	//UE_LOG(LogTemp, Display, TEXT("Damage: %f"), OutDamage);
}
*/