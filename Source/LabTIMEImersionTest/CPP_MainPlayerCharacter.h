// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_MainPlayerCharacter.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API ACPP_MainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_MainPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Defining The speed of the Walking
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Character Movement: Walking");
		const float WalkingSpeed = 1000.f;

	//Defining The speed of the Sprint
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Character Movement: Sprinting");
		const float SprintSpeed = 600.f;

	//Defining The speed of the Crouching
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Character Movement: Crouching");
		const float CrouchingSpeed = WalkingSpeed / 2;

	int WeaponSelected = 0;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Character Movement: Crouching");
		bool bIsCrouching = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Character Movement: Sprinting");
		bool bIsSprinting = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Character Movement: Aiming");
		bool bIsAiming = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Character Action: Firing");
		bool bIsFiring = false;
	



	//Reload Variables
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Character Action: Reloading");
		bool bIsReloading = false;

private:

	UPROPERTY(EditAnywhere)
		float BaseTurnRate = 45.f;

	UPROPERTY(EditAnywhere)
		float BaseLookUpRate = 45.f;

	// Movement Inputs
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	//Player Actions
	void Sprint();
	void StopSprinting();
	void Crouch();
	void StopCrouching();
	void Reload();

	//Mouse Inputs
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	//Gamepad Look Inputs
	void TurnRate(float AxisValue);
	void LookUpRate(float AxisValue);

	//Weapon Selection
	void SelectPrimaryWeapon();
	void SelectSecondaryWeapon();

	//Camera Manipulation
	void AimDownSight();
	void DeactivateAds();
	void StopAiming();

};
 