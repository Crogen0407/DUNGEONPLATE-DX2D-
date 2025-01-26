#include "pch.h"
#include "UI.h"
#include "Canvas.h"
#include "Slider.h"
#include "Button.h"
#include "Picture.h"
#include "Text.h"

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::LateUpdate()
{
	for (auto& child : children)
		child->LateUpdate();
}

void Canvas::Render(std::shared_ptr<Pipeline> pipeline)
{
	Object::Render(pipeline);
	for (auto& child : children)
	{
		if(child->GetActive())
			child->Render(pipeline);
	}
}