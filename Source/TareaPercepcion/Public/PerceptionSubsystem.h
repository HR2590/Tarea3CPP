// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PerceptionComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "PerceptionSubsystem.generated.h"
DECLARE_DELEGATE_OneParam(FOnActorDetected,AActor*);



UCLASS(Blueprintable,BlueprintType,meta=(BlueprintSpawnableComponent))
class TAREAPERCEPCION_API UPerceptionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	void RegisterDetectedActor(AActor* InActor);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	UPROPERTY() TArray<AActor*> AllDetectedActors;
	UPROPERTY() TArray<AActor*> AllActorsWithPerception;
	void RemoveDetectedActor(AActor* InActor);
	void RemoveActorWithPerception(AActor* InActor);
	static bool IsPerceptionActive(const AActor* InActor);
	void RegisterActorWithPerception(AActor* InActor);
	void SetPerceptionToAll(const bool& InState);
	bool HasPerception(const AActor* InActor);
	void RegisterAllActorsWithPerception(TArray<AActor*> OutActors);
	void InitPerceptionInfo(const FPerceptionInfo& InPerceptionInfo,AActor* InActor) const;
	
public:
	FOnActorDetected OnActorDetected;
	void SetPerception(const int& InIndex,const bool& InState);

};
