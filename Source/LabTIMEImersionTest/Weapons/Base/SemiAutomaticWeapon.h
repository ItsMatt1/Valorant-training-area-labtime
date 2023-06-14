// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "SemiAutomaticWeapon.generated.h"

/**
* This class inherits from AWeaponBase and adds the functionality
* of semi-automatic weapons.
* Semi Automatic are those that will NOT keep firing.
* The player needs to released and press the button again.
* @see AWeaponBase
*/
UCLASS()
class LABTIMEIMERSIONTEST_API ASemiAutomaticWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	/**
	* Fires the automatic weapon.
	* In this case, if the player holds the mouse buttom,
	* the weapon will keep firing until we have no ammo left.
	*/
	virtual void FireWeapon(UCameraComponent* CameraRayCastFireFrom) override;

};
