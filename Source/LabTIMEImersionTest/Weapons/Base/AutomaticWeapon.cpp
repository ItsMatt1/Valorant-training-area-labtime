// 2023 Labverso, Brazil. Imersion Test.


#include "AutomaticWeapon.h"
#include "DrawDebugHelpers.h"
#include <LabTIMEImersionTest/MainPlayer/MainPlayerCharacter.h>

void AAutomaticWeapon::FireWeapon()
{
	if (Ammo < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("No more bullets on magazine"));
		return;
	}

	FHitResult OutHit;

	//FVector Start = GetWorld()->GetFirstPlayerController()->GetPawn()

	
	
}

void AAutomaticWeapon::ReloadWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading the automatic weapon!"));
}
