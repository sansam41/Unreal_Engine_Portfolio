// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();
	m_StartButton= Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	m_QuitButton= Cast<UButton>(GetWidgetFromName(TEXT("QuitButtton")));

	m_StartButton->OnClicked.AddDynamic(this,&UStartWidget::StartButton);
	m_QuitButton->OnClicked.AddDynamic(this,&UStartWidget::QuitButton);

	m_StartButton->OnHovered.AddDynamic(this,&UStartWidget::StartButtonHovered);
	m_QuitButton->OnHovered.AddDynamic(this,&UStartWidget::QuitButtonHovered);
	BindingAnimations();
}
void UStartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStartWidget::BindingAnimations()
{
	UProperty* Prop = GetClass()->PropertyLink;

	while(Prop!=nullptr)
	{
		if(Prop->GetClass()==UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjProp=Cast<UObjectProperty>(Prop);

			if(ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Obj=ObjProp->GetObjectPropertyValue_InContainer(this);

				UWidgetAnimation* Anim=Cast<UWidgetAnimation>(Obj);

				if(Anim!=nullptr)
				{
					if(Anim->MovieScene->GetFName()=="StartButtonMouseOn")
						m_StartButtonMouseOn=Anim;
				}
			}
		}

		Prop = Prop->PropertyLinkNext;
	}
	
}

void UStartWidget::StartButton()
{
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("CharacterSelect"));
}

void UStartWidget::QuitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit,true);
}
void UStartWidget::StartButtonHovered()
{

	PlayAnimation(m_StartButtonMouseOn);
}

void UStartWidget::QuitButtonHovered()
{

}