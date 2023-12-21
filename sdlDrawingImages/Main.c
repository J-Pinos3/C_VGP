#include "SDL.H"
#include "SDL_image.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef struct {
	int x, y;
	short life;
	char* name;
} Man;

typedef struct {
	int x, y;
} Star;

typedef struct {
	//PLAYERS
	Man man;
	
	Star stars[100];

	//IMAGES
	SDL_Texture* star;
	SDL_Renderer* renderer;
} GameState;


void loadGame(GameState* game) {
	SDL_Surface* starSurface = NULL;

	starSurface = IMG_Load("star1.png");
	if (starSurface == NULL) {
		printf("Cannot find star1.png");
		SDL_Quit();
		exit(1);
	}
	game->star = SDL_CreateTextureFromSurface(game->renderer, starSurface);
	SDL_FreeSurface(starSurface);

	game->man.x = 320 - 40;
	game->man.y = 240 - 40;

	//initialize stars
	for (int i = 0; i < 100; i++) {
		game->stars[i].x = rand() % 640;//numbers bwtween 0 and (width|height)exclusive
		game->stars[i].y = rand() % 480;
	}
}


int processEvents(SDL_Window* window, GameState* game) {

	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT_CLOSE: {
			if (window) {
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
		}
		break;

		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = 1;
				break;

				//case SDLK_RIGHT: { man->x += 10; } break;
				//case SDLK_LEFT: { man->x -= 10; } break;
			}
		}
		break;

		case SDL_QUIT:
			done = 1;
			break;

		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT]) {
		game->man.x -= 10;
	}

	if (state[SDL_SCANCODE_RIGHT]) {
		(*game).man.x += 10;
	}

	if (state[SDL_SCANCODE_UP]) {
		game->man.y -= 10;
	}

	if (state[SDL_SCANCODE_DOWN]) {
		game->man.y += 10;
	}

	return done;
}


void doRender(SDL_Renderer* renderer, GameState* game) {
	//render display
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect = { (*game).man.x , game->man.y, 80, 80 };
	SDL_RenderFillRect(renderer, &rect);

	for (int i = 0; i < 100; i++) {
		//draw star image
		SDL_Rect starRect = { game->stars[i].x, game->stars[i].y,68,68};
		SDL_RenderCopy(renderer, game->star, NULL, &starRect);
	}


	//here im drawing 2 things, the 1st one is the white rectangle
	//and given that is the first thing breing drawn
	//the white rectangle will be behind the star

	SDL_RenderPresent(renderer);

}


int main(int argc, char* args[]) {

	GameState gameState;


	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	


	SDL_Init(SDL_INIT_VIDEO);
	srand((int) time(NULL));

	window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	gameState.renderer = renderer;

	loadGame(&gameState);
	
	int done = 0;

	while (!done) {

		done = processEvents(window, &gameState);

		doRender(renderer, &gameState);

		//SDL_Delay(50);
	}


	SDL_DestroyTexture(gameState.star);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
	return 0;
}