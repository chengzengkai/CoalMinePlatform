// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskManager.h"
#include "CoalMineTaskBase.h"
#include "Components/BillboardComponent.h"
#include "ManagerVisualizationComponent.h"

// Sets default values
ACoalMineTaskManager::ACoalMineTaskManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BillboardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("Icon"));
	SetRootComponent(BillboardComp);
	ConstructorHelpers::FObjectFinder<UTexture2D>IconImg(TEXT("/Game/CoalMinePlatform/Arts/TaskManager"));
	if (IconImg.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Sequence Task Control Icon Is Found"));
		BillboardComp->SetSprite(IconImg.Object);
	}

	TaskManagerVisualizationComp = CreateDefaultSubobject<UManagerVisualizationComponent>(TEXT("TaskManagerVisualizer"));
	if (TaskManagerVisualizationComp)
	{
		TaskManagerVisualizationComp->SetupAttachment(BillboardComp);
	}
}

// Called when the game starts or when spawned
void ACoalMineTaskManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoalMineTaskManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Status == ETaskManagerStatus::TaskManager_Running)
	{
		TArray<ACoalMineTaskBase*> TasksToDelete;

		ETaskManagerStatus PendingStatus = ETaskManagerStatus::TaskManager_Running;

		for (ACoalMineTaskBase* CurrentTask : CurrentTasks)
		{
			if (CurrentTask->Status != ETaskStatus::Running)
			{
				CurrentTask->OnInitialize(this);
			}
			switch (CurrentTask->OnUpdate(DeltaTime))
			{
			case ETaskStatus::Failure:

				PendingStatus = ETaskManagerStatus::TaskManager_Failure;
				TasksToDelete.AddUnique(CurrentTask);
				CurrentTask->OnFinish();
				break;

			case ETaskStatus::Success:

				PendingStatus = ETaskManagerStatus::TaskManager_Success;
				TasksToDelete.AddUnique(CurrentTask);
				CurrentTask->OnFinish();
				break;
			default:
				break;
			}
			for (ACoalMineTaskBase* TaskToDelete : TasksToDelete)
			{
				CurrentTasks.RemoveSwap(TaskToDelete);
			}
			if (CurrentTasks.Num() < 1)
			{
				FinishLevel(PendingStatus);
			}
		}
	}	
}

void ACoalMineTaskManager::StartLevel_Implementation()
{
	Status = ETaskManagerStatus::TaskManager_Running;
	
	for (ACoalMineTaskBase* Task:CurrentTasks)
	{
		if (Task && Task->Status == ETaskStatus::Running)
		{
			Task->Abort();
		}
	}
	if (InitialTask&&InitialTask->Status==ETaskStatus::Running)
	{
		InitialTask->Abort();
	}
	CurrentTasks.Add(InitialTask);
}

void ACoalMineTaskManager::FinishLevel_Implementation(ETaskManagerStatus NewStatus)
{
	Status = NewStatus;
	OnLevelFinish(Status);
}

void ACoalMineTaskManager::AbortLevel_Implementation()
{
	for (ACoalMineTaskBase* Task:CurrentTasks)
	{
		if (Task&&Task->Status==ETaskStatus::Running)
		{
			Task->Abort();
		}
	}
	Status = ETaskManagerStatus::TaskManager_Idle;
	OnAbortLevel();
}

void ACoalMineTaskManager::OnLevelFinish_Implementation(ETaskManagerStatus NewStatus)
{

}

void ACoalMineTaskManager::OnAbortLevel_Implementation()
{

}
