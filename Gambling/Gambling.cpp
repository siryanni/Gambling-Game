// Einbinden der benötigten SDL-Bibliotheken und Standardbibliotheken
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>	
#include <string>
#include "Header.h"  // Wahrscheinlich eigene Funktionen oder Definitionen

using namespace std;

int main(int argc, char* argv[])
{
	// Startguthaben ("bilanz") und Einsatzhöhe ("einsatz") setzen
	int bilanz = 100;
	int einsatz = 10;

	SDL_Event event; // Ereignis-Objekt für Benutzereingaben (z.B. Mausklicks)

	// SDL-Subsysteme initialisieren (Grafik, Fenster usw.)
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init(); // TrueType-Fonts initialisieren

	// Fenster erstellen (Größe: 1000x1000 Pixel)
	SDL_Window* window = SDL_CreateWindow("Bamble.cc", 1000, 1000, 0);

	// Renderer erzeugen (für das Zeichnen auf dem Fenster)
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);

	// Hintergrundbild laden
	SDL_Surface* backgroundSurface = IMG_Load("background.png");
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);

	// Farben definieren (weiß und schwarz)
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color black = { 0, 0, 0, 255 };

	// Schriftart laden (mit Größe 50)
	TTF_Font* font = TTF_OpenFont("MonospaceBold.ttf", 50);

	// Textgrafik für "Bilanz" erzeugen und als Texture speichern
	SDL_Surface* bilanzsurface = TTF_RenderText_Solid(font, to_string(bilanz).c_str(), to_string(bilanz).length(), black);
	SDL_Texture* bilanzTexture = SDL_CreateTextureFromSurface(renderer, bilanzsurface);

	// Gleiches für den "Einsatz"
	SDL_Surface* einsatzSurface = TTF_RenderText_Solid(font, to_string(einsatz).c_str(), to_string(einsatz).length(), black);
	SDL_Texture* einsatzTexture = SDL_CreateTextureFromSurface(renderer, einsatzSurface);

	// Rechtecke für die Anzeige von Bilanz und Einsatz (Position + Größe)
	SDL_FRect bilanzRect = { 21, 227, bilanzsurface->w, bilanzsurface->h };
	SDL_FRect einsatzRect = { 21, 369, einsatzSurface->w, einsatzSurface->h };

	// Hintergrund und Texturen zum ersten Mal anzeigen
	SDL_RenderTexture(renderer, backgroundTexture, 0, NULL);
	SDL_RenderTexture(renderer, bilanzTexture, NULL, &bilanzRect);
	SDL_RenderTexture(renderer, einsatzTexture, NULL, &einsatzRect);
	SDL_RenderPresent(renderer); // Alles auf dem Bildschirm anzeigen

	// Haupt-Eventloop (läuft unendlich weiter)
	while (true) {
		if(bilanz<= 0) // Wenn Bilanz 0 oder weniger ist, Spiel beenden
		{
			cout << "Game Over! Your balance is zero." << endl;
			break; // Beenden der Schleife
		}
		while (SDL_PollEvent(&event)) // Eingabeereignisse prüfen
		{
			// Wenn die Maus geklickt wurde
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				// Klick auf den "Einsatz erhöhen"-Button (bestimmter Bereich)
				if (event.button.x > 280 && event.button.x < 350 &&
					event.button.y > 350 && event.button.y < 385 &&
					einsatz <= bilanz - 10)
				{
					einsatz += 10; // Einsatz erhöhen (nur wenn genug Bilanz da ist)
				}

				// Klick auf den "Einsatz verringern"-Button
				if (event.button.x > 280 && event.button.x < 350 &&
					event.button.y > 385 && event.button.y < 415 &&
					einsatz >= 20)
				{
					einsatz -= 10; // Einsatz senken
				}

				// Position des Mausklicks in der Konsole ausgeben (Debug)
				cout << "x: " << event.button.x << " y: " << event.button.y << endl;

				// Klick auf den "Spielen"-Button
				if (event.button.x > 731 && event.button.x < 844 &&
					event.button.y > 747 && event.button.y < 859)
				{
					// 25% Gewinnchance (wenn Zufallswert 0 von 0–3)
					if (random(0, 4) == 0)
					{
						bilanz += einsatz * 4; // Gewinn: 4x Einsatz
					}
					else
					{
						bilanz -= einsatz; // Verlust: Einsatz abziehen
					}
				}

				// Texturen für neuen Bilanz- und Einsatz-Wert erzeugen
				SDL_Surface* bilanzsurface = TTF_RenderText_Solid(font, to_string(bilanz).c_str(), to_string(bilanz).length(), black);
				SDL_Texture* bilanzTexture = SDL_CreateTextureFromSurface(renderer, bilanzsurface);

				SDL_Surface* einsatzSurface = TTF_RenderText_Solid(font, to_string(einsatz).c_str(), to_string(einsatz).length(), black);
				SDL_Texture* einsatzTexture = SDL_CreateTextureFromSurface(renderer, einsatzSurface);

				// Alles neu zeichnen (Hintergrund, Texte, Anzeige)
				SDL_RenderTexture(renderer, backgroundTexture, 0, NULL);
				SDL_RenderTexture(renderer, bilanzTexture, NULL, &bilanzRect);
				SDL_RenderTexture(renderer, einsatzTexture, NULL, &einsatzRect);
				SDL_RenderPresent(renderer); // Bildschirm aktualisieren
			}
		}
	}

	return 0; // (wird nie erreicht, weil while(true) unendlich läuft)
}
