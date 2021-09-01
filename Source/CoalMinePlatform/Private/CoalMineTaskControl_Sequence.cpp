// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineTaskControl_Sequence.h"
#include "Engine/Classes/Engine/Texture2D.h"
#include "Components/BillboardComponent.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"


ACoalMineTaskControl_Sequence::ACoalMineTaskControl_Sequence() 
{
    // UTexture2D* Icon=FObjectFinder<UTexture2D>("/Game/CoalMinePlatform/Arts/Sequence.Sequence");
    // if(Icon)
    // {
    //     // BillboardComp->SetTexture
    // }
    ConstructorHelpers::FObjectFinder<UTexture2D>IconImg(TEXT("/Game/CoalMinePlatform/Arts/Sequence"));
    if(IconImg.Succeeded())
    {
        UE_LOG(LogTemp,Warning,TEXT("Sequence Task Control Icon Is Found"));
        BillboardComp->SetSprite(IconImg.Object);
    }
}
