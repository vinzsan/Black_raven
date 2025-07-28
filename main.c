#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <curl/curl.h>
#include <fcntl.h>

#define MAX_BUFFER 4096

typedef struct{
    int x,y;
} Vector2;

typedef struct{
    char *data;
    size_t size;
} Memory;

typedef struct {
    CURL *curl;
    CURLcode *res;
} Curl;

typedef struct{
    volatile int counter;
    volatile int flags_image;
    volatile int flags_font;
    volatile int change_str;
    volatile int alpha;
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

size_t write_data(void *ptr, size_t size, size_t nmemb, void *user) {
    size_t total_max = size * nmemb;
    Memory *mem = (Memory *)user;

    if(mem->size + total_max >= MAX_BUFFER - 1)
        total_max = MAX_BUFFER - mem->size - 1;

    memcpy(mem->data + mem->size, ptr, total_max);

    mem->size += total_max;
    mem->data[mem->size] = '\0';
    return total_max;
}

void *multithread(){
    CURL *curl = curl_easy_init();
    CURLcode res;
    //free(args);
    Memory mem = {
        .data = calloc(MAX_BUFFER,sizeof(char)),
        .size = 0
    };
    if(mem.data == NULL){
        perror("Error tidak dapat memuat resource");
        return NULL;
    }

    if(curl){
        curl_easy_setopt(curl,CURLOPT_URL,"http://voltraz.xyz");
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"accept : application/json");
        curl_easy_setopt(curl,CURLOPT_ACCEPT_ENCODING,"");
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&mem);
        res = curl_easy_perform(curl);  
    }
    else{
        fprintf(stderr,"Error request get method",curl_easy_strerror(res));
    }
    //write(STDOUT_FILENO,mem.data,mem.size);
    FILE *file = fopen("log.json","w");
    if(!file){
        //write(fd,mem.data,mem.size);
        perror("Error file isnt exist");
        fwrite(mem.data,mem.size,MAX_BUFFER,file);
    }
    //write(fd,mem.data,mem.size);
    fwrite(mem.data,1,mem.size,file);
    curl_easy_cleanup(curl);
    free(mem.data);
    return NULL;
}

int main(){
    // Init
    Window *window = malloc(sizeof(Window));
    window->CreateWindow = create_win;
    window->CreateRender = rendering;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    pthread_t tid;
    CURL *curl = curl_easy_init();
    CURLcode res;
    SDL_Window *win = window->CreateWindow("Black Raven",800,600,SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    SDL_Renderer *render = window->CreateRender(win,-1,SDL_RENDERER_ACCELERATED);
    //char *font_list = "0xProtoNerdFontPropo-Bold.ttf";
    TTF_Font *font[4];
    SDL_Surface *text_font[4];
    SDL_Color color = {0,0,0,0};
    Vector2 font_vector[4];
    SDL_Texture *new_font[4];
    pthread_create(&tid,NULL,multithread,NULL);
    char *str[4] = {"Click 'q' untuk keluar","ESC : Debug mode","Press 'h' to hide text"," "};
    int ttf_max = sizeof(str)/sizeof(str[0]);

    for(int i = 0;i < ttf_max;i++){
        font[i] = TTF_OpenFont("0xProtoNerdFont-Regular.ttf",24);
        text_font[i] = TTF_RenderText_Blended(font[i],str[i],color);
        font_vector[i].x =  text_font[i]->w;
        font_vector[i].y = text_font[i]->h;
        new_font[i] = SDL_CreateTextureFromSurface(render,text_font[i]);
        SDL_SetTextureAlphaMod(new_font[i],SDL_BLENDMODE_BLEND);
    }

    //int size = 3;
    char *image_array[3] = {"background.jpeg","background2.jpeg","waifu1.jpeg"};
    char
    SDL_Texture *text[3];
    
    int len = sizeof(text)/sizeof(text[0]);
    SDL_Surface *surf[len];
    
    for(int i = 0;i < len;i++){
        surf[i] = IMG_Load(image_array[i]);
        text[i] = SDL_CreateTextureFromSurface(render,surf[i]);
        SDL_SetTextureBlendMode(text[i],SDL_BLENDMODE_BLEND);
    }
    for(int i = 0;i < len;i++){
        SDL_FreeSurface(surf[i]);
    }
    for(int i = 0;i < ttf_max;i++){
        SDL_FreeSurface(text_font[i]);
    }
    int r_w,r_h;
    SDL_GetRendererOutputSize(render,&r_w,&r_h);
    SDL_Rect dst = {.w = 64,.h = 64,.x = (r_w - dst.w) / 2,.y = (r_h - dst.y) / 2};
    SDL_Rect buffer = dst;
    int speed = 5;

    float gravity = 0.5f;
    float velocity = 0;

    window->counter = 1;
    window->flags_image = 1;
    window->flags_font = 1;
    window->change_str = 1;
    window->alpha = 255;
    SDL_Event e;
    while(window->counter){
        const Uint8 *keyState = SDL_GetKeyboardState(NULL);
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
            if(e.key.keysym.sym == SDLK_ESCAPE){
                window->flags_image = 0;
            }
            if(e.key.keysym.sym == SDLK_r){
                dst.h = buffer.h;
                dst.w = buffer.w;
                window->flags_font = 4;
            }
            if(e.key.keysym.sym == SDLK_u){
                speed = 5;
            }
            if(e.key.keysym.sym == SDLK_4){
                window->flags_font = 3;
            }
            if(e.key.keysym.sym == SDLK_h){
                window->flags_font = 4;
            }
        }

        int win_w,win_h;
        SDL_GetWindowSize(win,&win_w,&win_h);
        //if(keyState[SDL_SCANCODE_UP]) dst.y -= speed;
        if(keyState[SDL_SCANCODE_DOWN]) dst.y += speed;
        if(keyState[SDL_SCANCODE_RIGHT]) dst.x += speed;
        if(keyState[SDL_SCANCODE_LEFT]) dst.x -= speed;
        if(keyState[SDL_SCANCODE_SPACE]) velocity = -8;
        if(keyState[SDL_SCANCODE_T]){
            dst.w += 5;
            dst.h += 5;
        }
        if(keyState[SDL_SCANCODE_Y]){
            dst.w -= 5;
            dst.h -= 5;
        }
        if(keyState[SDL_SCANCODE_S]){
            speed += 1;
        }
        if(keyState[SDL_SCANCODE_8]){
            if(window->alpha <= 255){
                window->alpha += 5;
            }
        }
        if(keyState[SDL_SCANCODE_9]){
            window->alpha -= 5;
        }
        if(dst.x < 0) dst.x = 0;
        if(dst.x > win_w - dst.w) dst.x = win_w - dst.w;
        if(dst.y < 0) dst.y = 0;
        if(dst.y > win_h - dst.h) dst.y = win_h - dst.h;

        velocity += gravity;
        dst.y += (int)velocity;

        if(dst.y + dst.h >= win_h){
            dst.y = win_h - dst.h;
            velocity = 0;
        }
        if (window->alpha > 255) window->alpha = 255;
        if (window->alpha < 0) window->alpha = 0;

        SDL_RenderClear(render);
        SDL_SetRenderDrawColor(render,0,0,0,255);
        int width,height;
        SDL_GetWindowSize(win,&width,&height);
        SDL_Rect pollin[4];
        for(int i = 0;i < ttf_max;i++){
            Vector2 vector = {.x = (width - font_vector[i].x)/2,.y = (height - font_vector[i].y)/2};
            SDL_Rect rectangle = {vector.x,vector.y,font_vector[i].x,font_vector[i].y};
            pollin[i] = rectangle;
        }
        SDL_RenderSetLogicalSize(render,width,height);
        for(int i = 0;i < sizeof(text)/sizeof(text[0]);i++){
            SDL_SetTextureAlphaMod(text[i],window->alpha);
            SDL_SetTextureAlphaMod(new_font[i],window->alpha);
        }
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
        SDL_RenderCopy(render,text[2],NULL,&dst);// Assets bukan background
        switch(window->flags_font){
            case 1:
                SDL_RenderCopy(render,new_font[0],NULL,&pollin[0]);
                break;
            case 2:
                SDL_RenderCopy(render,new_font[1],NULL,&pollin[1]);
                break;
            case 3:
                SDL_RenderCopy(render,new_font[2],NULL,&pollin[2]);
                break;
            case 4:
                SDL_RenderCopy(render,new_font[3],NULL,&pollin[3]);
                break;
            default:
            break;
        }
        SDL_RenderPresent(render);
        SDL_Delay(16);
    }
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(render);
    for(int i = 0;i < len;i++){
        SDL_DestroyTexture(text[i]);
    }
    for(int i = 0;i < ttf_max;i++){
        SDL_DestroyTexture(new_font[i]);
        TTF_CloseFont(font[i]);
    }
    pthread_join(tid,NULL);
    TTF_Quit();
    free(window);
    return 0;
}
