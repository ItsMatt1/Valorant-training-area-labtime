// 2023 Labverso, Brazil. Imersion Test.


#include "AutomaticWeapon.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include <LabTIMEImersionTest/MainPlayer/MainPlayerCharacter.h>

void AAutomaticWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAutomaticWeapon::FireWeapon(UCameraComponent* CameraRayCastFireFrom)
{
	//If MainPlayerCharacter passes a camera as a param then use its camera
	//If not, use our own ADSCamera.
	if (CameraRayCastFireFrom == nullptr)
	{
		CameraRayCastFireFrom = ADSCamera;
	}

	if (Ammo < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("No more bullets on magazine"));
		return;
	}


	GetWorld()->GetFirstPlayerController()->GetPawn()->
		AddControllerPitchInput(-0.3);
	GetWorld()->GetFirstPlayerController()->GetPawn()->
		AddControllerYawInput(-0.15);

	bIsFiring = true;

	//Play Sound
	UGameplayStatics::PlaySound2D(GetWorld(), ShootSound);

	// Getting the muzzle position.
	FVector EffectSpawnLocation = SkeletalMeshComponent->
		GetSocketLocation("AK_FlashFX");
	FRotator EffectSpawnRotation = SkeletalMeshComponent->
		GetSocketRotation("AK_FlashFX");

	// Spawn the emitter at the specified location.
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterTemplate, 
		EffectSpawnLocation, EffectSpawnRotation, FVector(0.1), true);

	//As it fired, decreased the ammo amount.
	Ammo--;

	FHitResult OutHit;

	//Position that the raycast will start.
	FVector Start = CameraRayCastFireFrom->GetComponentLocation();
	FVector ForwardVector = CameraRayCastFireFrom->GetForwardVector();

	//Ignoring own collision.
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this->GetOwner());

	//Position that the raycast will end.
	const float RayCastRange = 5000.f;
	FVector End = Start + (ForwardVector * RayCastRange);

	const bool bIsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start,
		End, ECC_Visibility, CollisionParams);
	
	if (!bIsHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fired and Hit Nothing!"));
		return;
	}

	const bool bIsAnActor = OutHit.Actor.IsValid();

	if (!bIsAnActor)
	{
		UE_LOG(LogTemp, Warning, 
			TEXT("Fired and Hit something that is not an actor!"));
		return;
	}

	const bool bIsActorEnemy = OutHit.GetActor()->ActorHasTag("Enemy");

	if (!bIsActorEnemy)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Fired and Hit an Actor that is not an Enemy!"));
		return;
	}

	UE_LOG(LogTemp, Warning,
		TEXT("Fired and Hit an Enemy!"));

	UGameplayStatics::ApplyDamage(Cast<AEnemyCharacterBase>(OutHit.GetActor()),
		0.1f, GetWorld()->GetFirstPlayerController(), this, nullptr);

	//Letting Target_Enemy handles the damage.
	Cast<AEnemyCharacterBase>(OutHit.GetActor())->EnemyHitByBulletEvent();
}