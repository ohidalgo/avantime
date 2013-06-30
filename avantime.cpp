#include "avantime.h"
#include "sfont.h"

int v_screenw = 800;
int v_screenh = 600;
int v_screenc = 16;
int v_botonxpos = 100;
int v_botonypos = 100;
int v_frames = 24;
int v_spritew = 256;
int v_spriteh = 224;

Mix_Music *cancion;
Animation Letra[7];
Object LetraK;
Object LetraQ;
SDL_Surface *text_surface;
SDL_Color fColor ;
char *Texto;
SFont_Font* sFont;
	
SDL_Rect textrect;	
SDL_Rect sfontrect;
bool textohide=true;
bool sfonthide=true;
bool salir = false;

void onkeys(SDL_KeyboardEvent key) {
  switch(key.keysym.sym) {
  	case SDLK_s:
		channel = Mix_PlayChannel(-1, sound, 0);
		//while(Mix_Playing(channel) != 0);
		break;
  	case SDLK_a:
  		for (int i=1; i<=6; i++ ) {
			Letra[i].posy = rand() % (v_screenh - v_spriteh);
			Letra[i].posx = rand() % (v_screenw - v_spritew);
			if (i==3 || i==6) Letra[i].Hide = rand() % 2;
			else Letra[i].Hide = false;
		}  	
    	break;
  	case SDLK_t:
		textrect.y = rand() % (v_screenh - 100);
		textohide = false;
		break;
  	case SDLK_c:
		sfontrect.y = rand() % (v_screenh - SFont_TextHeight(sFont));
  	   	sfonthide = false;
       	break;
  }
}
      	
int main(int argc, char** argv) {

	//Semilla aleatoria
	srand(time(NULL)); 
	
    //* Inicializando las biblioteca SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
       printf("No se pudo inicializar SDL: %s\n", SDL_GetError());
       exit(1);
    }
       
	//Inicializamos settings de SDL_mixer 
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		printf("Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}
	
	//Inicializamos Fonts
	if (TTF_Init() == -1) {
		printf("Imposible inicializar SDL_ttf: %s \n", TTF_GetError());
		exit(1);
	}

	sFont = SFont_InitFont(IMG_Load("avantime_TextSFont.NeonYellow.png"));
	if(!sFont) {
		fprintf(stderr, "Error cargando la fuente sFont");
		exit(1);
	}
		
    //Tratamos de entrar a modo grafico
    screen = SDL_SetVideoMode(v_screenw, v_screenh, v_screenc,SDL_HWSURFACE);
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
    fondo = IMG_Load("avantime_bg.jpg");
    boton = IMG_Load("avantime_button.png");
    
    //Cargamos Font ttf
    TTF_Font *font = loadfont("arial.ttf", 30);	

	//Cargamos imagenes de animacion de las Letras Q y K
	LetraK.Frames = v_frames;
	LetraK.Frame[1] = IMG_Load("./k/1.png");
	LetraK.Frame[2] = IMG_Load("./k/2.png");
	LetraK.Frame[3] = IMG_Load("./k/3.png");
	LetraK.Frame[4] = IMG_Load("./k/4.png");
	LetraK.Frame[5] = IMG_Load("./k/5.png");
	LetraK.Frame[6] = IMG_Load("./k/6.png");
	LetraK.Frame[7] = IMG_Load("./k/7.png");
	LetraK.Frame[8] = IMG_Load("./k/8.png");
	LetraK.Frame[9] = IMG_Load("./k/9.png");
	LetraK.Frame[10] = IMG_Load("./k/10.png");
	LetraK.Frame[11] = IMG_Load("./k/11.png");
	LetraK.Frame[12] = IMG_Load("./k/12.png");
	LetraK.Frame[13] = IMG_Load("./k/13.png");
	LetraK.Frame[14] = IMG_Load("./k/14.png");
	LetraK.Frame[15] = IMG_Load("./k/15.png");
	LetraK.Frame[16] = IMG_Load("./k/16.png");
	LetraK.Frame[17] = IMG_Load("./k/17.png");
	LetraK.Frame[18] = IMG_Load("./k/18.png");
	LetraK.Frame[19] = IMG_Load("./k/19.png");
	LetraK.Frame[20] = IMG_Load("./k/20.png");
	LetraK.Frame[21] = IMG_Load("./k/21.png");
	LetraK.Frame[22] = IMG_Load("./k/22.png");
	LetraK.Frame[23] = IMG_Load("./k/23.png");
	LetraK.Frame[24] = IMG_Load("./k/24.png");
	
	LetraQ.Frames = 24;
	LetraQ.Frame[1] = IMG_Load("./q/1.png");
	LetraQ.Frame[2] = IMG_Load("./q/2.png");
	LetraQ.Frame[3] = IMG_Load("./q/3.png");
	LetraQ.Frame[4] = IMG_Load("./q/4.png");
	LetraQ.Frame[5] = IMG_Load("./q/5.png");
	LetraQ.Frame[6] = IMG_Load("./q/6.png");
	LetraQ.Frame[7] = IMG_Load("./q/7.png");
	LetraQ.Frame[8] = IMG_Load("./q/8.png");
	LetraQ.Frame[9] = IMG_Load("./q/9.png");
	LetraQ.Frame[10] = IMG_Load("./q/10.png");
	LetraQ.Frame[11] = IMG_Load("./q/11.png");
	LetraQ.Frame[12] = IMG_Load("./q/12.png");
	LetraQ.Frame[13] = IMG_Load("./q/13.png");
	LetraQ.Frame[14] = IMG_Load("./q/14.png");
	LetraQ.Frame[15] = IMG_Load("./q/15.png");
	LetraQ.Frame[16] = IMG_Load("./q/16.png");
	LetraQ.Frame[17] = IMG_Load("./q/17.png");
	LetraQ.Frame[18] = IMG_Load("./q/18.png");
	LetraQ.Frame[19] = IMG_Load("./q/19.png");
	LetraQ.Frame[20] = IMG_Load("./q/20.png");
	LetraQ.Frame[21] = IMG_Load("./q/21.png");
	LetraQ.Frame[22] = IMG_Load("./q/22.png");
	LetraQ.Frame[23] = IMG_Load("./q/23.png");
	LetraQ.Frame[24] = IMG_Load("./q/24.png");	

	/*
	strcpy (LetraK.path,"./k/");
	LetraK.Init();
	strcpy (LetraQ.path,"./q/");
  	LetraQ.Init();
  	*/

	//Inicializamos animaciones posibles en pantalla
	for (int i=1; i<=6 ; i++) {
		Letra[i].MaxFrames = 24; 
		Letra[i].FrameRate = rand() % 120 + 42;
		Letra[i].FrameInc = 1;
		Letra[i].CurrentFrame = 1;
        Letra[i].Oscillate = true;
		Letra[i].posx = rand() % (v_screenw - v_spritew);
		Letra[i].posy = rand() % (v_screenh - v_spriteh); 
		Letra[i].Hide = true;  	 	
	}	
	
	//Inicializamos variables antes del bucle
	int color=0;
	Texto = "Texto de Prueba";
	textrect.x = 0;
	textrect.y = rand() % (v_screenh - 100);
	sfontrect.x = 0;
	sfontrect.y = rand() % (v_screenh - SFont_TextHeight(sFont));

    //Bucle Principal           
    while(not salir) {
    	// Dibujamos fondo
    	destino.x=0;
    	destino.y=0;
    	SDL_BlitSurface(fondo, NULL, screen, &destino);
    
    	// Dibujamos boton
    	destino.x=v_botonxpos;
    	destino.y=v_botonypos;
    	SDL_BlitSurface(boton, NULL, screen, &destino);
    	
    	//Dibujamos Letras Q y K
        for (int i=1; i<=6; i++ ) {
        	if (Letra[i].Hide == false) {
        		Letra[i].OnAnimate();
        		destino.x = Letra[i].posx;
        		destino.y = Letra[i].posy; 	
        		if (i<=3) SDL_BlitSurface(LetraK.Frame[Letra[i].CurrentFrame], NULL, screen, &destino);
				else SDL_BlitSurface(LetraQ.Frame[Letra[i].CurrentFrame], NULL, screen, &destino);
			}
        }
		 
		//Dibujamos Texto ttf
		if (textohide==false) {
			if (textrect.x <= v_screenw) {
				if (color <=254) fColor.r = fColor.g = fColor.b = color++; else color=0;
		    	text_surface = TTF_RenderText_Solid( font , "Texto de Prueba", fColor );
		    	SDL_BlitSurface(text_surface, NULL, screen, &textrect);
				textrect.x++;
			}
			else {
				textrect.x = 0; 
				textohide = true;
			}
            
		}
		
		//Dibujamos Texto Sfont
		if (sfonthide==false) {
			if (sfontrect.x <= v_screenw) {
				SFont_Write (screen, sFont, sfontrect.x,sfontrect.y,"Texto sFont!");
				sfontrect.x++;
			}
			else { 
				sfontrect.x = 0; 
				sfonthide = true;
			}
		}
	
		//Actualizamos la pantalla
        SDL_Flip(screen); 
		
        while (SDL_PollEvent(&evento)) {
            switch (evento.type) {
                case SDL_MOUSEBUTTONDOWN:
                	SDL_GetMouseState(&x, &y);
                if  ((evento.button.x >= v_botonxpos) && (evento.button.x <= v_botonxpos + boton -> w))
                     if ((evento.button.y >= v_botonypos) && (evento.button.y <= v_botonypos + boton -> h)) printf("Se ha hecho clic");
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
    LetraK.Release();
    LetraQ.Release();
	Mix_FreeChunk(sound);
    Mix_CloseAudio();
    SDL_Quit();
    SDL_FreeSurface(text_surface);
	SFont_FreeFont(sFont);
	return 0;
	}
