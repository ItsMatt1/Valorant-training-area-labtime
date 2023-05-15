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
	// Sets default values for this character's properties.
	ACPP_MainPlayerCharacter();
	~ACPP_MainPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent*
		PlayerInputComponent) override;

	/**
	* This fuction disables the AimDownSight camera.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "DeactivateAds"))
	void DeactivateAds_Cpp();

	/**
	* This fuction enables the AimDownSight camera.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ActivateAds"))
	void ActivateAds_Cpp();

	/**
	* This fuction hides Glock and shows AK-47 on player.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ShowAK"))
	void ShowAK_Cpp();

	/**
	* This fuction hides AK-47 and shows Glock on player.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ShowGlock"))
	void ShowGlock_Cpp();

protected:

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

private:

	// Movement Inputs
	/**
	* This fuction makes the player move on Z axis.
	* @param AxisValue
	*/
	void MoveForward(float AxisValue);

	/**
	* This fuction makes the player move on Y axis.
	* @param AxisValue
	*/
	void MoveRight(float AxisValue);

	//Player Actions

	/**
	* This fuction is called when player starts sprinting.
	*/
	void Sprint();

	/**
	* This fuction is called when player stops sprinting.
	*/
	void StopSprinting();

	/**
	* This fuction is called when player starts crouching.
	*/
	void Crouch();

	/**
	* This fuction is called when player stops crouching.
	*/
	void StopCrouching();

	/**
	* This fuction is called when player start reloading.
	*/
	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Reload"))
	void Reload();

	/**
	* This fuction is called to calculate the logic of the magazines given
	* the weapon.
	*/
	void ReloadLogic(int CurrentWeapon);

	/**
	* This fuction is called to set bIsReloading to false in order to stop 
	* the current animation.
	*/
	void DisableReloadAnim();

	FTimerHandle TriggerStopAnim;

	//Mouse Inputs

	/**
	* This fuction makes the player move the camera on X.
	* @param AxisValue
	*/
	void Turn(float AxisValue);

	/**
	* This fuction makes the player move the camera on Y.
	* @param AxisValue
	*/
	void LookUp(float AxisValue);

	//Gamepad Look Inputs
	/**
	* This fuction sooths the camera movement on Y given the fps.
	* @param AxisValue
	*/
	void TurnRate(float AxisValue);

	/**
	* This fuction sooths the camera movement on X given the fps.
	* @param AxisValue
	*/
	void LookUpRate(float AxisValue);

	//Weapon Selection
	/**
	* This fuction is called when player selects primary weapon.
	*/
	void SelectPrimaryWeapon();

	/**
	* This fuction is called when player selects secondary weapon.
	*/
	void SelectSecondaryWeapon();

	//Camera Manipulation
	/**
	* This fuction is called when player aims.
	*/
	void AimDownSight();

	/**
	* This fuction is called when player stops aiming.
	*/
	void StopAiming();


public:

	//Defining The speed of the Walking
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly,
		Category = "Character Movement: Walking");
	float WalkingSpeed = 600.f;

	//Defining The speed of the Sprint
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly,
		Category = "Character Movement: Sprinting");
	float SprintSpeed = 1000.f;

	//Defining The speed of the Crouching
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly,
		Category = "Character Movement: Crouching");
	float CrouchingSpeed = WalkingSpeed / 2;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Movement: Crouching");
	bool bIsCrouching = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Movement: Sprinting");
	bool bIsSprinting = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Movement: Aiming");
	bool bIsAiming = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Action: Firing");
	bool bIsFiring = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Action: Reloading");
	bool bIsReloading = false;

	//1 for AK-47.
	//2 for Glock.
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Action: WeaponSelected");
	int WeaponSelected = 1;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon: Ammo");
	int AmmoAK = 30;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon: FireRate");
	float FireRateAK = 0.1;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon: MaxAmmo");
	int MaxAmmoAK = 90;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon: ClipSize");
	int ClipSizeAK = 30;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon: Ammo");
	int AmmoGlock = 15;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon: MaxAmmo");
	int MaxAmmoGlock = 45;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon: ClipSize");
	int ClipSizeGlock = 15;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon: AmmoDiff");
	int AmmoDiffAk = 0;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon: AmmoDiff");
	int AmmoDiffGlock = 0;

private:

	UPROPERTY(EditAnywhere)
	float BaseTurnRate = 45.f;

	UPROPERTY(EditAnywhere)
	float BaseLookUpRate = 45.f;

};
 