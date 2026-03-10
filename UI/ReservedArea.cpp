#include "pch.h"
#include "UI_DLL_Interface.h"

#include "InteractiveFluent.h"
#include "ReservedArea.h"

internal::ReservedArea::ReservedArea() 
{
	setBackgroundColour(Color(255,255, 255, 0));
};




ReservedAreaPtr ReservedArea()
{
	return make_unique<internal::ReservedArea>();
}

