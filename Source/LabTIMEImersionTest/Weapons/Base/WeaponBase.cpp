// 2023 Labverso, Brazil. Imersion Test.


#include "WeaponBase.h"
#include "Camera/CameraComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//Creating the root Component.
	 WeaponRootComponent = CreateDefaultSubobject<USceneComponent>
		(TEXT("WeaponRootComponent"));

	 //Assign our component to the root of the unreal.
	RootComponent = WeaponRootComponent;

	//Setting the skeletalMeshComponent for each weapon.
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>
		(TEXT("SkeletalMeshComponent"));

	//Setting Relativate Location to 0,0,0.
	SkeletalMeshComponent->SetRelativeLocation(FVector::ZeroVector);
	SkeletalMeshComponent->SetupAttachment(WeaponRootComponent);

	//Setting the ADSCamera for each weapon.
	ADSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ADSCameraT"));
	ADSCamera->SetupAttachment(SkeletalMeshComponent , "AK_Muzzle");
	ADSCamera->bUsePawnControlRotation = true;
	ADSCamera->Deactivate();
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::FireWeapon(UCameraComponent* CameraRayCastFireFrom)
{
	UE_LOG(LogTemp, Warning, TEXT("PEW"));
}

void AWeaponBase::ReloadWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading..."));

	if (MaxAmmo <= 0 || Ammo >= ClipSize)
	{
		// No need to reload
		return;
	}

	bIsReloading = true;

	// Calculting how much ammo the player has spent of the max clip.
	// This is needed as when reloading, we only have to inscrese the amount
	// of bullets that were fired from the weapon, as also decreasing it from
	// the max available ammo (which will be consumed)
	const int32 AmmoDiff = ClipSize - Ammo;

	// Checking whether the weapon have ammo to reload.
	const bool bIsWeaponAbleToReload = (MaxAmmo > AmmoDiff);

	if (bIsWeaponAbleToReload)
	{
		Ammo += AmmoDiff;
		MaxAmmo -= AmmoDiff;
		//Play sound
	}
	else
	{
		Ammo += MaxAmmo;
		MaxAmmo = 0;
		//Play sound
	}
}

void AWeaponBase::EnableCamera()
{
	ADSCamera->Activate();
}

void AWeaponBase::DisableCamera()
{
	ADSCamera->Deactivate();
}