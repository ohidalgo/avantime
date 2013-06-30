#ifndef MYCODE_H  // Para evitar multiples include
#define MYCODE_H

    //Inicializaciones Audio
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
      fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
	  exit(1);
      }
      
    //Cargando Audio 
    Mix_Chunk *sound = NULL;
    sound = Mix_LoadWAV("avantime.wav");
    if(sound == NULL) fprintf(stderr, "No se pudo cargar el fichero WAV: %s\n", Mix_GetError());


void salida(){
	SDL_Event event;  /* Evento auxiliar */
	if(!SDL_PollEvent(&event)) return; /* Vuelve si no hay eventos */
	if (event.type==SDL_QUIT) /* Termina si se  cierra la ventana */
		exit(0);
	if (event.key.keysym.sym==SDLK_q) /* Termina si se pulsa "q" */
		exit(0);
	if (event.key.keysym.sym==SDLK_ESCAPE) /* Termina si se pulsa Esc. */
		exit(0);
}

enum walk { justice1 , justice2 , justice3 , justice4 
	, justice5 , justice6 , justice_No  };

// Check C/Cpp class for details
// For this class , you can think in this way :
// This system needs keyboard operation , so we have bKeyXXX
// It needs a timer , so put aTick in.
// It needs a surface to display and various events to watch , so we have
// screen and event.
class _SYSTEM {
	public: // The default member type of a class is private , since we
			// are going to use these members as public , thus we declare
			// here.   Check Cpp class member -> public for details.
		bool bRun;
		bool bKeyUP , bKeyDOWN , bKeyLEFT , bKeyRIGHT ;
		int aTick;
		SDL_Surface *screen ;
		inline void FPS_Initialize(int FPS); // Initialize FPS_Fn
		inline void FPS_Fn(void); // Keep an assigned FPS in a loop
		void PollEvent(_SYSTEM & Xsys); // Check system events
		void Initialize(_SYSTEM & Xsys);
		struct _TEXT {
			SDL_Surface *imgTemp ; // Store img of text for blit
			SDL_Rect imgRect ; // Store (x,y) of text for blit
			SDL_Color fColor , bgColor;
			TTF_Font *font10 , *font12 , *font14 , *font16 ;
			char string[128]; // A string that contains 128 char
			} txt;
		// Convert Variable Argument into a string
//		inline void txt(char * txt, char *pStr , ...); 
	private: // The members in private are for internal usage.
		int NextTick , interval ; 
		SDL_Event event;
	};

// We see that animation as an object , so it should contain all pictures
// : anim[Pic_No] , coordinate infomation : animRect , and current picture
// index : pidx
class _ANIM_OBJ {
	public:
		void Initialize(_ANIM_OBJ & Xao);
		// Show this obj on a dst surface
		void showOn(_ANIM_OBJ & Xao , _SYSTEM & Xsys); 
		SDL_Rect animRect;
	private: // The members in private are for internal usage.
		SDL_Surface *anim[justice_No];
		int pidx;
		int aTick;
		void Move(_ANIM_OBJ & Xao , _SYSTEM & Xsys); 
	};

// Initialize FPS_Fn( )
inline void _SYSTEM::FPS_Initialize(int FPS) {
	NextTick = 0;
	interval = 1 * 1000 / FPS ;
return;
}

// Keep an assigned FPS in a loop
inline void _SYSTEM::FPS_Fn(void) {
if ( NextTick > SDL_GetTicks() ) SDL_Delay( NextTick - SDL_GetTicks() );
	NextTick = SDL_GetTicks() + interval ;
return;
}

// Convert Variable Argument into a string
inline void txt(char * txt , char *pStr , ...) {
	va_list valist; // Type to hold information about variable arguments
	va_start(valist, pStr); // Initialize a variable argument list
	vsprintf( txt , pStr , valist ); // Print formatted variable argument list to string
	va_end(valist); // This macro should be executed before the function 
	//returns whenever va_start has been previously used in that function.
	return;
	}

// Draw string on screen : Convert Variable Argument into a string then blit
inline void txtIt(_SYSTEM & Xsys , short x , short y , short fsize , 
							short r , short g , short b , char *pStr , ...) {
	va_list valist; // Type to hold information about variable arguments
	va_start(valist, pStr); // Initialize a variable argument list
	vsprintf( Xsys.txt.string , pStr , valist ); // Print formatted variable argument list to string
	va_end(valist); // This macro should be executed before the function 
	//returns whenever va_start has been previously used in that function.
	Xsys.txt.imgRect.x = x ;
	Xsys.txt.imgRect.y = y ;
	Xsys.txt.fColor.r = r;
	Xsys.txt.fColor.g = g;
	Xsys.txt.fColor.b = b;
	
	switch( fsize ){
		case 10:
			Xsys.txt.imgTemp = TTF_RenderText_Solid( Xsys.txt.font10 , Xsys.txt.string , Xsys.txt.fColor );
			break;
		case 12:
			Xsys.txt.imgTemp = TTF_RenderText_Solid( Xsys.txt.font12 , Xsys.txt.string , Xsys.txt.fColor );
			break;
		case 14:
			Xsys.txt.imgTemp = TTF_RenderText_Solid( Xsys.txt.font14 , Xsys.txt.string , Xsys.txt.fColor );
			break;
		case 16:
			Xsys.txt.imgTemp = TTF_RenderText_Solid( Xsys.txt.font16 , Xsys.txt.string , Xsys.txt.fColor );
			break;
		default :
			Xsys.txt.imgTemp = TTF_RenderText_Solid( Xsys.txt.font12 , "Set font size to 10 12 14 16" , Xsys.txt.fColor );
			break;
		} // switch( fsize ){ END
	SDL_BlitSurface( Xsys.txt.imgTemp , NULL , Xsys.screen , &Xsys.txt.imgRect );
	return;
	}

// This function load a image file to a surface
// Set bCKey with colorkey (R,G,B) to clear a color on the image
// Set alpha value for transparency 0(No transparent) ~ 255(Ivisible)
inline SDL_Surface *ImgLoader(char *file,bool bCKey, int r , int g , int b , int alpha)
{
	SDL_Surface *pic;
	pic = IMG_Load(file); // From SDL_image.h , load the image to pic
	// Log error message into stderr.txt if happened
	if(pic==NULL) fprintf(stderr,"Missing image %s : %s\n",file,IMG_GetError());
	if( bCKey ) {
		// Sets the color key (transparent pixel) in a blittable surface and RLE acceleration.
		SDL_SetColorKey(pic,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(pic->format,r,g,b));
 		}
	if(alpha) SDL_SetAlpha(pic, SDL_SRCALPHA|SDL_RLEACCEL , 255 - alpha);
	// This function takes a surface and copies it to a new surface of the 
	// pixel format and colors of the video framebuffer, suitable for fast 
	// blitting onto the display surface.
	pic = SDL_DisplayFormat(pic);
	return (pic);
}

// Load a normal picture into a surface
inline SDL_Surface *ImgLoader(char *file)       
				{ return ImgLoader(file,1,0,0,0,0) ; }
// Load a pic & set the transparent color to (255,255,255) , no alpha
inline SDL_Surface *ImgLoader(char *file,bool bCKey)
				{ return ImgLoader(file,1,255,255,255,0) ; }

#endif
