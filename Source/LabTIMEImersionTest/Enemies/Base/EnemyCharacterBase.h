// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterBase.generated.h"

/** 
* This is the enemie's base character class. 
* This class deals with the base functionality of a enemy, e.g., it's movement.
* Extend this class for futher base functionalities.
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	/** Sets default values for this character's properties */
	AEnemyCharacterBase();

	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

public:
	/* Everytime the bullet hit an enemy this function is called,
	* this function verify if the health is equal to 0, if it is, call
	* EnemyKilled event and destroy its actor.
	* @note plans to implement it on cpp.
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = 
		"EnemyHitByBulletEvent"))
	void EnemyHitByBulletEvent();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:
	/** Creating Health Component on Enemy. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UHealthComponent* HealthComponent = nullptr;
};
