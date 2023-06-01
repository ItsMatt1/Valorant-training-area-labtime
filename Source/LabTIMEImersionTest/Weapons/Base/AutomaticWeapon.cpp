// 2023 Labverso, Brazil. Imersion Test.


#include "AutomaticWeapon.h"
#include "Camera/CameraComponent.h"
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

	FVector Start = ADSCamera->GetComponentLocation();
	FVector ForwardVector = ADSCamera->GetForwardVector();

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this->GetOwner());

	FVector End = Start + (ForwardVector * 5000.f);

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	
	if (isHit)
	{
		auto foo = OutHit.GetActor()->ActorHasTag("Enemy");
		if (foo == true)
		{
			OutHit.GetActor()->Destroy();
		}
	}
}

void AAutomaticWeapon::ReloadWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading the automatic weapon!"));
}
