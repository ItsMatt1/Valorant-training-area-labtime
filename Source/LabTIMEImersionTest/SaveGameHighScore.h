// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameHighScore.generated.h"

/**
 * 
 */
UCLASS()
class LABTIMEIMERSIONTEST_API USaveGameHighScore : public USaveGame
{
	GENERATED_BODY()

public:

	int32 HighScore = 0;
	
};
