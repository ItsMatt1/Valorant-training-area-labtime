// 2023 Labverso, Brazil. Imersion Test.


#include "AutomaticWeapon.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include <LabTIMEImersionTest/MainPlayer/MainPlayerCharacter.h>

void AAutomaticWeapon::FireWeapon(UCameraComponent* CameraRayCastFireFrom)
{
	if (CameraRayCastFireFrom == nullptr)
	{
		CameraRayCastFireFrom = ADSCamera;
	}

	if (Ammo < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("No more bullets on magazine"));
		return;
	}

	FHitResult OutHit;

	FVector Start = CameraRayCastFireFrom->GetComponentLocation();
	FVector ForwardVector = CameraRayCastFireFrom->GetForwardVector();

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this->GetOwner());

	FVector End = Start + (ForwardVector * 5000.f);

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
	
	if (isHit)
	{
		bool foo = OutHit.GetActor()->ActorHasTag("Enemy");

		if (foo)
		{
			OutHit.GetActor()->Destroy();

			//Enemy->EnemyHitByBulletEvent();
		}
	}
}

void AAutomaticWeapon::ReloadWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading the automatic weapon!"));
}
