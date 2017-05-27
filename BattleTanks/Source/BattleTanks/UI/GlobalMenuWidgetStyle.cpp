// Copyright MB

#include "BattleTanks.h"
#include "GlobalMenuWidgetStyle.h"

void FGlobalStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
}

const FName FGlobalStyle::TypeName = TEXT("FGlobalStyle");

const FName FGlobalStyle::GetTypeName() const
{
	static const FName typeName = TEXT("FGlobalStyle");
	return typeName;
}

const FGlobalStyle& FGlobalStyle::GetDefault()
{
	static FGlobalStyle Default;
	return Default;
}

UGlobalMenuWidgetStyle::UGlobalMenuWidgetStyle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
