// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskControl_Sequence.h"
#include "Engine/Classes/Engine/Texture2D.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"


ACoalMineTaskControl_Sequence::ACoalMineTaskControl_Sequence() 
{
    ConstructorHelpers::FObjectFinder<UTexture2D>IconImg(TEXT("/Game/CoalMinePlatform/Arts/Sequence"));
    if(IconImg.Succeeded())
    {
        UE_LOG(LogTemp,Warning,TEXT("Sequence Task Control Icon Is Found"));
        BillBoardComp->SetSprite(IconImg.Object);
    }
    SequentialVisualizationComp = CreateDefaultSubobject<USequentialVisualizationComponent>(TEXT("SequentialTaskVisualizationComp"));
    SequentialVisualizationComp->SetupAttachment(BillBoardComp);
    CurrentTaskIndex = 0;
}

void ACoalMineTaskControl_Sequence::OnInitialize_Implementation(ACoalMineTaskManager* NewTaskManager)
{
    Super::OnInitialize_Implementation(NewTaskManager);

    if (CurrentTask && CurrentTask->Status == ETaskStatus::Running)
    {
        CurrentTask->Abort();
    }

    CurrentTaskIndex = 0;
    CurrentTask = SubTasks[CurrentTaskIndex];
}

ETaskStatus ACoalMineTaskControl_Sequence::OnUpdate_Implementation(float DeltaTime)
{
    if (CurrentTask)
    {
        if (CurrentTask->Status != ETaskStatus::Running)
        {
            CurrentTask->OnInitialize(TaskManager);
        }

        bool bTaskChanged = false;
        switch (CurrentTask->OnUpdate(DeltaTime))
        {
            case ETaskStatus::Success:
            {
                CurrentTask->OnFinish();
                CurrentTaskIndex++;
                bTaskChanged = true;
            }
            break;
            case ETaskStatus::Failure:
            {
                Status = ETaskStatus::Failure;
                return Status;
            }
            break;
            default:
                break;
        }
        if (bTaskChanged)
        {
            if (CurrentTaskIndex<SubTasks.Num())
            {
                CurrentTask = SubTasks[CurrentTaskIndex];
            }
            else
            {
                Status = ETaskStatus::Success;
            }
        }
    }
    else
    {
        Status = ETaskStatus::Success;
    }
    return Status;
}

void ACoalMineTaskControl_Sequence::Abort_Implementation()
{
    Super::Abort_Implementation();
    if (CurrentTask && CurrentTask->Status == ETaskStatus::Running)
    {
        CurrentTask->Abort();
    }
}
