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
	TArray<ACoalMineTaskBase*> TasksToDelete;
	for (ACoalMineTaskBase* CurrentTask : CurrentTasks)
	{
		if (CurrentTask->Status != ETaskStatus::Running)
		{
			CurrentTask->OnInitialize(this);
		}
		switch (CurrentTask->OnUpdate(DeltaTime))
		{
		case ETaskStatus::Failure:
			TasksToDelete.AddUnique(CurrentTask);
			CurrentTask->OnFinish();
			break;

		case ETaskStatus::Success:
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
	}
}