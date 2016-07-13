#include "App.h"
#include <typeinfo>
#include "stdincl.h"
#include "Scene.h"
#include "ObjectHelpers.h"
#include "Helpers.h"
#include "ComponentCreator.h"
#include "ComponentFactory.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "Object.h"


int main()
{
	FreeConsole();
	App::App();
	g_app->Run();
}