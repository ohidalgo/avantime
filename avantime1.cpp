#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#define v_screenw 800
#define v_screenh 600
#define v_screenc 16
#define v_botonxpos 100
#define v_botonypos 100
#define v_frames 25
#define v_spritew 100
#define v_spriteh 100

    int channel;
    Mix_Chunk *sound = NULL;
    
/* void clips() { 
     int i;
     for (i=0; 1; v_frames-1) {
       clips[ i ].x = v_spritew*i; 
       clips[ i ].y = 0; 
       clips[ i ].w = v_spritew; 
       clips[ i ].h = v_spriteh;
       };
     } 
     
class animation { 
      private: 
      int positionx; 
      int positiony;
      int velocity; 
      int frame; 
      int letra; 
      
      public: Animation(); 
      void handle_events(); 
      void move(); 
      void show();
      }
          
Foo::Foo() { 
      positionx = 0; 
      positiony = 0;
      velocity = 0; 
      frame = 0; 
      letra = 0; 
      }
      */
      
void onkeys(SDL_KeyboardEvent key) {
  switch(key.keysym.sym) {
  case SDLK_s:
       channel = Mix_PlayChannel(-1, sound, 0);
       //while(Mix_Playing(channel) != 0);
       break;
  case SDLK_a:
       break;
  case SDLK_t:
       break;
  case SDLK_c:
       break;
  }
}
      
int main(int argc, char** argv) {
     
    //* Inicializando las biblioteca SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
       printf("No se pudo inicializar SDL: %s\n", SDL_GetError());
       exit(1);
       }
       
	//Initialize SDL_mixer with our chosen audio settings
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		printf("Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}
	
    //Tratamos de entrar a modo grafico
    SDL_Surface *screen = SDL_SetVideoMode(v_screenw, v_screenh, v_screenc,SDL_HWSURFACE|SDL_RESIZABLE);
    if( screen == NULL ) {
        printf( "Error al entrar a modo grafico: %s\n", SDL_GetError() );
        SDL_Quit();
        return -1;
        }
    else SDL_WM_SetCaption( "Avantime Test", "Avantime" );  
      
    //Cargando Audio 
	sound = Mix_LoadWAV("avantime.wav");
	if(sound == NULL) {
		printf("Unable to load WAV file: %s\n", Mix_GetError());
	}
      
    //Preparamos las imagenes a mostrar
    SDL_Surface *fondo = IMG_Load("avantime_bg.jpg");
    SDL_Surface *boton = IMG_Load("avantime_button.png");
    
    // Dibujamos fondo
    SDL_Rect destino;
    destino.x=0;
    destino.y=0;
    SDL_BlitSurface(fondo, NULL, screen, &destino);
    destino.x=v_botonxpos;
    destino.y=v_botonypos;
    SDL_BlitSurface(boton, NULL, screen, &destino);

    //Actualizamos la pantalla
    SDL_Flip(screen);

    //Inicializaciones pre-Bucle
    SDL_Event evento;
    bool salir = false;
    Mix_Music *cancion;
    int limite_superior = 6;
    int limite_inferior = 4;

    //Bucle Principal           
    while(not salir) {
        int x, y;
        int numero = (rand() % limite_superior) + limite_inferior;
        SDL_Flip(screen);
        SDL_GetMouseState(&x, &y);
        while (SDL_PollEvent(&evento)) {
            switch (evento.type) {
                case SDL_MOUSEBUTTONDOWN:
                   if  ((evento.button.x >= v_botonxpos) && (evento.button.x <= v_botonxpos + boton -> w))
                     if ((evento.button.y >= v_botonypos) && (evento.button.y <= v_botonypos + boton -> h)) printf("se ha hecho clic");
                   break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                     onkeys(evento.key);
                     break;
                case SDL_QUIT:
                  salir = true;
                  break;
                case SDLK_ESCAPE:
                  salir = true;
                  break;
                }
            }
        }
    SDL_FreeSurface(fondo);
	Mix_FreeChunk(sound);
	Mix_CloseAudio();
    Mix_CloseAudio();
    SDL_Quit();
	return 0;
    }
