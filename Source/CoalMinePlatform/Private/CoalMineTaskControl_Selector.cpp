// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskControl_Selector.h"

ACoalMineTaskControl_Selector::ACoalMineTaskControl_Selector()
{
    ConstructorHelpers::FObjectFinder<UTexture2D>IconImg(TEXT("/Game/CoalMinePlatform/Arts/Selector"));
    if (IconImg.Succeeded())
    {
        UE_LOG(LogTemp, Warning, TEXT("Sequence Task Control Icon Is Found"));
        BillboardComp->SetSprite(IconImg.Object);
    }
}