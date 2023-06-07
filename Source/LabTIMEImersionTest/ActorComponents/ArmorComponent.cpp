// 2023 Labverso, Brazil. Imersion Test.


#include "ArmorComponent.h"

// Sets default values for this component's properties
UArmorComponent::UArmorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UArmorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UArmorComponent::TakeDamage(AActor* DamagedActor, float Damage,
	const class UDamageType* DamageType, class AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (Damage <= 0)
	{
		return;
	}

	//Receive armor damage, not let it pass 0.
	Armor = FMath::Clamp(Armor - Damage, 0.0f, DefaultArmor);
}