// Copyright MB

#include "BattleTanks.h"
#include "GlobalMenuWidgetStyle.h"


FGlobalMenuStyle::FGlobalMenuStyle()
{
}

FGlobalMenuStyle::~FGlobalMenuStyle()
{
}

const FName FGlobalMenuStyle::TypeName(TEXT("FGlobalMenuStyle"));

const FGlobalMenuStyle& FGlobalMenuStyle::GetDefault()
{
	static FGlobalMenuStyle Default;
	return Default;
}

void FGlobalMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

