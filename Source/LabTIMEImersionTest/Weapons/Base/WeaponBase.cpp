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

	//Getting  the current amount of ammo on ak.
	int32 AmmoDiff = ClipSize - Ammo;

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