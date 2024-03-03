#include "Sandbox.h"

int main() {
	Barta::Application* app = new Sandbox();
	app->run();
	delete app;

    return 0;
}