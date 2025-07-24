#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct{
    volatile int counter;
    volatile int flags_image;
    SDL_Window* (*CreateWindow)(const char *title,int width,int height,Uint32 flags);
    SDL_Renderer* (*CreateRender)(SDL_Window *win,int level,Uint32 flags);
    SDL_Texture* (*CreateTextureSurf)(SDL_Renderer *render,const char *name);
} Window;

SDL_Window *create_win(const char *title,int w,int h,Uint32 flags){
    SDL_WindowFlags f = flags;
    SDL_Window *window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,f);
    if(!window){
        perror("Error create window");
        return NULL;
    }
    return window;
}

SDL_Renderer *rendering(SDL_Window *win,int l,Uint32 f){
    SDL_Renderer *ren = SDL_CreateRenderer(win,l,f);
    return ren;
}

SDL_Texture *create_texture_surf(SDL_Renderer *render,const char *name){
    SDL_Surface *surf = IMG_Load(name);
    if(!surf){
        perror("Error create surface");
        return NULL;
    }
    SDL_Texture *text = SDL_CreateTextureFromSurface(render,surf);
    SDL_FreeSurface(surf);
    return text;
}

//static Window window = {create_win,rendering};

int main(){
    // Init
    Window *window = malloc(sizeof(Window));
    window->CreateWindow = create_win;
    window->CreateRender = rendering;
    window->CreateTextureSurf = create_texture_surf;
    // Main program
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = window->CreateWindow("Black Raven",800,600,SDL_WINDOW_RESIZABLE);
    SDL_Renderer *render = window->CreateRender(win,-1,SDL_RENDERER_ACCELERATED);
    char *image_array[2] = {"liminal.jpeg","waifu1.jpeg"};
    SDL_Texture *text[2];
    
    int len = sizeof(text)/sizeof(text[0]);
    
    for(int i = 0;i < len;i++){
        text[i] = window->CreateTextureSurf(render,image_array[i]);
    }
    window->counter = 1;
    window->flags_image = 1;
    while(window->counter){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                window->counter = 0;
            }
            if(e.key.keysym.sym == SDLK_q) window->counter = 0;
            if(e.key.keysym.sym == SDLK_1){
                window->flags_image = 1;
            }
            if(e.key.keysym.sym == SDLK_2){
                window->flags_image = 2;
            }
        }
        SDL_RenderClear(render);
        switch(window->flags_image){
            case 1:
                SDL_RenderCopy(render,text[0],NULL,NULL);
                break;
            case 2:
                SDL_RenderCopy(render,text[1],NULL,NULL);
                break;
            default:
            break;
        }
        SDL_RenderPresent(render);
    }
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(render);
    for(int i = 0;i < len;i++){
        SDL_DestroyTexture(text[i]);
    }
    free(window);
    return 0;
}