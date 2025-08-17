#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct{
    volatile int counter;
    volatile int flags_image;
    volatile int flags_font;
    volatile int change_str;
    volatile int alpha;
    //static_cast Static_cast;
} Flags;

typedef struct{
    SDL_Window* (*CreateWindow)(const char *title,int width,int height,Uint32 flags);
    SDL_Renderer* (*CreateRender)(SDL_Window *win,int level,Uint32 flags);
    SDL_Texture* (*CreateTextureSurf)(SDL_Renderer *render,const char *name);
    Flags flags;
} WrapperSDL2;

SDL_Window *create_win(const char *title,int w,int h,Uint32 flags){
    SDL_WindowFlags f = flags;
    SDL_Window *window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,f);
    if(!window){
      printf("Error made windows %s",SDL_GetError());
      return NULL;
    }
    return window;
}

SDL_Renderer *rendering(SDL_Window *win,int l,Uint32 f){
    SDL_Renderer *ren = SDL_CreateRenderer(win,l,f);
    if(!ren){
      printf("Error made renderer %s",SDL_GetError());
      return NULL;
    }
    return ren;
}

SDL_Texture *create_texture_surf(SDL_Renderer *render,const char *name){
    SDL_Surface *surf = IMG_Load(name);
    if(!surf){
      printf("Error create texture surface %s",SDL_GetError());
      return NULL;
    }
    SDL_Texture *text = SDL_CreateTextureFromSurface(render,surf);
    SDL_FreeSurface(surf);
    return text;
}

WrapperSDL2 InitWrapper(){
  WrapperSDL2 win = {create_win,rendering};
  memset(&win.flags,0,sizeof(win.flags));
  return win;
}

//typedef struct {
//    
//} Wrapper;

int page(){
    static WrapperSDL2 Wrapper = InitWrapper();
}