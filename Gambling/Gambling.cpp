// Include the necessary SDL libraries and standard libraries
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>	
#include <string>
#include "Header.h"  // Probably contains custom functions or definitions

using namespace std;

int main(int argc, char* argv[])
{
	// Set starting balance ("bilanz") and bet amount ("einsatz")
	int bilanz = 100;
	int einsatz = 10;

	SDL_Event event; // Event object for user input (e.g., mouse clicks)

	// Initialize SDL subsystems (graphics, window, etc.)
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init(); // Initialize TrueType fonts

	// Create window (size: 1000x1000 pixels)
	SDL_Window* window = SDL_CreateWindow("Bamble.cc", 1000, 1000, 0);

	// Create renderer (for drawing on the window)
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);

	// Load background image
	SDL_Surface* backgroundSurface = IMG_Load("background.png");
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);

	// Define colors (white and black)
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color black = { 0, 0, 0, 255 };

	// Load font (size 50)
	TTF_Font* font = TTF_OpenFont("MonospaceBold.ttf", 50);

	// Create text graphic for "Bilanz" and store it as a texture
	SDL_Surface* bilanzsurface = TTF_RenderText_Solid(font, to_string(bilanz).c_str(), to_string(bilanz).length(), black);
	SDL_Texture* bilanzTexture = SDL_CreateTextureFromSurface(renderer, bilanzsurface);

	// Same for "Einsatz"
	SDL_Surface* einsatzSurface = TTF_RenderText_Solid(font, to_string(einsatz).c_str(), to_string(einsatz).length(), black);
	SDL_Texture* einsatzTexture = SDL_CreateTextureFromSurface(renderer, einsatzSurface);

	// Rectangles for displaying balance and bet (position + size)
	SDL_FRect bilanzRect = { 21, 227, bilanzsurface->w, bilanzsurface->h };
	SDL_FRect einsatzRect = { 21, 369, einsatzSurface->w, einsatzSurface->h };

	// Display background and textures for the first time
	SDL_RenderTexture(renderer, backgroundTexture, 0, NULL);
	SDL_RenderTexture(renderer, bilanzTexture, NULL, &bilanzRect);
	SDL_RenderTexture(renderer, einsatzTexture, NULL, &einsatzRect);
	SDL_RenderPresent(renderer); // Show everything on screen

	// Main event loop (runs infinitely)
	while (true) {
		if (bilanz <= 0) // If balance is zero or less, end game
		{
			cout << "Game Over! Your balance is zero." << endl;
			break; // Exit the loop
		}
		while (SDL_PollEvent(&event)) // Check for input events
		{
			// If the mouse was clicked
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				// Click on "increase bet" button (specific area)
				if (event.button.x > 280 && event.button.x < 350 &&
					event.button.y > 350 && event.button.y < 385 &&
					einsatz <= bilanz - 10)
				{
					einsatz += 10; // Increase bet (only if enough balance)
				}

				// Click on "decrease bet" button
				if (event.button.x > 280 && event.button.x < 350 &&
					event.button.y > 385 && event.button.y < 415 &&
					einsatz >= 20)
				{
					einsatz -= 10; // Decrease bet
				}

				// Output position of mouse click to console (for debugging)
				cout << "x: " << event.button.x << " y: " << event.button.y << endl;

				// Click on "Play" button
				if (event.button.x > 731 && event.button.x < 844 &&
					event.button.y > 747 && event.button.y < 859)
				{
					// 25% chance to win (if random value is 0 out of 0–3)
					if (random(0, 4) == 0)
					{
						bilanz += einsatz * 4; // Win: 4x the bet
					}
					else
					{
						bilanz -= einsatz; // Loss: subtract the bet
					}
				}

				// Create new textures for updated balance and bet
				SDL_Surface* bilanzsurface = TTF_RenderText_Solid(font, to_string(bilanz).c_str(), to_string(bilanz).length(), black);
				SDL_Texture* bilanzTexture = SDL_CreateTextureFromSurface(renderer, bilanzsurface);

				SDL_Surface* einsatzSurface = TTF_RenderText_Solid(font, to_string(einsatz).c_str(), to_string(einsatz).length(), black);
				SDL_Texture* einsatzTexture = SDL_CreateTextureFromSurface(renderer, einsatzSurface);

				// Redraw everything (background, texts, display)
				SDL_RenderTexture(renderer, backgroundTexture, 0, NULL);
				SDL_RenderTexture(renderer, bilanzTexture, NULL, &bilanzRect);
				SDL_RenderTexture(renderer, einsatzTexture, NULL, &einsatzRect);
				SDL_RenderPresent(renderer); // Update screen
			}
		}
	}

	return 0; // (never reached because while(true) runs indefinitely)
}
