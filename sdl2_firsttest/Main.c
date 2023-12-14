#include <stdio.h>
#include <SDL.h>

typedef struct {
	int x, y;
	short int life;
	char* name;
} Man;

void function(int x, int y, int array[], Man *man) {
	(*man).x = 110;
	man->y = 71;
	printf("x: %d\ny: %d\n\n", man->x, man->y);
}

int main(int argc, char* args[]) {

	Man man;
	man.x = 54;
	man.y = 37;
	int array[2] = {1,2};
	printf("outside 1 \nx: %d\ny: %d\n\n", man.x, man.y);
	function(0, 125, array, &man);
	printf("outside 2\nx: %d\ny: %d\n\n", man.x, man.y);
	

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);


	window = SDL_CreateWindow(
		"Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		0);

	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255,255,255,255);

	SDL_Rect rect = { 220,140,200,200 };
	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);

	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	return 0;
}