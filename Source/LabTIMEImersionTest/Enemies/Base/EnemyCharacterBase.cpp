// 2023 Labverso, Brazil. Imersion Test.


#include "EnemyCharacterBase.h"
#include "LabTIMEImersionTest/ActorComponents/HealthComponent.h"
#include "LabTIMEImersionTest/SaveGameHighScore.h"
#include "LabTIMEImersionTest/MainPlayer/MainPlayerState.h"
#include <Kismet/GameplayStatics.h>

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

    //bool bIsHighScoreAlreadySet = UGameplayStatics::DoesSaveGameExist(SlotName, 0);

    //if (bIsHighScoreAlreadySet)
    //{
    //    SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, 0);

    //    USaveGameHighScore* SaveGameHS = Cast<USaveGameHighScore>(SaveGameObject);

    //    if (SaveGameHS)
    //    {
    //        AMainPlayerState* MainPlayerState = Cast<AMainPlayerState>(UGameplayStatics::GetActorOfClass(this, AMainPlayerState::StaticClass()));
    //        if (MainPlayerState)
    //        {
    //            MainPlayerState->SetHighScore(SaveGameHS->HighScore);
    //        }
    //    }
    //}

    //GameInstance = UGameplayStatics::GetGameInstance(GetWorld());

    //class UMyGameInstance* CastedInstance = Cast<UMyGameInstance>(GameInstance);

    //if (CastedInstance != nullptr)
    //{
    //    // The object was successfully casted to BP_MyGameInstance
    //    // Retrieve the value of bIsEnemyArmored variable
    // 
    //    bool bIsEnemyArmored = CastedInstance->bIsEnemyArmored;
    //}

    
}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
