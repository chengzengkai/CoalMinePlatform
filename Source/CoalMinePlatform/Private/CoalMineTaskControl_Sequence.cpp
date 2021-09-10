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
}

ETaskStatus ACoalMineTaskControl_Sequence::OnUpdate_Implementation(float DeltaTime)
{
    return ETaskStatus();
}

void ACoalMineTaskControl_Sequence::Abort_Implementation()
{
}
