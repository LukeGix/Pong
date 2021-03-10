#include "Game.h"
int main(int argc, char* argv[]){
	Game g;

	if(g.Initialize()){
		g.Loop();
	}

	g.Shutdown();

	return 0;
}