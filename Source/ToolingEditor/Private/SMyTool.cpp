#include "SMyTool.h"

void SMyTool::Construct(const FArguments& InArgs) {
	// A compound widget is full of childs
	ChildSlot[
		SNew(SVerticalBox) // this is a child widget
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10.f)
			[
				SNew(STextBlock) // this a leaf widget; a leaf widget is a widget that doesn't have childs
					.Text(FText::FromString("My Slate Tool"))
					.Font(FCoreStyle::GetDefaultFontStyle("Bold", 14))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10.f)
			[
				// using lambda to retrieve attribute StatusText
				SNew(STextBlock).Text_Lambda(
					[this]()
					{
						return FText::FromString(StatusText);
					})
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10.f)
			[
				SNew(SButton)
				.Text(FText::FromString("Click me"))
				.OnClicked(this, &SMyTool::OnButtonClicked) // callback
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10.f)
			[
				SNew(STextBlock).Text_Lambda(
					[this]()
					{
						return FText::Format(
							FText::FromString("Clicked {0} times")
							, FText::AsNumber(ClickCounter));
					})
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(10.f)
				[
					SNew(STextBlock).Text_Lambda(
						[this]()
						{
							return FText::Format(
								FText::FromString("Clicked {0} times")
								, FText::AsNumber(Number));
						})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(10.f)
				[
					SNew(SButton)
					.Text(FText::FromString("Number +"))
					.OnClicked_Lambda(
						[this]()
						{
							Number++;
							return FReply::Handled();
						})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(10.f)
				[
					SNew(SButton)
					.Text(FText::FromString("Number -"))
					.OnClicked_Lambda(
					[this]() 
					{
						Number--;
						return FReply::Handled(); 
					})
				]
			]
	];
}

FReply SMyTool::OnButtonClicked() {
	StatusText = "Button clicked";
	++ClickCounter;
	return FReply::Handled();
}