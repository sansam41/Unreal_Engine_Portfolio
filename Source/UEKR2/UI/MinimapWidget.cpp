// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UMinimapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_PlayerArrow = Cast<UImage>(GetWidgetFromName(TEXT("PlayerArrow")));

	CreateMonsterArray();
}

void UMinimapWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMinimapWidget::CreateMonsterArray()
{
	m_AddCount = 0;

	UCanvasPanel* Panel = WidgetTree->FindWidget<UCanvasPanel>(TEXT("MonsterParent"));

	for (int32 i = 0; i < 20; ++i)
	{
		FString	Name = FString::Printf(TEXT("Monster%d"), i);

		UImage* Image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(),
			*Name);

		Image->SetVisibility(ESlateVisibility::Collapsed);
		FSlateColor Color = FColor::Red;
		Image->SetBrushTintColor(Color);

		m_MonsterArray.Add(Image);

		if (Panel)
		{
			UCanvasPanelSlot* PanelSlot = Panel->AddChildToCanvas(Image);

			PanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			PanelSlot->SetSize(FVector2D(10.f, 10.f));
		}
	}
}

void UMinimapWidget::RotationArrow(float Yaw)
{
	m_PlayerArrow->SetRenderTransformAngle(Yaw);
}

void UMinimapWidget::AddMonster(const FVector& Pos)
{
	if (m_AddCount == m_MonsterArray.Num())
	{
		UCanvasPanel* Panel = WidgetTree->FindWidget<UCanvasPanel>(TEXT("MonsterParent"));

		FString	Name = FString::Printf(TEXT("Monster%d"), m_AddCount);

		UImage* Image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(),
			*Name);
		Image->SetVisibility(ESlateVisibility::Collapsed);

		m_MonsterArray.Add(Image);

		if (Panel)
		{
			UCanvasPanelSlot* PanelSlot = Panel->AddChildToCanvas(Image);

			PanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			PanelSlot->SetSize(FVector2D(10.f, 10.f));
		}
	}

	//PrintViewport(1.f, FColor::Red, Pos.ToString());
	m_MonsterArray[m_AddCount]->SetVisibility(ESlateVisibility::Visible);

	FVector2D	ImagePos;

	ImagePos.X = Pos.Y;
	ImagePos.Y = Pos.X * -1.f;
	ImagePos *= 0.1f;

	ImagePos.X += 200.f;
	ImagePos.Y += 150.f;

	//PrintViewport(1.f, FColor::Red, ImagePos.ToString());

	UImage* Image = m_MonsterArray[m_AddCount];
	++m_AddCount;

	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Image->Slot);

	PanelSlot->SetPosition(ImagePos);
}

void UMinimapWidget::ClearMonster()
{
	for (int32 i = 0; i < m_AddCount; ++i)
	{
		m_MonsterArray[i]->SetVisibility(ESlateVisibility::Collapsed);
	}

	m_AddCount = 0;
	/*UCanvasPanel* Panel = WidgetTree->FindWidget<UCanvasPanel>(TEXT("MonsterParent"));

	if (Panel)
		Panel->ClearChildren();*/
}
