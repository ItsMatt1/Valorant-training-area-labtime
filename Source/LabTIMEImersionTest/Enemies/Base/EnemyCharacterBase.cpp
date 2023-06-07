// 2023 Labverso, Brazil. Imersion Test.


#include "EnemyCharacterBase.h"
#include "LabTIMEImersionTest/ActorComponents/HealthComponent.h"

// Sets default values
AEnemyCharacterBase::AEnemyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//Adding the health component on editor
	HealthComponent = CreateDefaultSubobject<UHealthComponent>
		(TEXT("HealthComponent"));
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
