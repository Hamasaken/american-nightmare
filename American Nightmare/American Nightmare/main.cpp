#include "Program.h"

int main(int argc, char *argv[])
{
	// Start the application class
	Program *pgr = new Program();
	if (pgr == nullptr) return NULL;
	if (!pgr->Start()) return NULL;

	// Main Loop
	while (pgr->Run());

	// Delete everything
	pgr->Stop();

	return NULL;
}