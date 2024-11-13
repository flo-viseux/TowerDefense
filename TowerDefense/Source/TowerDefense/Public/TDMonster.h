#pragma once

#include "CoreMinimal.h"
#include "TDAbility.h"
#include "TDEffect.h"
#include "GameFramework/Pawn.h"
#include "Components/SplineComponent.h"
#include "TDMonster.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateHealth, float, PercentHealth, int, CurrentHealth);

UCLASS()
class TOWERDEFENSE_API ATDMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDMonster();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Gold")
	int GetGold() const;

	UFUNCTION(BlueprintCallable, Category="Path")
	void SetSplinePath(USplineComponent* NewSpline);
	
	UFUNCTION(BlueprintCallable, Category="Path")
	USplineComponent* GetPath() const;
	
	UFUNCTION(BlueprintCallable, Category="Path")
	float GetDistanceAlongPath() const;

	UFUNCTION(BlueprintCallable, Category="Path")
	void DealDamageAndDestroy();

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void ApplyEffect(FTDEffect Effect);
	
	UFUNCTION(BlueprintCallable, Category = "Effect")
	void RemoveEffect(FTDEffect Effect);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnUpdateHealth OnUpdateHealth;

private:
	FTDAbility HealthAbility;
	
	FTDAbility SpeedAbility;

	FTDEffect DamageEffect;

	TArray<FTDEffect> CurrentTemporaryEffects;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	float InitialHealth = 100;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	float InitialSpeed = 10;

	UPROPERTY(EditAnywhere, Category = "Effect")
	float InitialDamage = -10;

	UPROPERTY(EditAnywhere, Category = "Gold")
	int Gold = 25;

	UPROPERTY()
	USplineComponent* PathToFollow;

	float DistanceAlongPath;
	
	bool bReachedEnd = false;
};
