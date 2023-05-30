// 2023 Labverso, Brazil. Imersion Test.


#include "MainPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "LabTIMEImersionTest/Interface/MainHUD.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayerController.h"

// Sets default values
AMainPlayerCharacter::AMainPlayerCharacter()
{
	// Set this character to call Tick() every frame. You can turn this off to
	//improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh(), "Head");
	FollowCamera->bUsePawnControlRotation = true;

	//ADSCameraT = CreateDefaultSubobject<UCameraComponent>(TEXT("ADSCameraT"));
	//ADSCameraT->SetupAttachment(, "Head");
	//ADSCameraT->bUsePawnControlRotation = true;
}

AMainPlayerCharacter::~AMainPlayerCharacter()
{
}

// Called when the game starts or when spawned
void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();

	auto SpawnAk = GetWorld()->SpawnActor<AWeaponBase>(AK47, Location, Rotation);
	SpawnAk->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "Weapon_Attach");

	auto SpawnGlock = GetWorld()->SpawnActor<AWeaponBase>(Glock, Location, Rotation);
	SpawnGlock->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "Weapon_Attach");

	SpawnGlock->GetRootComponent()->SetVisibility(true);

	AvailableWeapons.Add("AK-47", SpawnAk);
	AvailableWeapons.Add("Glock", SpawnGlock);

	if (!AvailableWeapons.Contains("AK-47"))
	{
		UE_LOG(LogTemp, Error,
			TEXT("Gun AK-47 not found."));
		return;
	}

	EquippedWeapon = AvailableWeapons["AK-47"];
}

// Called every frame
void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent*
	PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this,
		&AMainPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this,
		&AMainPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this,
		&AMainPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this,
		&AMainPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this,
		&AMainPlayerCharacter::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this,
		&AMainPlayerCharacter::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,
		this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released,
		this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed,
		this, &AMainPlayerCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released,
		this, &AMainPlayerCharacter::StopSprinting);

	PlayerInputComponent->BindAction(TEXT("SelectPrimaryWeapon"),
		EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::SelectPrimaryWeapon);
	PlayerInputComponent->BindAction(TEXT("SelectSecondaryWeapon"),
		EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::SelectSecondaryWeapon);

	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed,
		this, &AMainPlayerCharacter::Crouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released,
		this, &AMainPlayerCharacter::StopCrouching);

	PlayerInputComponent->BindAction(TEXT("AimDownSight"),
		EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::AimDownSight);
	PlayerInputComponent->BindAction(TEXT("AimDownSight"),
		EInputEvent::IE_Released, this, &AMainPlayerCharacter::StopAiming);

	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed,
		this, &AMainPlayerCharacter::Reload);

	PlayerInputComponent->BindAction(TEXT("PrimaryFire"),
		EInputEvent::IE_Pressed, this,
		&AMainPlayerCharacter::PrimaryFire);
	PlayerInputComponent->BindAction(TEXT("PrimaryFire"),
		EInputEvent::IE_Released, this,
		&AMainPlayerCharacter::StopFiring);

}

void AMainPlayerCharacter::MoveForward(float AxisValue)
{
	//Get Rotation and Axis of the Player
	const FRotator GetPawnRotation = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector Forward = UKismetMathLibrary::GetForwardVector(
		GetPawnRotation);

	// Add movement input along the given world direction vector
	AddMovementInput(Forward, AxisValue);
}

void AMainPlayerCharacter::MoveRight(float AxisValue)
{
	//Get Rotation and Axis of the Player
	const FRotator GetPawnRotation = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector Right = UKismetMathLibrary::GetRightVector(
		GetPawnRotation);

	// Add movement input along the given world direction vector
	AddMovementInput(Right, AxisValue);
}

void AMainPlayerCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AMainPlayerCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AMainPlayerCharacter::TurnRate(float AxisValue)
{
	float frameDeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(AxisValue * BaseTurnRate * frameDeltaTime);
}

void AMainPlayerCharacter::LookUpRate(float AxisValue)
{
	float frameDeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(AxisValue * BaseLookUpRate * frameDeltaTime);
}

void AMainPlayerCharacter::SelectPrimaryWeapon()
{
	if (!AvailableWeapons.Contains("AK-47"))
	{
		UE_LOG(LogTemp, Error,
			TEXT("Gun AK-47 not found."));
		return;
	}

	EquippedWeapon = AvailableWeapons["AK-47"];

	AvailableWeapons.Contains("AK-47");

	AvailableWeapons["Glock"]->GetRootComponent()->SetVisibility(false, true);

	EquippedWeapon->GetRootComponent()->SetVisibility(true, true);
}


void AMainPlayerCharacter::SelectSecondaryWeapon()
{
	if (!AvailableWeapons.Contains("Glock"))
	{
		UE_LOG(LogTemp, Error,
			TEXT("Gun Glock not found."));
		return;
	}

	EquippedWeapon = AvailableWeapons["Glock"];

	AvailableWeapons["AK-47"]->GetRootComponent()->SetVisibility(false, true);

	EquippedWeapon->GetRootComponent()->SetVisibility(true, true);
}

void AMainPlayerCharacter::AimDownSight()
{
	//Player cant realod if it is aiming.
	if (bIsReloading)
	{
		return;
	}

	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}

	ActivateAdsEvent();
	bIsAiming = true;
}

void AMainPlayerCharacter::StopAiming()
{
	DeactivateAdsEvent();
}

void AMainPlayerCharacter::PrimaryFire()
{
	//Disables firing if the player is sprinting or reloading.
	if (bIsSprinting || bIsReloading)
	{
		return;
	}

	/* Reminder */
	//1 for Ak.
	//2 for Glock.

	EquippedWeapon->FireWeapon();

	//switch (WeaponSelected)
	//{
	//case 1:
	//	if (AmmoAK >= 1)
	//	{
	//		bIsFiring = true;
	//		FireAkEvent();
	//	}
	//	break;
	//case 2:
	//	if (AmmoGlock >= 1)
	//	{
	//		bIsFiring = true;
	//		FireGlockEvent();
	//	}
	//	break;
	//default:
	//	break;
	//}
}

void AMainPlayerCharacter::StopFiring()
{
	bIsFiring = false;
}

void AMainPlayerCharacter::Sprint()
{
	//If the player is aiming the player cannot sprint, so this deactivates 
	// the aim.
	if (bIsAiming)
	{
		DeactivateAdsEvent();
	}

	//If the player is crouching the player cannot sprint, so this deactivates 
	// the crouch.
	if (bIsCrouching)
	{
		bIsCrouching = false;
		UnCrouch();
	}

	bIsSprinting = true;

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMainPlayerCharacter::StopSprinting()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void AMainPlayerCharacter::Crouch()
{
	//If the player is sprinting the player cannot crouch, so this deactivates 
	// the sprint.
	if (bIsSprinting)
	{
		bIsSprinting = false;
	}

	bIsCrouching = true;

	GetCharacterMovement()->MaxWalkSpeed = CrouchingSpeed;

	ACharacter::Crouch();
}

void AMainPlayerCharacter::StopCrouching()
{
	bIsCrouching = false;

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	UnCrouch();
}


void AMainPlayerCharacter::Reload()
{
	if (bIsAiming || bIsFiring)
	{
		return;
	}

	EquippedWeapon->ReloadWeapon();

	switch (WeaponSelected)
	{
	case 1:
		ReloadLogic(1);
		break;
	case 2:
		ReloadLogic(2);
		break;
	default:
		break;
	}
}

void AMainPlayerCharacter::ReloadLogic(int CurrentWeapon)
{
	if (CurrentWeapon == 1)
	{
		if (MaxAmmoAK <= 0)
		{
			//No more Bullets
			return;
		}

		if (AmmoAK >= ClipSizeAK)
		{
			//Full ammo already!
			return;
		}

		bIsReloading = true;

		//Getting  the current ammount of ammo on ak.
		AmmoDiffAk = ClipSizeAK - AmmoAK;

		const bool bIsWeaponAbleToReload = (MaxAmmoAK > AmmoDiffAk);
		 
		if (bIsWeaponAbleToReload)
		{
			AmmoAK += AmmoDiffAk;
			MaxAmmoAK -= AmmoDiffAk;
			//Play sound
		}
		else
		{
			AmmoAK += MaxAmmoAK;
			MaxAmmoAK = 0;
			//Play sound
		}

		GetWorld()->GetTimerManager().SetTimer(TriggerStopAnim, this,
			&AMainPlayerCharacter::DisableReloadAnim, 2.4f, true);

	}
	else if (CurrentWeapon == 2)
	{
		if (MaxAmmoGlock <= 0)
		{
			//No more Bullets
			return;
		}

		if (AmmoGlock < ClipSizeGlock)
		{
			if (MaxAmmoGlock > (ClipSizeGlock - AmmoGlock))
			{
				AmmoDiffGlock = ClipSizeGlock - AmmoGlock;
				AmmoGlock += AmmoDiffGlock;
				MaxAmmoGlock -= AmmoDiffGlock;
				//Play sound

				bIsReloading = true;
			}
			else
			{
				AmmoDiffGlock = ClipSizeGlock - AmmoGlock;
				AmmoGlock += MaxAmmoGlock;
				MaxAmmoGlock = 0;
				//Play sound

				bIsReloading = true;
			}
			GetWorld()->GetTimerManager().SetTimer(TriggerStopAnim, this,
				&AMainPlayerCharacter::DisableReloadAnim, 2.4f, true);
		}
		else
		{
			//Full ammo already!
			return;
		}
	}

}

void AMainPlayerCharacter::DisableReloadAnim()
{
	bIsReloading = false;
}

void AMainPlayerCharacter::TakeDamage()
{
	//15% of Damage
	Armor -= 0.15f;

	if (Armor < 0)
	{
		TakeHealthDamageCallWidget();

		Health += Armor;
		Armor = 0;

		if (Health < 0)
		{
			GameOver();
		}
	}
	else
	{
		TakeArmorDamageCallWidget();
	}
}

void AMainPlayerCharacter::TakeArmorDamageCallWidget()
{
	//Gets Player's Hud
	AMainHUD* Hud = UGameplayStatics::GetPlayerController(this, 0)->
		GetHUD<AMainHUD>();

	if (!Hud)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not get main HUD to show HealthDamage."));
		return;
	}

	// Request the main HUD to show the HealthDamage widget
	Hud->ToggleArmorDamageWidget(true);
}

void AMainPlayerCharacter::TakeHealthDamageCallWidget()
{
	//Gets Player's Hud
	AMainHUD* Hud = UGameplayStatics::GetPlayerController(this, 0)->
		GetHUD<AMainHUD>();

	if (!Hud)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not get main HUD to show ArmorDamage."));
		return;
	}

	// Request the main HUD to show the ArmorDamage widget
	Hud->ToggleDamageWidget(true);
}