// Copyright MB

#pragma once


#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class BATTLETANKS_API SPlayersHUDUI : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPlayersHUDUI)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
