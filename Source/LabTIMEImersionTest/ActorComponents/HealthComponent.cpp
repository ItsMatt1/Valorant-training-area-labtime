// 2023 Labverso, Brazil. Imersion Test.

#include "HealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be
	// ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();

	if (!MyOwner)
	{
		return;
	}

	MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage,
	const class UDamageType* DamageType, class AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (Damage <= 0)
	{
		UE_LOG(LogTemp,
			Warning,
			TEXT("%s received strangedamage amount: \"%f\". Maybe check damage dealer? (%s)"),
			*GetOwner()->GetName(), Damage, *DamageCauser->GetName());
		return;
	}

	if (Armor > 0)
	{
		//Receive armor damage, not let it pass 0.
		Armor = FMath::Clamp(Armor - Damage, 0.0f, DefaultArmor);
		return;
	}

	//Receive health damage, not let it pass 0.
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
}