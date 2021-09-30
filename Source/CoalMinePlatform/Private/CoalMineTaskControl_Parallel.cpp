// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskControl_Parallel.h"


ACoalMineTaskControl_Parallel::ACoalMineTaskControl_Parallel()
{
    ConstructorHelpers::FObjectFinder<UTexture2D>IconImg(TEXT("/Game/CoalMinePlatform/Arts/Parallel"));
    if (IconImg.Succeeded())
    {
        UE_LOG(LogTemp, Warning, TEXT("Parallel Task Control Icon Is Found"));
        BillBoardComp->SetSprite(IconImg.Object);
    }
    ParallelVisualizationComponent = CreateDefaultSubobject<UParallelVisualizationComponent>(TEXT("ParallelTaskVisualizationComp"));
    ParallelVisualizationComponent->SetupAttachment(BillBoardComp);
}

void ACoalMineTaskControl_Parallel::OnInitialize_Implementation(ACoalMineTaskManager* NewTaskManager)
{
    Super::OnInitialize_Implementation(NewTaskManager);
    for (ACoalMineTaskBase* Task: CurrentTasks)
    {
        if (Task && Task->Status == ETaskStatus::Running)
        {
            Task->Abort();
        }
    }
    CurrentTasks.Empty();
    for (ACoalMineTaskBase* Task : SubTasks)
    {
        CurrentTasks.AddUnique(Task);
    }
    FailedTaskCount = 0;
}

ETaskStatus ACoalMineTaskControl_Parallel::OnUpdate_Implementation(float DeltaTime)
{
    TArray<ACoalMineTaskBase*>TaskToDelete;
    for (ACoalMineTaskBase* Task : CurrentTasks)
    {
        if (Task && Task->Status !=ETaskStatus::Running)
        {
            Task->OnInitialize(TaskManager);
        }
        switch (Task->OnUpdate(DeltaTime))
        {
        case ETaskStatus::Success:
        {
            Task->OnFinish();
            TaskToDelete.AddUnique(Task);
            if (SuccessPolicy==ESuccessPolicy::Policy_RequireOne)
            {
                Status = ETaskStatus::Success;
            }
        }
        break;
        
        case ETaskStatus::Failure:
        {
            FailedTaskCount++;
            Task->OnFinish();
            TaskToDelete.AddUnique(Task);
            if (FailPolicy==EFailPolicy::Policy_RequireOne)
            {
                Status = ETaskStatus::Failure;
            }
        }
        break;

        default:
            break;
        }
    }
    for (ACoalMineTaskBase* Task : TaskToDelete)
    {
        CurrentTasks.RemoveSwap(Task);
    }
    if (Status==ETaskStatus::Success||Status==ETaskStatus::Failure)
    {
        AbortCurrentTasks();
        return Status;
    }

    if (CurrentTasks.Num()<1)
    {
        if (SuccessPolicy==ESuccessPolicy::Policy_RequireAll)
        {
            if (FailedTaskCount>0)
            {
                Status = ETaskStatus::Failure;
                UE_LOG(LogTemp, Warning, TEXT("Parallel Task Control is Failed,because it Require All SubTasks Success"));
                return Status;
            }
        }
        if (FailPolicy==EFailPolicy::Policy_RequireAll)
        {
            if (FailedTaskCount>=SubTasks.Num())
            {
                Status = ETaskStatus::Failure;
                UE_LOG(LogTemp, Warning, TEXT("Parallel Task Control is Failed,because All SubTasks both failed"));
                return Status;
            }
        }
		Status = ETaskStatus::Success;
		return Status;
    }
    return Status;
}

void ACoalMineTaskControl_Parallel::Abort_Implementation()
{
    Super::Abort_Implementation();
    AbortCurrentTasks();
}

void ACoalMineTaskControl_Parallel::AbortCurrentTasks()
{
	for (ACoalMineTaskBase* Task : CurrentTasks)
	{
		if (Task)
		{
			Task->Abort();
            UE_LOG(LogTemp, Warning, TEXT("Abort Current Tasks is Called"));
            UE_LOG(LogTemp, Warning, TEXT("Manual To Abort Parallel Task Control"));
		}
	}
}
