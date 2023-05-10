// 2023 Labverso, Brazil. Imersion Test.


#include "CPP_MainPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACPP_MainPlayerCharacter::ACPP_MainPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SprintSpeed = 1000.f;
	WalkingSpeed = 600.f;
	CrouchingSpeed = WalkingSpeed / 2;

	WeaponSelected = 1;
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

	PlayerInputComponent->BindAction(TEXT("SelectPrimaryWeapon"), EInputEvent::IE_Pressed,
		this, &ACPP_MainPlayerCharacter::SelectPrimaryWeapon);
	PlayerInputComponent->BindAction(TEXT("SelectSecondaryWeapon"), EInputEvent::IE_Pressed,
		this, &ACPP_MainPlayerCharacter::SelectSecondaryWeapon);

	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed,
		this, &ACPP_MainPlayerCharacter::Crouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released,
		this, &ACPP_MainPlayerCharacter::StopCrouching);

}
                                                                               
/**
* This fuction makes the player move on Z axis
* @param AxisValue
*/
void ACPP_MainPlayerCharacter::MoveForward(float AxisValue)
{
	//Get Rotation and Axis of the Player
	const FRotator GetPawnRotation = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector Forward = UKismetMathLibrary::GetForwardVector(
		GetPawnRotation);

	// Add movement input along the given world direction vector
	AddMovementInput(Forward, AxisValue);
}

/**
* This fuction makes the player move on Y axis
* @param AxisValue
*/
void ACPP_MainPlayerCharacter::MoveRight(float AxisValue)
{	
	//Get Rotation and Axis of the Player
	const FRotator GetPawnRotation = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector Right = UKismetMathLibrary::GetRightVector(
		GetPawnRotation);

	AddMovementInput(Right, AxisValue); 
}

/**
* This fuction makes the player move the camera on X
* @param AxisValue
*/
void ACPP_MainPlayerCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

/**
* This fuction makes the player move the camera on Y 
* @param AxisValue
*/
void ACPP_MainPlayerCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}


/**
* This fuction sooths the camera movement on Y given the fps
* @param AxisValue
*/
void ACPP_MainPlayerCharacter::TurnRate(float AxisValue)
{
	float frameDeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(AxisValue * BaseTurnRate * frameDeltaTime);
}

/**
* This fuction sooths the camera movement on X given the fps
* @param AxisValue
*/
void ACPP_MainPlayerCharacter::LookUpRate(float AxisValue)
{
	float frameDeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(AxisValue * BaseLookUpRate * frameDeltaTime);
}

void ACPP_MainPlayerCharacter::SelectPrimaryWeapon()
{
	WeaponSelected = 1;

}

void ACPP_MainPlayerCharacter::SelectSecondaryWeapon()
{
	WeaponSelected = 2;
}

void ACPP_MainPlayerCharacter::Sprint()
{
	isSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ACPP_MainPlayerCharacter::StopSprinting()
{
	isSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void ACPP_MainPlayerCharacter::Crouch()
{
	if (isSprinting)
		isSprinting = false;

	isCrouching = true;

	GetCharacterMovement()->MaxWalkSpeed = CrouchingSpeed;

	ACharacter::Crouch();

}

void ACPP_MainPlayerCharacter::StopCrouching()
{
	isCrouching = false;

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	UnCrouch();
}


