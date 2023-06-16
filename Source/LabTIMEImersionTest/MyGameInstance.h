// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LABTIMEIMERSIONTEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	int32 Seconds = 0;

	int32 KillLimit = 0;

	bool bIsEnemyArmored = false;
	
};
