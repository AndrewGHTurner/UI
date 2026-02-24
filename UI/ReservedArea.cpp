#include "pch.h"
#include "UI_DLL_Interface.h"

#include "InteractiveFluent.h"
#include "ReservedArea.h"

internal::ReservedArea::ReservedArea() 
{

};




ReservedAreaPtr ReservedArea()
{
	return make_unique<internal::ReservedArea>();
}

