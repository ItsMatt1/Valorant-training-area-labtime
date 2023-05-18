// 2023 Labverso, Brazil. Imersion Test.


#include "CPP_MainPlayerController.h"
#include "LabTIMEImersionTest/Interface/MainHUD.h"

void ACPP_MainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind the player "OpenScoreboard" input to show the scoreboard widget
	InputComponent->BindAction("OpenScoreboard", IE_Pressed,
		this, &ACPP_MainPlayerController::RequestOpenScoreBoard);
	InputComponent->BindAction("OpenScoreboard", IE_Released,
		this, &ACPP_MainPlayerController::RequestCloseScoreBoard);
}

void ACPP_MainPlayerController::RequestOpenScoreBoard()
{
	AMainHUD* PlayerMainHUD = Cast<AMainHUD>(GetHUD());
	if (!PlayerMainHUD)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not get main HUD to show scoreboard."));
		return;
	}

	// Request the main HUD to show the scoreboard widget
	PlayerMainHUD->ToggleScoreboardWidget(true);
}

void ACPP_MainPlayerController::RequestCloseScoreBoard()
{
	AMainHUD* PlayerMainHUD = Cast<AMainHUD>(GetHUD());
	if (!PlayerMainHUD)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Could not get main HUD to show scoreboard."));
		return;
	}

	// Request the main HUD to show the scoreboard widget
	PlayerMainHUD->ToggleScoreboardWidget(false);
}

