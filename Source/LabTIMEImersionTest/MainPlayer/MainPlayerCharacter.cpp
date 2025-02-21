// 2023 Labverso, Brazil. Imersion Test.


#include "MainPlayerCharacter.h"
#include "MainPlayerController.h"
#include "LabTIMEImersionTest/ActorComponents/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "LabTIMEImersionTest/Interface/MainHUD.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainPlayerCharacter::AMainPlayerCharacter()
{
	// Set this character to call Tick() every frame. You can turn this off to
	//improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Adding the health component on editor
	HealthComponent = CreateDefaultSubobject<UHealthComponent>
		(TEXT("HealthComponent"));
	
	//Adding the camera component on editor
	FollowCamera = CreateDefaultSubobject<UCameraComponent>
		(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh(), "Head");
	FollowCamera->bUsePawnControlRotation = true;

	OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
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

	//Spawning AK-47
	auto SpawnAk = GetWorld()->SpawnActor<AWeaponBase>(AK47,
		Location, Rotation);

	SpawnAk->AttachToComponent(GetMesh(), FAttachmentTransformRules::
		SnapToTargetIncludingScale, "Weapon_Attach");

	//Spawning Glock
	auto SpawnGlock = GetWorld()->SpawnActor<AWeaponBase>(Glock,
		Location, Rotation);

	SpawnGlock->AttachToComponent(GetMesh(), FAttachmentTransformRules::
		SnapToTargetIncludingScale, "Weapon_Attach");

	SpawnGlock->GetRootComponent()->SetVisibility(false, true);

	AvailableWeapons.Add("AK-47", SpawnAk);
	AvailableWeapons.Add("Glock", SpawnGlock);

	if (!AvailableWeapons.Contains("AK-47"))
	{
		UE_LOG(LogTemp, Error,
			TEXT("Gun AK-47 not found."));
		return;
	}

	//Player starts with the AK-47
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
		this, &AMainPlayerCharacter::RequestCrouch);
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
	//Player cant reload if it is aiming.
	if (EquippedWeapon->bIsReloading)
	{
		return;
	}

	//Player cant sprint if it is aiming.
	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}

	FollowCamera->Deactivate();

	EquippedWeapon->EnableCamera();

	GetCharacterMovement()->MaxWalkSpeed = CrouchingSpeed;

	bIsAiming = true;

	OurPlayerController->SetViewTargetWithBlend(EquippedWeapon);
}

void AMainPlayerCharacter::StopAiming()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	FollowCamera->Activate();

	EquippedWeapon->DisableCamera();

	bIsAiming = false;

	OurPlayerController->SetViewTargetWithBlend(this);
}

void AMainPlayerCharacter::PrimaryFire()
{
	//Disables firing if the player is sprinting or reloading.
	if (bIsSprinting || EquippedWeapon->bIsReloading)
	{
		return;
	}

	keepFiring = true;
	VerifyFiring();

	//Activating a "delay" for the automatic weapon.
	GetWorld()->GetTimerManager().SetTimer(FireRate, this,
		&AMainPlayerCharacter::VerifyFiring, 0.1f, true);
}

void AMainPlayerCharacter::VerifyFiring()
{
	if (!keepFiring)
	{
		GetWorld()->GetTimerManager().ClearTimer(FireRate);
		return;
	}

	if (FString(EquippedWeapon->GetWeaponName()).Equals("Glock"))
	{
		EquippedWeapon->FireWeapon(bIsAiming ? nullptr : FollowCamera);
		keepFiring = false; // Stop firing after one shot for Glock.
		return;
	}

	EquippedWeapon->FireWeapon(bIsAiming ? nullptr : FollowCamera);
}


void AMainPlayerCharacter::StopFiring()
{
	EquippedWeapon->bIsFiring = false;
	keepFiring = false;
}

void AMainPlayerCharacter::Sprint()
{
	//If the player is aiming the player cannot sprint, so this deactivates 
	// the aim.
	if (bIsAiming)
	{
		StopAiming();
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

void AMainPlayerCharacter::RequestCrouch()
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

	ACharacter::UnCrouch();
}


void AMainPlayerCharacter::Reload()
{
	if (bIsAiming || EquippedWeapon->bIsFiring)
	{
		return;
	}

	EquippedWeapon->ReloadWeapon();

	UGameplayStatics::PlaySound2D(GetWorld(), ReloadSound);

	GetWorld()->GetTimerManager().SetTimer(TriggerStopAnim, this,
		&AMainPlayerCharacter::DisableReloadAnim, 2.4f, true);
}

void AMainPlayerCharacter::DisableReloadAnim()
{
	EquippedWeapon->bIsReloading = false;
}

void AMainPlayerCharacter::HandleDamageWidget()
{
	if (HealthComponent->Armor > 0)
	{
		TakeArmorDamageCallWidget();
		return;
	}

	TakeHealthDamageCallWidget();

	if (HealthComponent->Health <= 0)
	{
		GameOver();
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
			TEXT("Could not get main HUD to show ArmorDamage."));
		return;
	}

	// Request the main HUD to show the Armor Damage widget.
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
			TEXT("Could not get main HUD to show HealthDamage."));
		return;
	}

	// Request the main HUD to show the Health Damage Widget.
	Hud->ToggleDamageWidget(true);
}