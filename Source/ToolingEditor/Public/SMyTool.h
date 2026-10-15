// compound widget
#include "Widgets/SCompoundWidget.h"

class SMyTool : public SCompoundWidget {

	// It is neccessaryto define arguments of the widget even if is empty
	SLATE_BEGIN_ARGS(SMyTool){}
	SLATE_END_ARGS()

	// Constructor
	void Construct(const FArguments& InArgs);

private:
	FReply OnButtonClicked();
	FString StatusText = TEXT("Ready");
	int32 ClickCounter = 0;
	int32 Number = 0;
};