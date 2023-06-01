// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LabTIMEImersionTest/Weapons/Base/WeaponBase.h"
#include "LabTIMEImersionTest/Weapons/Base/AutomaticWeapon.h"
#include "MainPlayerCharacter.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Sets default values for this character's properties. */
	AMainPlayerCharacter();
	~AMainPlayerCharacter();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent*
		PlayerInputComponent) override;

	/**
	* This Function call the GameOverWidget and show on screen.
	* 
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "GameOver"))
	void GameOver();

	/**
	* This function calls makes the player take 15% of damage.
	* It reduces its health and/or armor.
	* Its called on BP_TargetEnemy
	*/
	UFUNCTION(BlueprintCallable)
	void TakeDamageFromEnemy();

protected:

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

private:

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

	/**
	* This function is called when the player starts sprinting and will do this
	* by changing the character movement max walk speed.
	*/
	void Sprint();

	/**
	* This function is called when player stops sprinting and will decrease the
	* character movement max walk speed.
	*/
	void StopSprinting();

	/**
	* This function is called when player starts crouching and will call the
	* Crouch function from Unreal.
	*/
	void RequestCrouch();

	/**
	* This function is called when player stops crouching and will call the
	* Uncrouch function from Unreal.
	*/
	void StopCrouching();

	/**
	* This function is called when the player starts reloading and will request
	the current equipped weapon to reload it’s ammunition.
	*/
	void Reload();

	/**
	* This function is called to calculate and update the magazines given
	* the weapon.
	* @param CurrentWeapon is a int which is always 1 or 2.
	* 1 for AK-47.
	* 2 for Glock.
	*/
	void ReloadLogic(int CurrentWeapon);

	/**
	* This function is called to set bIsReloading to false in order to stop
	* the current animation.
	*/
	void DisableReloadAnim();

	/**
	* This function makes the player move the camera on X.
	* @param AxisValue
	*/
	void Turn(float AxisValue);

	/**
	* This function makes the player move the camera on Y.
	* @param AxisValue
	*/
	void LookUp(float AxisValue);

	/**
	* This function sooths the camera movement on Y given the fps.
	* @param AxisValue
	*/
	void TurnRate(float AxisValue);

	/**
	* This function sooths the camera movement on X given the fps.
	* @param AxisValue
	*/
	void LookUpRate(float AxisValue);

	/**
	* This function is called when player selects primary weapon and will
	* change the current weapon to the AK-47.
	*/
	void SelectPrimaryWeapon();

	/**
	* This function is called when player selects secondary weapon and will
	* change the current weapon to the Glock.
	*/
	void SelectSecondaryWeapon();

	/**
	* This function is called when player aims.
	*/
	void AimDownSight();

	/**
	* This function is called when player stops aiming.
	*/
	void StopAiming();

	/**
	* This function is called when player shoots and will call the function
	* FireWeapon from current equipped weapon.
	*/
	void PrimaryFire();

	/**
	* This function is called when stop shooting and will set bIsFiring to 
	* false.
	*/
	void StopFiring();

	/**
	* This Function call the ArmorDamage Widget and show it on screen.
	*/
	void TakeArmorDamageCallWidget();

	/**
	* This Function call the HealthDamage Widget and show it on screen.
	*/
	void TakeHealthDamageCallWidget();

public:

	/** The Camera that follows the player component */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* FollowCamera;

	/** Defining amount of Health, starts with 1 and go until 0 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Info");
	float Health = 1.f;

	/** Defining amount of Armor, starts with 1 and go until 0 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Info");
	float Armor = 1.f;

	/** Defining The speed of the Walking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Movement");
	float WalkingSpeed = 600.f;

	/** Defining The speed of the Sprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Movement");
	float SprintSpeed = 1000.f;

	/** Defining The speed of the Crouching */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Movement");
	float CrouchingSpeed = WalkingSpeed / 2;

	/** Boolean which is true whenever player crouchs */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Movement");
	bool bIsCrouching = false;

	/** Boolean which is true whenever player sprints */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Movement");
	bool bIsSprinting = false;

	/** Boolean which is true whenever player aims */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Movement");
	bool bIsAiming = false;

	/** Boolean which is true whenever player fires*/
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Action");
	bool bIsFiring = false;

	/** Boolean which is true whenever player is realoding*/
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Action");
	bool bIsReloading = false;

	/**	1 for AK-47.
		2 for Glock. */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Action");
	int WeaponSelected = 1;

	/** Ammount of AK-47 ammo */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon AK");
	int32 AmmoAK = 30;

	/** AK-47 FireRate */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon AK");
	float FireRateAK = 0.1;

	/** Ammount of AK-47 Max Ammo */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon AK");
	int32 MaxAmmoAK = 90;

	/** The size of one clip of the AK-47 */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon AK");
	int32 ClipSizeAK = AmmoAK;

	/** Ammount of Glock ammo */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon Glock");
	int32 AmmoGlock = 15;

	/** Ammount of Glock Max ammo */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon Glock");
	int32 MaxAmmoGlock = 45;

	/** The size of one clip of the Glock */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon Glock");
	int32 ClipSizeGlock = AmmoGlock;

	/** Variable to calculate the difference entre current clip - clipsize */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon AK");
	int32 AmmoDiffAk = 0;

	/** Variable to calculate the difference entre current clip - clipsize */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Weapon Glock");
	int32 AmmoDiffGlock = 0;

	/** Actor to Spawn AK-47 */
	UPROPERTY(EditAnyWhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AWeaponBase> AK47;

	/** Actor to Spawn Glock */
	UPROPERTY(EditAnyWhere, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<AWeaponBase> Glock;

	/** Variable to keep track of the current weapon equipped */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Equipped Weapon");
	AWeaponBase* EquippedWeapon = nullptr;

	/** Map to store all the weapons created and spawned*/
	TMap<FString, AWeaponBase*> AvailableWeapons;

private:

	/** Set the turn rate of the controller */
	UPROPERTY(EditAnywhere)
	float BaseTurnRate = 45.f;

	/** Set the look up rate of the controller */
	UPROPERTY(EditAnywhere)
	float BaseLookUpRate = 45.f;

	/**
	* Its a simple FTimer Handle to distinguish timers and finish animation.
	*/
	FTimerHandle TriggerStopAnim;
};
