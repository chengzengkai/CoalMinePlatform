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
    CurrentTaskIndex = 0;
}

ETaskStatus ACoalMineTaskControl_Parallel::OnUpdate_Implementation(float DeltaTime)
{
	return ETaskStatus();

}

void ACoalMineTaskControl_Parallel::Abort_Implementation()
{
}
void ACoalMineTaskControl_Parallel::OnInitialize_Implementation(ACoalMineTaskManager* NewTaskManager)
{

}