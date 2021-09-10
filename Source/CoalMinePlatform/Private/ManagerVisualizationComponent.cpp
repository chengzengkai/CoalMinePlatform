// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerVisualizationComponent.h"
#include "CoalMineTaskBase.h"
#include "CoalMineTaskManager.h"


UManagerVisualizationComponent::UManagerVisualizationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bHiddenInGame = true;
    bCastDynamicShadow = false;
    LineThickness = 3.2f;
    LineColor = FColor::Blue;
}

FPrimitiveSceneProxy* UManagerVisualizationComponent::CreateSceneProxy()
{
    class FDrawTaskSceneProxy :public FPrimitiveSceneProxy
    {
    public:
        SIZE_T GetTypeHash()const override
        {
            static size_t UniquePointer;
            return reinterpret_cast<size_t>(&UniquePointer);
        }
        FDrawTaskSceneProxy(const UManagerVisualizationComponent* InComponent)
            :FPrimitiveSceneProxy(InComponent)
            , LineThickness(InComponent->LineThickness)
            , LineColor(InComponent->LineColor)
            , InitialTask(InComponent->GetOwnerInitialTask())
        {
            
        }
        virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
        {
            QUICK_SCOPE_CYCLE_COUNTER(STAT_GetDynamicMeshElements_DrawDynamicElements);

            const FMatrix& LocalToWorld = GetLocalToWorld();

            for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
            {

                if (VisibilityMap & (1 << ViewIndex))
                {
                    const FSceneView* View = Views[ViewIndex];
                    const FLinearColor DrawCapsuleColor = GetViewSelectionColor(LineColor, *View, IsSelected(), IsHovered(), false, IsIndividuallySelected());

                    FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);
                    if (InitialTask && InitialTask->IsValidLowLevel())
                    {
                        FVector InitialTaskLoc = InitialTask->GetActorLocation();
                        const FVector XAxis = (InitialTaskLoc - LocalToWorld.GetOrigin()).GetSafeNormal();
                        const FVector ZAxis(0, 0, 1);
                        const FVector YAxis = FVector::CrossProduct(XAxis, ZAxis);
                        FMatrix ArrowMatrix = FMatrix(XAxis, YAxis, ZAxis, LocalToWorld.GetOrigin());
                        DrawDirectionalArrow(PDI, ArrowMatrix, LineColor, (LocalToWorld.GetOrigin() - InitialTaskLoc).Size(), 16, SDPG_World, LineThickness);
                    }
                }
            }
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
        const ACoalMineTaskBase* InitialTask;
    };
    return new FDrawTaskSceneProxy(this);
}

FBoxSphereBounds UManagerVisualizationComponent::CalcBounds(const FTransform& LocalToWorld) const
{
    ACoalMineTaskBase* InitialTask = GetOwnerInitialTask();
    FVector CenterPoint = GetComponentLocation();
    float FarestDist = 0;
    
    if (InitialTask)
    {
    	CenterPoint = (CenterPoint + InitialTask->GetActorLocation()) / 2;
    	FarestDist = (CenterPoint - GetComponentLocation()).Size();
    
    	FarestDist = FarestDist * 1.6f;
    }
    
    return FBoxSphereBounds(CenterPoint, FVector(FarestDist, FarestDist, FarestDist), FarestDist);
}

ACoalMineTaskBase* UManagerVisualizationComponent::GetOwnerInitialTask() const
{
    ACoalMineTaskBase* InitialTask = nullptr;
    ACoalMineTaskManager* TaskManager = Cast<ACoalMineTaskManager>(GetOwner());
    if (TaskManager)
    {
        InitialTask = TaskManager->InitialTask;
    }
    return InitialTask;
}
