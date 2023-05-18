// 2023 Labverso, Brazil. Imersion Test.


#include "CPP_MainPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LabTIMEImersionTest/Interface/MainHUD.h"

// Sets default values
ACPP_MainPlayerCharacter::ACPP_MainPlayerCharacter()
{
 	// Set this character to call Tick() every frame. You can turn this off to
	//improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

ACPP_MainPlayerCharacter::~ACPP_MainPlayerCharacter()
{
}

// Called when the game starts or when spawned
void ACPP_MainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPP_MainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACPP_MainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* 
	PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, 
		&ACPP_MainPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, 
		&ACPP_MainPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, 
		&ACPP_MainPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this,
		&ACPP_MainPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this,
		&ACPP_MainPlayerCharacter::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this,
		&ACPP_MainPlayerCharacter::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, 
		this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released,
		this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed,
		this, &ACPP_MainPlayerCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released,
		this, &ACPP_MainPlayerCharacter::StopSprinting);

	PlayerInputComponent->BindAction(TEXT("SelectPrimaryWeapon"), 
		EInputEvent::IE_Pressed, this, 
		&ACPP_MainPlayerCharacter::SelectPrimaryWeapon);
	PlayerInputComponent->BindAction(TEXT("SelectSecondaryWeapon"), 
		EInputEvent::IE_Pressed, this, 
		&ACPP_MainPlayerCharacter::SelectSecondaryWeapon);

	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed,
		this, &ACPP_MainPlayerCharacter::Crouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released,
		this, &ACPP_MainPlayerCharacter::StopCrouching);

	PlayerInputComponent->BindAction(TEXT("AimDownSight"), 
		EInputEvent::IE_Pressed, this,&ACPP_MainPlayerCharacter::AimDownSight);
	PlayerInputComponent->BindAction(TEXT("AimDownSight"), 
		EInputEvent::IE_Released, this, &ACPP_MainPlayerCharacter::StopAiming);

	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed,
		this, &ACPP_MainPlayerCharacter::Reload);

	PlayerInputComponent->BindAction(TEXT("PrimaryFire"),
		EInputEvent::IE_Pressed, this,
		&ACPP_MainPlayerCharacter::PrimaryFire);
	PlayerInputComponent->BindAction(TEXT("PrimaryFire"),
		EInputEvent::IE_Released, this,
		&ACPP_MainPlayerCharacter::StopFiring);

}
                                                                               
void ACPP_MainPlayerCharacter::MoveForward(float AxisValue)
{
	//Get Rotation and Axis of the Player
	const FRotator GetPawnRotation = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector Forward = UKismetMathLibrary::GetForwardVector(
		GetPawnRotation);

	// Add movement input along the given world direction vector
	AddMovementInput(Forward, AxisValue);
}

void ACPP_MainPlayerCharacter::MoveRight(float AxisValue)
{	
	//Get Rotation and Axis of the Player
	const FRotator GetPawnRotation = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector Right = UKismetMathLibrary::GetRightVector(
		GetPawnRotation);

	// Add movement input along the given world direction vector
	AddMovementInput(Right, AxisValue); 
}

void ACPP_MainPlayerCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ACPP_MainPlayerCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ACPP_MainPlayerCharacter::TurnRate(float AxisValue)
{
	float frameDeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(AxisValue * BaseTurnRate * frameDeltaTime);
}

void ACPP_MainPlayerCharacter::LookUpRate(float AxisValue)
{
	float frameDeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(AxisValue * BaseLookUpRate * frameDeltaTime);
}

void ACPP_MainPlayerCharacter::SelectPrimaryWeapon()
{
	WeaponSelected = 1;

	ShowAK_Cpp();
}


void ACPP_MainPlayerCharacter::SelectSecondaryWeapon()
{
	WeaponSelected = 2;

	ShowGlock_Cpp();
}

void ACPP_MainPlayerCharacter::AimDownSight()
{
	if (bIsReloading)
	{
		return;
	}
	
	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}
	
	ActivateAds_Cpp();
	bIsAiming = true;
}

void ACPP_MainPlayerCharacter::StopAiming()
{
	DeactivateAds_Cpp();
}

void ACPP_MainPlayerCharacter::PrimaryFire()
{
	if (bIsSprinting || bIsReloading)
	{
		return;
	}

	switch (WeaponSelected)
	{
		case 1:
			if (AmmoAK >= 1)
			{
				bIsFiring = true;
				FireAK_CPP();
			}
			break;
		case 2:
			if (AmmoGlock >= 1)
			{
				bIsFiring = true;
				FireGlock_CPP();
			}
			break;
		default:
			break;
	}
}

void ACPP_MainPlayerCharacter::StopFiring()
{
	bIsFiring = false;
}

void ACPP_MainPlayerCharacter::Sprint()
{
	//If the player is aiming the player cannot sprint, so this deactivates 
	// the aim.
	if (bIsAiming)
	{ 
		DeactivateAds_Cpp();
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

void ACPP_MainPlayerCharacter::StopSprinting()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void ACPP_MainPlayerCharacter::Crouch()
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

void ACPP_MainPlayerCharacter::StopCrouching()
{
	bIsCrouching = false;

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	UnCrouch();
}


void ACPP_MainPlayerCharacter::Reload()
{
	if (bIsAiming || bIsFiring)
	{
		return;
	}

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

void ACPP_MainPlayerCharacter::ReloadLogic(int CurrentWeapon)
{
	if (CurrentWeapon == 1) 
	{
		if (MaxAmmoAK <= 0)
		{
			//No more Bullets
			return;
		}

		if (AmmoAK < ClipSizeAK)
		{
			bIsReloading = true;
			if (MaxAmmoAK > (ClipSizeAK - AmmoAK))
			{
				AmmoDiffAk = ClipSizeAK - AmmoAK;
				AmmoAK += AmmoDiffAk;
				MaxAmmoAK -= AmmoDiffAk;
				//Play sound

			}
			else
			{
				AmmoDiffAk = ClipSizeAK - AmmoAK;
				AmmoAK += MaxAmmoAK;
				MaxAmmoAK = 0;
				//Play sound

			}
			GetWorld()->GetTimerManager().SetTimer(TriggerStopAnim, this, &ACPP_MainPlayerCharacter::DisableReloadAnim, 2.4f, true);
		}
		else
		{
			//Full ammo already!
			return;
		}
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
			GetWorld()->GetTimerManager().SetTimer(TriggerStopAnim, this, &ACPP_MainPlayerCharacter::DisableReloadAnim, 2.4f, true);
		}
		else
		{
			//Full ammo already!
			return;
		}
	}
	
}

void ACPP_MainPlayerCharacter::DisableReloadAnim()
{
	bIsReloading = false;
}


