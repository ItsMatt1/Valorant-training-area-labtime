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
		float WalkingSpeed = 0.f;

	//Defining The speed of the Sprint
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Character Movement: Walking");
		float SprintSpeed = 0.f;

	//Defining The speed of the Crouching
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Character Movement: Walking");
	float CrouchingSpeed = 0.f;

	int WeaponSelected = 0;

	bool isSprinting = false;
	bool isAiming = false;
	bool isCrouching = false;
	bool isFiring = false;
	bool isReloading = false;

private:
	// Movement Inputs
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Sprint();
	void StopSprinting();
	void Crouch();
	void StopCrouching();

	//Mouse Inputs
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	//Gamepad Look Inputs
	void TurnRate(float AxisValue);
	void LookUpRate(float AxisValue);

	//Weapon Selection
	void SelectPrimaryWeapon();
	void SelectSecondaryWeapon();

	UPROPERTY(EditAnywhere)
		float BaseTurnRate = 45.f;

	UPROPERTY(EditAnywhere)
		float BaseLookUpRate = 45.f;


};
 