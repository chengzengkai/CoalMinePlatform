// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskLinkComponent.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"

FPrimitiveSceneProxy* UTaskLinkComponent::CreateSceneProxy()
{
    class FDrawTaskSceneProxy :public FPrimitiveSceneProxy
    {
    public:
        SIZE_T GetTypeHash()const override
        {
            return 0;
        }
        FDrawTaskSceneProxy(const UTaskLinkComponent* InComponent):LineThickness(10.f),LineColor(FColor::Blue),FPrimitiveSceneProxy(InComponent)
        {
            Owner=InComponent->GetOwner();
        }
        virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
        {
            const FMatrix& LocalToWorld = GetLocalToWorld();
            FBox TestBox = FBox(FVector(-100.f), FVector(100.f));
            DrawWireBox(
                Collector.GetPDI(0),
                LocalToWorld,
                TestBox,
                FLinearColor::Blue,
                ESceneDepthPriorityGroup::SDPG_Foreground,
                10.f);
            FVector TaskLocation = Owner->GetActorLocation();
            float length = 0;
            FVector Direction;
            (TaskLocation - LocalToWorld.GetOrigin()).ToDirectionAndLength(Direction,length);
            FVector X= Direction.GetSafeNormal();
            FVector Z = FVector(0, 0, 1);
            FVector Y=UKismetMathLibrary::Cross_VectorVector(X, Z);
            FMatrix ArrowMatrix = FMatrix(X, Y, Z, LocalToWorld.GetOrigin());
            DrawDirectionalArrow(Collector.GetPDI(0), ArrowMatrix, FLinearColor::Black, length, 10.f, ESceneDepthPriorityGroup::SDPG_World, 10.f);
        }
        virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View)const override
        {
            const bool bProxyVisible = true;

            // Should we draw this because collision drawing is enabled, and we have collision
            const bool bShowForCollision = View->Family->EngineShowFlags.Collision && IsCollisionEnabled();

            FPrimitiveViewRelevance Result;
            Result.bDrawRelevance = (IsShown(View) && bProxyVisible) || bShowForCollision;
            Result.bDynamicRelevance = true;
            Result.bShadowRelevance = IsShadowCast(View);
            Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
            return Result;
        }
        virtual uint32 GetMemoryFootprint(void) const override { return(sizeof(*this) + GetAllocatedSize()); }
        uint32 GetAllocatedSize(void) const { return(FPrimitiveSceneProxy::GetAllocatedSize()); }

    private:
        const float	LineThickness;
        const FColor	LineColor;
        AActor* Owner;
    };
    return new FDrawTaskSceneProxy(this);
}
