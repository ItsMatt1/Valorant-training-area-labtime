// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABTIMEIMERSIONTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	/** Override of the TakeAnyDamage function of unreal, its called when you
	want to make the actor take damage.
	* @param DamagedActor, Actor that will be damaged.
	* @param Damage, the amount of damage that will be taken.
	* @param InstigatedBy, Controller that was responsible for causing this
		damage (e.g. player who shot the weapon).
	* @param DamageType, Class that describes the damage that was done.
	* @param DamageCauser, Actor that directly caused the damage.
	*/
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, 
		const class UDamageType* DamageType, class AController* InstigatedBy, 
		AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	/** The health that the actor starts. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Health")
	float DefaultHealth = 1;
	
	/** The health that the actor is currently at. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Health")
	float Health = 1;

	/** The armor that the actor starts. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Armor")
	float DefaultArmor = 1;

	/** The armor that the actor is currently at. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Armor")
	float Armor = 1;
};
