// Copyright MB

#pragma once


#include "Styling/SlateWidgetStyle.h"
#include "SlateBasics.h"
#include "SlateWidgetStyleContainerBase.h"
#include "GlobalMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct BATTLETANKS_API FGlobalStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	//FGlobalStyle();
	//virtual ~FGlobalStyle();

	// Stores a list of Brushes we are using (we aren't using any) into OutBrushes.
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	// Stores the TypeName for our widget style.
	static const FName TypeName;

	// Retrieves the type name for our global style, which will be used by our Style Set to load the right file. 
	virtual const FName GetTypeName() const override;

	// Allows us to set default values for our various styles. 
	static const FGlobalStyle& GetDefault();

	// Style that define the appearance of all menu buttons. 
	UPROPERTY(EditAnywhere, Category = Appearance)
	FButtonStyle MenuButtonStyle;

	// Style that defines the text on all of our menu buttons. 
	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle MenuButtonTextStyle;

	// Style that defines the text for our menu title. 
	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle MenuTitleStyle;

	// Style that defines the text for our players HUD
	FTextBlockStyle PlayersHUDStyle;

	/* Brush used to draw the menu background. */
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush BackgroundBrush;
	FGlobalStyle& SetBackgroundBrush(const FSlateBrush& InBackgroundBrush) { BackgroundBrush = InBackgroundBrush; return *this; }

	/**
	* The brush used to draw the menu tile background
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush TileBackgroundBrush;
	FGlobalStyle& SetTileBackgroundBrush(const FSlateBrush& InTileBackgroundBrush) { TileBackgroundBrush = InTileBackgroundBrush; return *this; }

	/**
	* The brush used to draw the pop-up menu background
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush PopupBackgroundBrush;
	FGlobalStyle& SetPopupBackgroundBrush(const FSlateBrush& InPopupBackgroundBrush) { PopupBackgroundBrush = InPopupBackgroundBrush; return *this; }

	/**
	* The brush used to draw the top menu decoration
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush TopDecoration;
	FGlobalStyle& SetTopDecoration(const FSlateBrush& InTopDecoration) { TopDecoration = InTopDecoration; return *this; }

	/**
	* The brush used to draw the left menu decoration
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush LeftDecoration;
	FGlobalStyle& SetLeftDecoration(const FSlateBrush& InLeftDecoration) { LeftDecoration = InLeftDecoration; return *this; }

	/**
	* The brush used to draw the right menu decoration
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush RightDecoration;
	FGlobalStyle& SetRightDecoration(const FSlateBrush& InRightDecoration) { RightDecoration = InRightDecoration; return *this; }

	/**
	* The sound that should play when entering a sub-menu
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound MenuEnterSound;
	FGlobalStyle& SetMenuEnterSound(const FSlateSound& InMenuEnterSound) { MenuEnterSound = InMenuEnterSound; return *this; }

	/**
	* The sound that should play when leaving a sub- menu
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound MenuExitSound;
	FGlobalStyle& SetMenuExitSound(const FSlateSound& InMenuExitSound) { MenuExitSound = InMenuExitSound; return *this; }

	/**
	* The brush used to draw the resources area background
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush ResourcesBackgroundBrush;
	FGlobalStyle& SetResourcesBackgroundBrush(const FSlateBrush& InResourcesBackgroundBrush) { ResourcesBackgroundBrush = InResourcesBackgroundBrush; return *this; }

	/**
	* The brush used to draw the resources image
	*/
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush ResourcesImage;
	FGlobalStyle& SetResourcesImage(const FSlateBrush& InResourcesImage) { ResourcesImage = InResourcesImage; return *this; }

	/**
	* The sound that should play when starting the game
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound StartGameSound;
	FGlobalStyle& SetStartGameSound(const FSlateSound& InStartGameSound) { StartGameSound = InStartGameSound; return *this; }

	/**
	* The sound that should play when exiting the game
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound ExitGameSound;
	FGlobalStyle& SetExitGameSound(const FSlateSound& InExitGameSound) { ExitGameSound = InExitGameSound; return *this; }

	/**
	* The sound that should play when changing the selected menu item
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound MenuItemChangeSound;
	FGlobalStyle& SetMenuItemChangeSound(const FSlateSound& InMenuItemChangeSound) { MenuItemChangeSound = InMenuItemChangeSound; return *this; }

	///**
	//* The brush used to draw the frame around the mini-map
	//*/
	//UPROPERTY(EditAnywhere, Category = Appearance)
	//FSlateBrush MinimapFrameBrush;
	//FGlobalStyle& SetMinimapFrameBrush(const FSlateBrush& InMinimapFrameBrush) { MinimapFrameBrush = InMinimapFrameBrush; return *this; }

	///**
	//* The brush used to draw the victory image
	//*/
	//UPROPERTY(EditAnywhere, Category = Appearance)
	//FSlateBrush VictoryImage;
	//FGlobalStyle& SetVictoryImage(const FSlateBrush& InVictoryImage) { VictoryImage = InVictoryImage; return *this; }

	///**
	//* The brush used to draw the defeat image
	//*/
	//UPROPERTY(EditAnywhere, Category = Appearance)
	//FSlateBrush DefeatImage;
	//FGlobalStyle& SetDefeatImage(const FSlateBrush& InDefeatImage) { DefeatImage = InDefeatImage; return *this; }

	///**
	//* The color used to draw the victory text
	//*/
	//UPROPERTY(EditAnywhere, Category = Appearance)
	//FSlateColor VictoryTextColor;
	//FGlobalStyle& SetVictoryTextColor(const FSlateColor& InVictoryTextColor) { VictoryTextColor = InVictoryTextColor; return *this; }

	///**
	//* The color used to draw the defeat text
	//*/
	//UPROPERTY(EditAnywhere, Category = Appearance)
	//FSlateColor DefeatTextColor;
	//FGlobalStyle& SetDefeatTextColor(const FSlateColor& InDefeatTextColor) { DefeatTextColor = InDefeatTextColor; return *this; }
};


/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UGlobalMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

	UGlobalMenuWidgetStyle(const FObjectInitializer &);

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FGlobalStyle MenuStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &MenuStyle );
	}
};
