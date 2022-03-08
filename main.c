#include <SDL2/SDL.h>

#define LARGEUR_TILE 49
#define HAUTEUR_TILE 49

#define MAP_LARGEUR 21
#define MAP_HAUTEUR 17

typedef struct
{
    int x;
    int y;
}Pacman;

char* table[] = {
                    "111111111111111111111",
                    "100000000000000000001",
                    "111111111111111110101",
                    "100000000000000010101",
                    "101110101111101110101",
                    "101010101000100000101",
                    "101010101010111111101",
                    "101010101110000000001",
                    "100010100000111111101",
                    "111010110111100000101",
                    "100010010001101111101",
                    "101010010100001010001",
                    "101110110111111011101",
                    "101010000100000000101",
                    "101011111101111110111",
                    "100000000001000000002",
                    "111111111111111111111"
                 };

char* tab[MAP_HAUTEUR][MAP_LARGEUR];

int direction = 0;

//--------------------//

void Afficher(SDL_Window* window, SDL_Surface* screen, SDL_Surface* tileset, SDL_Surface* tile_P, int direction)
{
	SDL_Rect Rect_dest;     // surface de destination
	SDL_Rect Rect_source;   // texture source

	Rect_source.w = LARGEUR_TILE;
	Rect_source.h = HAUTEUR_TILE;

	for(int i = 0; i < MAP_LARGEUR; i++)
	{
		for(int j = 0; j < MAP_HAUTEUR; j++)
		{
            Rect_dest.x = i*LARGEUR_TILE;       // valeur x du rectangle de la surface de la fenetre qui vas etre modifier, i = la position 'x' sur la fenetre | LARGEUR_TILE = la largeur de la surface concerner
            Rect_dest.y = j*HAUTEUR_TILE;       // valeur y du rectangle de la surface de la fenetre qui vas etre modifier, y = la position 'y' sur la fenetre | HAUTEUR_TILE = la hauteur de la surface concerner

            if (tab[j][i] == 'P'){
                Rect_source.x = direction*LARGEUR_TILE;     // valeur x du rectangle de la surface du fichier bmp, table[j][i] = la position 'x' du rectangle sur l'image | LARGEUR_TILE = la largeur de la texture
                Rect_source.y = 0;
                SDL_BlitSurface(tile_P,&Rect_source,screen,&Rect_dest);
			}
			else{
                Rect_source.x = (table[j][i]-'0')*LARGEUR_TILE;     // valeur x du rectangle de la surface du fichier bmp, table[j][i] = la position 'x' du rectangle sur l'image | LARGEUR_TILE = la largeur de la texture
                Rect_source.y = 0;
                SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest);
			}
		}
	}
	SDL_UpdateWindowSurface(window);
}

//--------------------------------------------------//

int main(int argc,char** argv)
{
    SDL_Window* window;                         // The window we'll be rendering to
    SDL_Surface* screen,*tileset, *tile_P;      // The surface contained by the window

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);		// prepare SDL

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
//        printf ("SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }
    else{
        window = SDL_CreateWindow ( "SDL Tutorial",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        LARGEUR_TILE * MAP_LARGEUR,
                                        LARGEUR_TILE * MAP_HAUTEUR,
                                        SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
//            printf ("SDL_Error: %s\n", SDL_GetError());
            SDL_Quit();
            exit(-1);
        }
        else{
            screen  = SDL_GetWindowSurface(window);

            tileset = SDL_LoadBMP("Tile.bmp");
            tile_P  = SDL_LoadBMP("PACMAN.bmp");
            if (!tileset)
            {
                printf("Echec de chargement tileset.bmp\n");
                SDL_Quit();
                exit(-1);
            }
            if (!tile_P)
            {
                printf("Echec de chargement tile_P.bmp\n");
                SDL_Quit();
                exit(-1);
            }
        }
    }

    printf("Bienvenue dans le labyrinthe de Sophia ! \n");

	Pacman Player;
	Player.x = 1;
	Player.y = 1;

	tab[Player.y][Player.x] = 'P';

//--------------------//

    do{
		SDL_WaitEvent(&event);

        Afficher(window, screen, tileset, tile_P, direction);

        if (event.type == SDL_KEYDOWN){
            int x = Player.x, y = Player.y;
            switch(event.key.keysym.sym){
                    case SDLK_UP:    direction = 1;
                                     tab[Player.y][Player.x] = 0;
                                     Player.y--; break;

                    case SDLK_DOWN:  direction = 2;
                                     tab[Player.y][Player.x] = 0;
                                     Player.y++; break;

                    case SDLK_LEFT:  direction = 3;
                                     tab[Player.y][Player.x] = 0;
                                     Player.x--; break;

                    case SDLK_RIGHT: direction = 0;
                                     tab[Player.y][Player.x] = 0;
                                     Player.x++; break;

                    case SDLK_ESCAPE: event.type = SDL_QUIT; break;
            }
            if(table[Player.y][Player.x] == '1'){
                Player.x = x; Player.y = y;
            }
            tab[Player.y][Player.x] = 'P';
        }
        if (table[Player.y][Player.x] == '2'){
            printf("\nBravo ! Vous etes sortis du labyrinthe ! \n");
            Afficher(window, screen, tileset, tile_P, direction);
            SDL_Delay(2000);
            event.type = SDL_QUIT;
        }
    } while(event.type != SDL_QUIT);

	SDL_FreeSurface(tileset);
	SDL_FreeSurface(tile_P);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
