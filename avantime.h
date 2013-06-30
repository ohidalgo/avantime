#ifndef _MySdlTools_
    #define _MySdlTools_
    
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

int v_screenw = 800;
int v_screenh = 600;
int v_screenc = 16;
int v_botonxpos = 100;
int v_botonypos = 100;
int v_frames = 25;
int v_spritew = 256;
int v_spriteh = 224;
Mix_Music *cancion;
int channel;
int audio_rate = 22050;
Uint16 audio_format = AUDIO_S16SYS;
int audio_channels = 2;
int audio_buffers = 4096;
Mix_Chunk *sound = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *fondo = NULL;
SDL_Surface *boton = NULL;
SDL_Rect destino;
SDL_Event evento;
bool salir = false;
int limite_superior = 6;
int limite_inferior = 4;
int x, y;

class Object {
	public:
		int Frames;
		char path[];
		SDL_Surface *Frame[24];
		void Init();
		void Release();
	};
/*	
void Object::Init() {
	char ext[5];
	char temp[3] = "";
	strcpy(temp, path);
	for (int i=1; i<=Frames ; i++) {
		strcat(ext,itoa(i,temp,10)); strcat(ext,".png");
		printf(temp);
		Frame[i] = IMG_Load(temp);
	}
	return;
}
*/

void Object::Release() {
	for (int i=1; i<=Frames ; i++) SDL_FreeSurface(Frame[i]);
	return;
}
         
class Animation {
    public:
        int    FrameInc;
        int    FrameRate; //Milliseconds   	
        int    MaxFrames;
        bool   Oscillate;
        bool 	Hide;
        int		CurrentFrame;
		int 	posx;
		int 	posy;
		bool 	letrak;
	private:
		long   OldTime; 
        
    public:
        void OnAnimate();
        void SetFrameRate(int Rate);
        int GetCurrentFrame();
        void SetCurrentFrame(int Frame);
};
		  
void Animation::OnAnimate() {
    if(OldTime + FrameRate > SDL_GetTicks()) {
        return;
    } 
    OldTime = SDL_GetTicks();
    CurrentFrame += FrameInc;
    if(Oscillate) {
        if(FrameInc > 0) {
            if(CurrentFrame >= MaxFrames) {
                FrameInc = -FrameInc;
            }
        }else{
            if(CurrentFrame <= 1) {
                FrameInc = -FrameInc;
            }
        }
    }else{
        if(CurrentFrame >= MaxFrames) {
            CurrentFrame = 1;
        }
    }
}

void Animation::SetFrameRate(int Rate) {
    FrameRate = Rate;
}
 
void Animation::SetCurrentFrame(int Frame) {
    if(Frame < 0 || Frame >= MaxFrames) return;
    CurrentFrame = Frame;
}
 
int Animation::GetCurrentFrame() {
    return CurrentFrame;
}

TTF_Font* loadfont(char* file, int ptsize)
  {
    TTF_Font* tmpfont;
    tmpfont = TTF_OpenFont(file, ptsize);
    if (tmpfont == NULL){
      printf("Imposible cargar fuente: %s %s \n", file, TTF_GetError());
      exit(1);
    }
    return tmpfont;
  }	
  
enum textquality {solid, shaded, blended};
 
SDL_Surface *drawtext(TTF_Font *fonttodraw, char fgR, char fgG, char fgB, char fgA, 
  char bgR, char bgG, char bgB, char bgA, char text[], textquality quality)
  {
    SDL_Color tmpfontcolor = {fgR,fgG,fgB,fgA};
    SDL_Color tmpfontbgcolor = {bgR, bgG, bgB, bgA};
    SDL_Surface *resulting_text;
 
    if (quality == solid) resulting_text = TTF_RenderText_Solid(fonttodraw, text, tmpfontcolor);
    else if (quality == shaded) resulting_text = TTF_RenderText_Shaded(fonttodraw, text, tmpfontcolor, tmpfontbgcolor);
    else if (quality == blended) resulting_text = TTF_RenderText_Blended(fonttodraw, text, tmpfontcolor);
 
    return resulting_text;
  }
#endif
