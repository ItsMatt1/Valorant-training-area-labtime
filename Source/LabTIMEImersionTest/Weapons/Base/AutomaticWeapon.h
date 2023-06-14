// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "AutomaticWeapon.generated.h"

/**
* This class inherits from AWeaponBase and adds the functionality
* of automatic weapons.
* Automatic weapons are those that will keep firing as long as the
* player keeps the fire input pressed.
* 
* @see AWeaponBase
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AAutomaticWeapon : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	/** 
	* Fires the automatic weapon. 
	* In this case, if the player holds the mouse buttom, 
	* the weapon will keep firing until we have no ammo left.
	* 
	* @param CameraRayCastFireFrom, which Camera is the raycast starting from.
	*/
	virtual void FireWeapon(UCameraComponent* CameraRayCastFireFrom) override;

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

protected:
	/** Specifying the fire rate of the automatic weapons. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite,
		Category = "Weapon Characteristics");
	float FireRate = 0.5f;
};
