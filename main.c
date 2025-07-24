#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <curl/curl.h>

typedef struct{
    int x,y;
} Vector2;

typedef struct{
    volatile int counter;
    volatile int flags_image;
    volatile int flags_font;
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
    //window->CreateTextureSurf = create_texture_surf;
    // Main program
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    SDL_Window *win = window->CreateWindow("Black Raven",800,600,SDL_WINDOW_RESIZABLE);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    SDL_Renderer *render = window->CreateRender(win,-1,SDL_RENDERER_ACCELERATED);
    char *font_list[2] = {"0xProtoNerdFontPropo-Bold.ttf","0xProtoNerdFont-Regular.ttf"};
    TTF_Font *font[2];
    SDL_Surface *text_font[2];
    SDL_Color color = {0,0,0,0};
    Vector2 font_vector[2];
    SDL_Texture *new_font[2];
    int ttf_max = sizeof(font_list)/sizeof(font_list[0]);
    for(int i = 0;i < ttf_max;i++){
        font[i] = TTF_OpenFont(font_list[i],24);
        text_font[i] = TTF_RenderText_Blended(font[i],"Click 'q' untuk keluar",color);
        font_vector[i].x =  text_font[i]->w;
        font_vector[i].y = text_font[i]->h;
        new_font[i] = SDL_CreateTextureFromSurface(render,text_font[i]);
    }
    //SDL_Color color = {0,0,0,0};
    //SDL_Surface *text_font = TTF_RenderText_Blended(font,"Click 'q' untuk keluar",color);
    //SDL_Texture *new_font = SDL_CreateTextureFromSurface(render,text_font);

    //Vector2 font_vector = {.x = text_font->w,.y = text_font->h};
    //SDL_RenderSetLogicalSize(render,800,600);
    char *image_array[2] = {"background.jpeg","background2.jpeg"};
    SDL_Texture *text[2];
    
    int len = sizeof(text)/sizeof(text[0]);
    SDL_Surface *surf[len];
    
    for(int i = 0;i < len;i++){
        surf[i] = IMG_Load(image_array[i]);
        text[i] = SDL_CreateTextureFromSurface(render,surf[i]);
        //SDL_RenderSetLogicalSize(render,surf[i]->w,surf[i]->h);
    }
    for(int i = 0;i < len;i++){
        SDL_FreeSurface(surf[i]);
    }
    for(int i = 0;i < ttf_max;i++){
        SDL_FreeSurface(text_font[i]);
    }
    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    
    //aalineRGBA(render,)
    window->counter = 1;
    window->flags_image = 1;
    window->flags_font = 1;
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
            if(e.key.keysym.sym == SDLK_w){
                window->flags_font = 1;
            }
            if(e.key.keysym.sym == SDLK_e){
                window->flags_font = 2;
            }
        }
        SDL_RenderClear(render);
        int width,height;
        SDL_GetWindowSize(win,&width,&height);
        SDL_Rect pollin[2];
        for(int i = 0;i < ttf_max;i++){
            Vector2 vector = {.x = (width - font_vector[i].x)/2,.y = (height - font_vector[i].y)/2};
            SDL_Rect rectangle = {vector.x,vector.y,font_vector[i].x,font_vector[i].y};
            pollin[i] = rectangle;
            //SDL_RenderCopy(render,new_font,NULL,&rectangle);
        }
        //SDL_RenderClear(render);
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
        switch(window->flags_font){
            case 1:
            SDL_RenderCopy(render,new_font[0],NULL,&pollin[0]);
            break;
            case 2:
            SDL_RenderCopy(render,new_font[1],NULL,&pollin[1]);
            break;
            default:
            break;
        }
        //SDL_Rect rectangle = {100,100,0,0};
        //SDL_QueryTexture(new_font,NULL,NULL,&vector.x,&vector.y);
        //SDL_RenderCopy(render,new_font,NULL,&pollin);
        SDL_RenderPresent(render);
        SDL_Delay(1);
    }
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(render);
    for(int i = 0;i < len;i++){
        SDL_DestroyTexture(text[i]);
        //TTF_CloseFont(font[i]);
    }
    for(int i = 0;i < ttf_max;i++){
        SDL_DestroyTexture(new_font[i]);
        TTF_CloseFont(font[i]);
    }
    TTF_Quit();
    free(window);
    return 0;
}