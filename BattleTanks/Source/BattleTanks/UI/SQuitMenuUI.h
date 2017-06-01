// Copyright MB

#pragma once


#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class BATTLETANKS_API SQuitMenuUI : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SQuitMenuUI)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
