// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

/**
* This is the player main player state.
* This player state will keep track of the player's score on the game.
* Thus, at this moment stores the amount of enemies we has killed.
* This class can be accessed to show the player score on the screen, 
* for instance.
*/
UCLASS()
class LABTIMEIMERSIONTEST_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	/** 
	* Getter to the enemies killed amount. The amount of enemies 
	* killed by the player.
	* 
	* @return The amount of enemies the player has killed since last reset.
	*/
	UFUNCTION(BlueprintCallable, 
		meta=(Tooltip="Get the amount of enemies killed by the player"))
	int32 GetEnemiesKilledAmount() { return EnemiesKilledAmount; }

	/**
	* Increment the EnemiesKilledAmount in one unit.
	* 
	* its called when player kills an enemy.
	* @return The amount of enemies the player has killed since last reset.
	*/
	UFUNCTION(BlueprintCallable,
		meta = (Tooltip = "Increment the amount of kills."))
	int32 UpdateEnemiesKilledAmount() { EnemiesKilledAmount++;
		return EnemiesKilledAmount; }

	/**
	* Getter to the highest score of the player.
	* 
	* @note stored at \Saved\SaveGames\High Score Slot.sav
	* @return PlayerHighScore.
	*/
	UFUNCTION(BlueprintCallable,
		meta = (Tooltip = 
			"Get the highest amount of enemies killed by the player"))
	int32 GetHighScore() { return PlayerHighScore; }

	/**
	* Setter to the highest score of the player.
	* 
	* @note stored at \Saved\SaveGames\High Score Slot.sav
	* @return PlayerHighScore.
	*/
	UFUNCTION(BlueprintCallable,
		meta = (Tooltip =
			"Set the highest amount of enemies killed by the player"))
	int32 SetHighScore(int NewHighScore) { PlayerHighScore = NewHighScore;
		return PlayerHighScore; }

	/** Player defined the playtime. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Settings");
	int32 SecondsDefined = 0;

	/** Player defined the kill limit. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Settings");
	int32 KillsDefined = 0;

	/** Player defined if the enemies will have armor or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Settings");
	bool ArmorDefined = false;

private:
	/** The amount of enemies killed by the player on the current round. */
	int32 EnemiesKilledAmount = -1;

	/** The amount of enemies killed by the player on the current round. */
	int32 PlayerHighScore = 0;
};
