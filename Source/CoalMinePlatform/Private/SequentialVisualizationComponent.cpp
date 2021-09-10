// Fill out your copyright notice in the Description page of Project Settings.


#include "SequentialVisualizationComponent.h"
#include "CoalMineCompositionTask.h"

USequentialVisualizationComponent::USequentialVisualizationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bHiddenInGame = true;
	bCastDynamicShadow = false;

	LineThickness = 3.2f;
	LineColor = FColor::Cyan;
}

void USequentialVisualizationComponent::BeginPlay()
{
    Super::BeginPlay();
}

FPrimitiveSceneProxy* USequentialVisualizationComponent::CreateSceneProxy()
{
	class FDrawTaskSceneProxy :public FPrimitiveSceneProxy
	{
	public:

		SIZE_T GetTypeHash() const override
		{
			static size_t UniquePointer;
			return reinterpret_cast<size_t>(&UniquePointer);
		}

		FDrawTaskSceneProxy(const USequentialVisualizationComponent* InComponent)
			: FPrimitiveSceneProxy(InComponent)
			, LineThickness(InComponent->LineThickness)
			, LineColor(InComponent->LineColor)
			, ChildTasks(InComponent->GetOwnerSubTasks())
		{
			bWillEverBeLit = false;
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

					FVector StartLoc = LocalToWorld.GetOrigin();

					for (ACoalMineTaskBase* ChildTask : ChildTasks)
					{
						if (ChildTask && ChildTask->IsValidLowLevel())
						{
							FVector ChildTaskLoc = ChildTask->GetActorLocation();
							const FVector XAxis = (ChildTaskLoc - StartLoc).GetSafeNormal();
							const FVector ZAxis(0, 0, 1);
							const FVector YAxis = -FVector::CrossProduct(XAxis, ZAxis);

							FMatrix ArrowMatrix = FMatrix(XAxis, YAxis, ZAxis, StartLoc);
							DrawDirectionalArrow(PDI, ArrowMatrix, LineColor, (StartLoc - ChildTaskLoc).Size(), 16, SDPG_World, LineThickness);

							StartLoc = ChildTaskLoc;
						}
					}
				}
			}
		}

		virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
		{
			//const bool bProxyVisible = !bDrawOnlyIfSelected || IsSelected();
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
		const TArray<ACoalMineTaskBase*> ChildTasks;
	};
	return new FDrawTaskSceneProxy(this);
}

FBoxSphereBounds USequentialVisualizationComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	TArray<ACoalMineTaskBase*>ChildTasks = GetOwnerSubTasks();
	FVector CenterPoint = GetComponentLocation();
	for (ACoalMineTaskBase* ChildTask : ChildTasks)
	{
		if (ChildTask)
		{
			CenterPoint = (CenterPoint + ChildTask->GetActorLocation()) / 2;
		}
	}
	float FarestDist = (CenterPoint - GetComponentLocation()).Size();
	for (ACoalMineTaskBase* ChildTask : ChildTasks)
	{
		if (ChildTask)
		{
			float Dist = (CenterPoint - ChildTask->GetActorLocation()).Size();
			if (Dist > FarestDist)
			{
				FarestDist = Dist;
			}
		}
	}
	FarestDist = FarestDist * 1.6f;

	return FBoxSphereBounds(CenterPoint, FVector(FarestDist, FarestDist, FarestDist), FarestDist);
}

TArray<ACoalMineTaskBase*> USequentialVisualizationComponent::GetOwnerSubTasks() const
{
	TArray<ACoalMineTaskBase*>Tasks;
	ACoalMineCompositionTask* SequentialTask = Cast<ACoalMineCompositionTask>(GetOwner());
	if (SequentialTask)
	{
		Tasks = SequentialTask->SubTasks;
	}
    return Tasks;
}
