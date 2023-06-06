// 2023 Labverso, Brazil. Imersion Test.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArmorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LABTIMEIMERSIONTEST_API UArmorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArmorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	/** The health that the actor starts. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Armor")
	float DefaultArmor = 1;

	/** The health that the actor is currently at. */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Armor")
	float Armor = 1;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
