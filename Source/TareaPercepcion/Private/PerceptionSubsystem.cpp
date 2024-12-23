// Fill out your copyright notice in the Description page of Project Settings.


#include "PerceptionSubsystem.h"
#include "PerceptionComponent.h"



void UPerceptionSubsystem::RegisterDetectedActor(AActor* InActor)
{
	if(IsPerceptionActive(InActor))AllDetectedActors.AddUnique(InActor);
	else RemoveDetectedActor(InActor);
	
}
void UPerceptionSubsystem::RegisterActorWithPerception(AActor* InActor)
{
	if(IsPerceptionActive(InActor))AllActorsWithPerception.AddUnique(InActor);
	else RemoveActorWithPerception(InActor);
}

void UPerceptionSubsystem::SetPerceptionToAll(const bool& InState)
{
	for (const auto& Actor : AllActorsWithPerception)
	{
		Actor->FindComponentByClass<UPerceptionComponent>()->SetPerception(InState);
	}
}

bool UPerceptionSubsystem::HasPerception(const AActor* InActor)
{
	if (!InActor) return false;
	return InActor->FindComponentByClass<UPerceptionComponent>()?true:false;
}

void UPerceptionSubsystem::RegisterAllActorsWithPerception(TArray<AActor*> OutActors)
{

for(TObjectIterator<AActor> It; It; ++It)
{
	if(HasPerception(*It))AllActorsWithPerception.AddUnique(*It);
}
}

void UPerceptionSubsystem::SetPerception(const int& InIndex, const bool& InState)
{
	if(!AllActorsWithPerception.Num())return;
	if (InIndex==-1) SetPerceptionToAll(InState);
	if(InIndex<0) return;
	AllActorsWithPerception[InIndex]->FindComponentByClass<UPerceptionComponent>()->SetPerception(InState);
	
}


void UPerceptionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterAllActorsWithPerception(AllActorsWithPerception);
	GetWorld()->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateUObject(this,&ThisClass::RegisterActorWithPerception));
	GetWorld()->AddOnActorDestroyedHandler(FOnActorDestroyed::FDelegate::CreateUObject(this,&ThisClass::RemoveActorWithPerception));
	OnActorDetected.BindUObject(this,&ThisClass::RegisterDetectedActor);
	
}
	

void UPerceptionSubsystem::Deinitialize()
{
	Super::Deinitialize();
	OnActorDetected.Unbind();

}

bool UPerceptionSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UPerceptionSubsystem::RemoveDetectedActor(AActor* InActor)
{
	AllDetectedActors.Remove(InActor);
}

void UPerceptionSubsystem::RemoveActorWithPerception(AActor* InActor)
{
AllActorsWithPerception.Remove(InActor);
}


bool UPerceptionSubsystem::IsPerceptionActive(const AActor* InActor)
{
	if (!InActor||!InActor->GetComponentByClass<UPerceptionComponent>()) return false;
	return InActor->FindComponentByClass<UPerceptionComponent>()->PerceptionInfo.IsPerceptionActive;
}




