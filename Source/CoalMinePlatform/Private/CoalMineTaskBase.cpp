// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskBase.h"
#include "CoalMineTaskManager.h"

// Sets default values
ACoalMineTaskBase::ACoalMineTaskBase()
{
	PrimaryActorTick.bCanEverTick = false;
	SetHidden(true);

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	bNetLoadOnClient = false;

	BillBoardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	BillBoardComp->SetupAttachment(RootComp);
}

void ACoalMineTaskBase::OnInitialize_Implementation(ACoalMineTaskManager* NewManager)
{
	Status = ETaskStatus::Running;
	TaskManager = NewManager;
}

ETaskStatus ACoalMineTaskBase::OnUpdate_Implementation(float DeltaTime)
{
	return Status;
}

void ACoalMineTaskBase::OnFinish_Implementation()
{
}

void ACoalMineTaskBase::Abort_Implementation()
{
	Status = ETaskStatus::Idle;
}