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
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();

	/**
	* This function its called when enemy damaged the player.
	* It handles which type of damage he'll take armor or straight health.
	* 
	* @note Its called on BP_TargetEnemy.
	*/
	UFUNCTION(BlueprintCallable)
	void HandleDamageWidget();

protected:

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

private:

	/**
	* A getter for boolean bIsCrouching.
	* that it is used mainly for animation purposes.
	* 
	* @return bIsSprinting.
	*/
	UFUNCTION(BlueprintCallable,
		meta = (Tooltip = "Get bIsCrouching value and return"))
	inline bool GetIsCrouching() { return bIsCrouching; }

	/**
	* A getter for boolean bIsSprinting.
	* that it is used mainly for animation purposes.
	*
	* @return bIsSprinting.
	*/
	UFUNCTION(BlueprintCallable,
		meta = (Tooltip = "Get bIsSprinting value and return"))
	inline bool GetIsSprinting() { return bIsSprinting; }

	/**
	* A getter for boolean bIsAiming.
	*
	* @return bIsAiming.
	*/
	UFUNCTION(BlueprintCallable,
		meta = (Tooltip = "Get bIsAiming value and return"))
	inline bool GetIsAiming() { return bIsAiming; }

private:
	/**
	* Handles the forward movement of the character.
	* This method should be binded on a axis input.
	*
	* @param AxisValue The axis value of the input
	*/
	inline void MoveForward(float AxisValue);

	/**
	* Handles the right movement of the character.
	* This method should be binded on a axis input.
	*
	* @param AxisValue The axis value of the input
	*/
	inline void MoveRight(float AxisValue);

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
	* This function is called to set bIsReloading to false in order to stop
	* the current animation.
	*/
	void DisableReloadAnim();

	/**
	* This function makes the player move the camera on X.
	* 
	* @param AxisValue
	*/
	inline void Turn(float AxisValue);

	/**
	* This function makes the player move the camera on Y.
	* 
	* @param AxisValue
	*/
	inline void LookUp(float AxisValue);

	/**
	* This function sooths the camera movement on Y given the fps.
	* 
	* @param AxisValue
	*/
	inline void TurnRate(float AxisValue);

	/**
	* This function sooths the camera movement on X given the fps.
	* 
	* @param AxisValue
	*/
	inline void LookUpRate(float AxisValue);

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
	* VerifyFiring .
	*/
	inline void PrimaryFire();

	/**
	* This function is called when player is still holding Primary Fire Button
	* and will call the function FireWeapon from current equipped weapon.
	*/
	inline void VerifyFiring();

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
	class UCameraComponent* FollowCamera = nullptr;

	/** Defining The speed of the Walking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Movement")
	float WalkingSpeed = 600.f;

	/** Defining The speed of the Sprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Movement")
	float SprintSpeed = 1000.f;

	/** Defining The speed of the Crouching */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Character Movement")
	float CrouchingSpeed = WalkingSpeed / 2;

	/** Actor to Spawn AK-47 */
	UPROPERTY(EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> AK47;

	/** Actor to Spawn Glock */
	UPROPERTY(EditAnyWhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> Glock;

	/** Variable to keep track of the current weapon equipped */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Equipped Weapon")
	AWeaponBase* EquippedWeapon = nullptr;

	/** Map to store all the weapons created and spawned */
	TMap<FString, AWeaponBase*> AvailableWeapons;

	/** A reload sound to be set at blueprint. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Sounds")
	USoundBase* ReloadSound = nullptr;

	/** Creating Health Component on Player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UHealthComponent* HealthComponent = nullptr;

private:

	/** Set the turn rate of the controller */
	UPROPERTY(EditAnywhere)
	float BaseTurnRate = 45.f;

	/** Set the look up rate of the controller */
	UPROPERTY(EditAnywhere)
	float BaseLookUpRate = 45.f;

	/** Boolean which is true whenever player crouches */
	bool bIsCrouching = false;

	/** Boolean which is true whenever player sprints */
	bool bIsSprinting = false;

	/** Boolean which is true whenever player aims */
	bool bIsAiming = false;

	/** Keep track if player is still holding PrimaryFire Button (left mouse
		click) */
	bool keepFiring = false;

	/**
	* Its a simple FTimer Handle to distinguish timers and finish animation.
	*/
	FTimerHandle TriggerStopAnim;

	/**
	* Its a simple FTimer Handle to distinguish timers and set FireRate of 
		automatic weapons.
	*/
	FTimerHandle FireRate;

	/** Create a reference to Player Controller */
	APlayerController* OurPlayerController = nullptr;
};
