// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_MainPlayerCharacter.generated.h"

UCLASS()
class LABTIMEIMERSIONTEST_API ACPP_MainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_MainPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	// Movement Inputs
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	//Mouse Inputs
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	//Gamepad Look Inputs
	void TurnRate(float AxisValue);
	void LookUpRate(float AxisValue);

	UPROPERTY(EditAnywhere)
		float BaseTurnRate = 45.f;

	UPROPERTY(EditAnywhere)
		float BaseLookUpRate = 45.f;
};
 