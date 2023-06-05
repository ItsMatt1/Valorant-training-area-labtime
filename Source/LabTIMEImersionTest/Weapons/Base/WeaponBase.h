// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabTIMEImersionTest/Enemies/Base/EnemyCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "WeaponBase.generated.h"

/** 
* This is the abstract base class for all weapons.
* It deals with the base functionality that all weapons have, 
* e.g., the base mesh, firing the weapon, weapon common properties, and etc.
* @note Every weapon should inherit this base class
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	/** Getter to the weapon's current ammunition amount */
	UFUNCTION(BlueprintCallable,
		meta = (Tooltip = "Getter to the weapon's current ammo"))
		int32 GetWeaponCurrentAmmo() { return WeaponAmmunitionAmount; }

	/** Getter to the weapon's name */
	UFUNCTION(BlueprintCallable,
		meta = (Tooltip = "Getter to the weapon's name"))
		FString GetWeaponName() { return WeaponName; }
	
public:	
	/** Sets default values for this actor's properties */
	AWeaponBase();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Fires the weapon */
	virtual void FireWeapon(UCameraComponent* CameraRayCastFireFrom);

	/** Reloads the weapon */
	virtual void ReloadWeapon();

	/** Enables the ADSCamera */
	virtual void EnableCamera();

	/** Disables the ADSCamera*/
	virtual void DisableCamera();

	virtual void VerifyStillShooting();

public:

	/** Boolean which is true whenever player reloads. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Weapon Characteristics");
	bool bIsReloading = false;

	/** Boolean which is true whenever player fires. */
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,
		Category = "Character Action");
	bool bIsFiring = false;

	bool bIsStillFiring = false;

	/**
	* Its a simple FTimer Handle to distinguish timers and finish animation.
	*/
	FTimerHandle Firerate;

	/** A template effect to be set at gun's blueprint. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Emmiter");
	UParticleSystem* EmitterTemplate = nullptr;

protected:

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

protected:

	/** 
	* The weapon ammunition amount. 
	* The bullet rounds amount it can fire in a row 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, 
		meta=(Tooltip="The weapon ammunition amount", AllowPrivateAccess=True))
	int32 WeaponAmmunitionAmount = 0;

	/** The weapon's name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, 
		meta=(Tooltip="The weapon's name", AllowPrivateAccess=True))
	FString WeaponName = FString();

	/** Setting the Skeletal Mesh for the weapons. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

	/** Setting A RootComponent for the weapons to attach components. */
	USceneComponent* WeaponRootComponent = nullptr;

	/** The Camera that follows the gun aimsight component */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* ADSCamera = nullptr;

	/** Ammount of ammo */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Weapon Characteristics");
	int32 Ammo = 0;

	/** Ammount of Max Ammo */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Weapon Characteristics");
	int32 MaxAmmo = 0;

	/** The size of one clip  */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Weapon Characteristics");
	int32 ClipSize = 0;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Enemy");
	AEnemyCharacterBase* Enemy = nullptr;

protected:
	/** The amount of ammunition the weapon still has on it's chamber */
	int32 WeaponCurrentAmmunitionAmount = 0;

	/** Variable to calculate the difference between current clip - clipsize. */
	int32 AmmoDiff = 0;
};
