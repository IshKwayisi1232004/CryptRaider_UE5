//This the .h for the grabber, which creates the functions and variables, usable in the Grabber.cpp


#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDERPROJECT_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//UFUNCTION allows for blueprints to see C++ functions. 
	UFUNCTION(BlueprintCallable)
	void Release();

	//A Grabber UFUNCTION for blueprints to see this function
	UFUNCTION(BlueprintCallable)
	void Grabber();

private: 
	//Create a MaxGrabDistance property that is editable in the Unreal Engine editor 
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400; 

	//Create a GrabRadius property that is editable in the Unreal Engine editor 
	UPROPERTY(EditAnywhere)
	float GrabRadius = 100; 

	//Create a HoldDistance property that is editable in the Unreal Engine editor 
	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	//Private GetPhysicsHandke() function to return the object being grabbed
	UPhysicsHandleComponent* GetPhysicsHandle() const;

	//
	bool GetGrabbableInReach(FHitResult& OutHitResult) const; 
		
	//void PrintDamage(const float& Damage);
	//bool HasDamage(float& OutDamage);
};
