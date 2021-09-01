// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineSubsystem.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "MovieScene/Public/MovieSceneSequencePlayer.h"
void UCoalMineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCoalMineSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UCoalMineSubsystem::PlaySequence(ULevelSequence* Sequence)
{
	UGameInstance* GI = Cast<UGameInstance>(GetOuter());
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is invalid,can not spawn levelsequenceActor"));
		return;
	}
	ALevelSequenceActor* LSActor=World->SpawnActor<ALevelSequenceActor>(ALevelSequenceActor::StaticClass(), FActorSpawnParameters());
	if (LSActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn levelsequenceactor"));
		return;
	}
	LSActor->SetSequence(Sequence);
	LSActor->GetSequencePlayer()->Play();
}
