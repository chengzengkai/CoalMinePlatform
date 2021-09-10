// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskControl_Selector.h"

ACoalMineTaskControl_Selector::ACoalMineTaskControl_Selector()
{
    ConstructorHelpers::FObjectFinder<UTexture2D>IconImg(TEXT("/Game/CoalMinePlatform/Arts/Selector"));
    if (IconImg.Succeeded())
    {
        UE_LOG(LogTemp, Warning, TEXT("Sequence Task Control Icon Is Found"));
        BillBoardComp->SetSprite(IconImg.Object);
    }
    ParallelVisualizationComponent = CreateDefaultSubobject<UParallelVisualizationComponent>(TEXT("ParallelTaskVisualizationComp"));
    ParallelVisualizationComponent->SetupAttachment(BillBoardComp);
    ParallelVisualizationComponent->LineColor = FColor::Red;
    CurrentTaskIndex = 0;
}

void ACoalMineTaskControl_Selector::OnInitialize_Implementation(ACoalMineTaskManager* NewTaskManager)
{
}

ETaskStatus ACoalMineTaskControl_Selector::OnUpdate_Implementation(float DeltaTime)
{
    return ETaskStatus();
}

void ACoalMineTaskControl_Selector::Abort_Implementation()
{
}
