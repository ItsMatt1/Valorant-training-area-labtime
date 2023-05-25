// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayerCharacter.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties.
	AMainPlayerCharacter();
	~AMainPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent*
		PlayerInputComponent) override;

	/**
	* This fuction disables the AimDownSight camera.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName =
		"DeactivateAds"))
	void DeactivateAdsEvent();

	/**
	* This fuction enables the AimDownSight camera.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName
		= "ActivateAds"))
	void ActivateAdsEvent();

	/**
	* This fuction hides Glock and shows AK-47 on player.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ShowAK"))
	void ShowAkEvent();

	/**
	* This fuction hides AK-47 and shows Glock on player.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ShowGlock"))
	void ShowGlockEvent();

	/**
	* This fuction calls Fire Event of Weapon_Base on BP_MainPlayerCharacter.
	* It throws a line tracing between the player and the middle of the screen.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Fire"))
	void FireAkEvent();

	/**
	* This fuction calls Fire Event of Weapon_Glock on BP_MainPlayerCharacter.
	* It throws a line tracing between the player and the middle of the screen.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Fire"))
	void FireGlockEvent();

	/**
	* This Function call the GameOverWidget.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "GameOver"))
	void GameOver();

	/**
	* This fuction calls makes the player take 15% of damage.
	* It reduces its health and/or armor.
	* Its called on BP_TargetEnemy
	*/
	UFUNCTION(BlueprintCallable)
	void TakeDamage();

protected:

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

private:

	// Movement Inputs
	/**
	* Handles the forward movement of the character.
	* This method should be binded on a axis input.
	*
	* @param AxisValue The axis value of the input
	*/
	void MoveForward(float AxisValue);

	/**
	* Handles the right movement of the character.
	* This method should be binded on a axis input.
	*
	* @param AxisValue The axis value of the input
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
	void Reload();

	/**
	* This fuction is called to calculate and update the magazines given
	* the weapon.
	* @param CurrentWeapon is a int which is always 1 or 2.
	* 1 for AK-47.
	* 2 for Glock.
	*/
	void ReloadLogic(int CurrentWeapon);

	/**
	* This fuction is called to set bIsReloading to false in order to stop
	* the current animation.
	*/
	void DisableReloadAnim();

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

	/**
	* This fuction is called when player shoots.
	*/
	void PrimaryFire();

	/**
	* This fuction is called when stop shooting.
	*/
	void StopFiring();

	/**
	* This Function call the ArmorDamage Widget.
	*/
	void TakeArmorDamageCallWidget();

	/**
	* This Function call the HealthDamage Widget.
	*/
	void TakeHealthDamageCallWidget();

public:

	//Defining amount of Health, starts with 1 and go until 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Info: Health");
	float Health = 1.f;

	//Defining amount of Armor, starts with 1 and go until 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Info: Armor");
	float Armor = 1.f;

	//Defining The speed of the Walking
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Movement: Walking");
	float WalkingSpeed = 600.f;

	//Defining The speed of the Sprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Movement: Sprinting");
	float SprintSpeed = 1000.f;

	//Defining The speed of the Crouching
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
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
		Category = "Weapon AK: Ammo");
	int32 AmmoAK = 30;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon AK: FireRate");
	float FireRateAK = 0.1;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon AK: MaxAmmo");
	int32 MaxAmmoAK = 90;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon AK: ClipSize");
	int32 ClipSizeAK = 30;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon Glock: Ammo");
	int32 AmmoGlock = 15;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon Glock: MaxAmmo");
	int32 MaxAmmoGlock = 45;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon Glock: ClipSize");
	int32 ClipSizeGlock = 15;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon AK: AmmoDiff");
	int32 AmmoDiffAk = 0;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon Glock: AmmoDiff");
	int32 AmmoDiffGlock = 0;

private:

	UPROPERTY(EditAnywhere)
	float BaseTurnRate = 45.f;

	UPROPERTY(EditAnywhere)
	float BaseLookUpRate = 45.f;

	/**
	* Its a simple FTimer Handle to distinguish timers and finish animation.
	*/
	FTimerHandle TriggerStopAnim;
};
