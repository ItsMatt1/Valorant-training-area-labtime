// 2023 Labverso, Brazil. Imersion Test.


#include "SemiAutomaticWeapon.h"

void ASemiAutomaticWeapon::FireWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("PEW from semi-automatic weapon!"));
}

void ASemiAutomaticWeapon::ReloadWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading the semi-automatic weapon!"));
}
