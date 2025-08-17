#define _GNU_SOURCE
#define REQUEST_SERVER
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
#include "request.h"

#define MAX_TEXT_CENTER 6
#define MAX_IMAGE_TEXT 3

#define MAX_BUFFER 4096

pthread_mutex_t futex = PTHREAD_MUTEX_INITIALIZER;

//extern void *get_login_page(const char *username,const char *password);

typedef union{
    int Integer;
    float Float64;
    double Double;
} static_cast;

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
    //Flags system page
    volatile int flags_login_page;
    volatile int flags_settings_page;
    static_cast Static_cast;
} Flags;

typedef struct{
    SDL_Window* (*CreateWindow)(const char *title,int width,int height,Uint32 flags);
    SDL_Renderer* (*CreateRender)(SDL_Window *win,int level,Uint32 flags);
    SDL_Texture* (*CreateTextureSurf)(SDL_Renderer *render,const char *name);
    SDL_Texture* (*CreateTTFTexture)(SDL_Renderer *render,const char *ttf_font,int ptsize,SDL_Color color,const char *text);
    Flags flags;
} WrapperSDL2;

// Function

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

SDL_Texture *create_ttf_texture(SDL_Renderer *render,const char *ttf_font,int ptsize,SDL_Color color,const char *text){
    TTF_Font *font_render = TTF_OpenFont(ttf_font,ptsize);
    SDL_Surface* login_page_surf = TTF_RenderText_Blended(font_render,text,color);
    SDL_Texture* login_str_texture = SDL_CreateTextureFromSurface(render,login_page_surf);
    SDL_FreeSurface(login_page_surf);
    TTF_CloseFont(font_render);
    return login_str_texture;
}

//END FUNC

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
        curl_easy_setopt(curl,CURLOPT_URL,"http://192.168.168.160:3000/api/getall");
	    //curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"accept : application/json");
        curl_easy_setopt(curl,CURLOPT_ACCEPT_ENCODING,"");
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&mem);
        res = curl_easy_perform(curl);  
    }
    else{
        fprintf(stderr,"Error request get method %s",curl_easy_strerror(res));
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

WrapperSDL2 InitWrapper(){
  WrapperSDL2 win = {create_win,rendering,create_texture_surf,create_ttf_texture};
  memset(&win.flags,0,sizeof(win.flags));
  return win;
}

int main(){
    // Init
    WrapperSDL2 Wrapper = InitWrapper();
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    pthread_t tid;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    CURLcode res;
    SDL_Window *win = Wrapper.CreateWindow("Black Raven",800,600,SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    SDL_Renderer *render = Wrapper.CreateRender(win,-1,SDL_RENDERER_ACCELERATED);
    //char *font_list = "0xProtoNerdFontPropo-Bold.ttf";
    TTF_Font *font[MAX_TEXT_CENTER];
    SDL_Surface *text_font[MAX_TEXT_CENTER];
    SDL_Color color = {0,0,0,0};
    Vector2 font_vector[MAX_TEXT_CENTER];
    SDL_Texture *new_font[MAX_TEXT_CENTER];
    pthread_create(&tid,NULL,multithread,NULL);
    pthread_detach(tid);
    char *str[MAX_TEXT_CENTER] = {"Silahkan Login untuk memulai permainan",
                                    "Click 'q' untuk keluar",
                                    "ESC : Debug mode",
                                    "Press 'h' to hide text",
                                    " ",
                                    "Demonstrated of C power and PHP server side",
                                };
    int ttf_max = sizeof(str)/sizeof(str[0]);

    for(int i = 0;i < MAX_TEXT_CENTER;i++){
        pthread_mutex_lock(&futex);
        font[i] = TTF_OpenFont("0xProtoNerdFont-Regular.ttf",24);
        text_font[i] = TTF_RenderText_Blended(font[i],str[i],color);
        text_font[i] = TTF_RenderText_Blended(font[i], str[i], color);
        if (!text_font[i]) {
            printf("TTF_RenderText_Blended failed at str[%d]: %s\n", i, TTF_GetError());
            exit(1);
        }
        font_vector[i].x =  text_font[i]->w;
        font_vector[i].y = text_font[i]->h;
        new_font[i] = SDL_CreateTextureFromSurface(render,text_font[i]);
        SDL_SetTextureAlphaMod(new_font[i],SDL_BLENDMODE_BLEND);
        pthread_mutex_unlock(&futex);
    }

    //char *login_str = "Silahkan Login untuk memulai permainan";
    SDL_Color white = {255, 255, 255, 255};  // putih
    SDL_Color red   = {255,   0,   0, 255};  // merah
    SDL_Color green = {  0, 255,   0, 255};  // hijau
    SDL_Color blue  = {  0,   0, 255, 255};  // biru
    SDL_Texture *login_str_texture = Wrapper.CreateTTFTexture(render,"0xProtoNerdFont-Regular.ttf",24,green,"Silahkan login/registrasi dahulu");

    //int size = 3;
    char *image_array[MAX_IMAGE_TEXT] = {"background.jpeg","background2.jpeg","waifu1.jpeg"};
    //char *char_chage[3] = {""}
    SDL_Texture *text[MAX_IMAGE_TEXT];
    
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

    printf("Engine by Vinzsan ⚥\n");
    printf("Backend by Rev ♀\n");

    char *request = (char *)get_page("https://google.com");
    printf("%s",request);
    fflush(stdout);
    free(request);

    Wrapper.flags.Static_cast.Float64 = 0;

    Wrapper.flags.alpha = 255;
    Wrapper.flags.flags_font = 1;
    Wrapper.flags.flags_image = 1;
    Wrapper.flags.change_str = 1;
    Wrapper.flags.counter = 1;
    Wrapper.flags.flags_login_page = 1;
    //SDL_Event event_main;
    SDL_Event e;
    while(Wrapper.flags.counter){
        const Uint8 *keyState = SDL_GetKeyboardState(NULL);
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                Wrapper.flags.counter = 0;
            }
            if(e.key.keysym.sym == SDLK_q){
                Wrapper.flags.counter = 0;
            }
            if(Wrapper.flags.flags_login_page == 2){
                if(e.type == SDL_QUIT){
                Wrapper.flags.counter = 0;
            }
            if(e.key.keysym.sym == SDLK_q) Wrapper.flags.counter = 0;
            if(e.key.keysym.sym == SDLK_1){
                Wrapper.flags.flags_image = 1;
            }
            if(e.key.keysym.sym == SDLK_2){
                Wrapper.flags.flags_image = 2;
            }
            if(e.key.keysym.sym == SDLK_w){
                Wrapper.flags.flags_font = 1;
            }
            if(e.key.keysym.sym == SDLK_e){
                Wrapper.flags.flags_font = 2;
            }
            if(e.key.keysym.sym == SDLK_ESCAPE){
                Wrapper.flags.flags_image = 0;
            }
            if(e.key.keysym.sym == SDLK_r){
                dst.h = buffer.h;
                dst.w = buffer.w;
                Wrapper.flags.flags_font = 4;
            }
            if(e.key.keysym.sym == SDLK_u){
                speed = 5;
            }
            if(e.key.keysym.sym == SDLK_4){
                Wrapper.flags.flags_font = 3;
            }
            if(e.key.keysym.sym == SDLK_h){
                Wrapper.flags.flags_font = 4;
            }
	        if(e.key.keysym.sym == SDLK_6){
                Wrapper.flags.flags_font = 5;
	        }
            if(e.key.keysym.sym == SDLK_l){
                Wrapper.flags.flags_login_page = 1;
            }
            }
        }
        SDL_RenderClear(render);
        SDL_SetRenderDrawColor(render,0,0,0,255);
        int width_resource_render,heigth_resource_render;
        SDL_GetRendererOutputSize(render,&width_resource_render,&heigth_resource_render);
        //<--------REOURCE ROLLING--------------------
        SDL_RenderSetLogicalSize(render,width_resource_render,heigth_resource_render);
        for(int i = 0;i < sizeof(text)/sizeof(text[0]);i++){
            SDL_SetTextureAlphaMod(text[i],Wrapper.flags.alpha);
        }
        for(int i = 0;i < ttf_max;i++){
            SDL_SetTextureAlphaMod(new_font[i],Wrapper.flags.alpha);
        }
        //TTF
        SDL_Rect pollin[MAX_TEXT_CENTER];
        for(int i = 0;i < ttf_max;i++){
            Vector2 vector = {.x = (width_resource_render - font_vector[i].x)/2,.y = (heigth_resource_render - font_vector[i].y)/2};
            SDL_Rect rectangle = {vector.x,vector.y,font_vector[i].x,font_vector[i].y};
            pollin[i] = rectangle;
        }
        //<--------REGION BLOCK PAGE------------------
        if (Wrapper.flags.flags_login_page == 1) {
            int width, height;
            SDL_GetWindowSize(win, &width, &height);

            Vector2 gap_size = {50, 50};
            Vector2 block = { (width - 2 * gap_size.x), (height - 2 * gap_size.y) };
            SDL_Rect rect = { gap_size.x, gap_size.y, block.x, block.y };
            SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
            SDL_RenderClear(render);
            SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
            SDL_RenderFillRect(render, &rect);
            SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
            SDL_RenderDrawRect(render, &rect);
            SDL_RenderCopy(render, login_str_texture, NULL, &pollin[0]);
            if (keyState[SDL_SCANCODE_K]) 
                Wrapper.flags.flags_login_page = 2;
        }
        //---------END REGION BLOCK PAGE--------------
        if(Wrapper.flags.flags_login_page == 2){
        //const Uint8 *keyState = SDL_GetKeyboardState(NULL);
            int win_w,win_h;
            SDL_GetWindowSize(win,&win_w,&win_h);
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
                if(Wrapper.flags.alpha <= 255){
                    Wrapper.flags.alpha += 5;
                }
            }
            if(keyState[SDL_SCANCODE_9]){
                Wrapper.flags.alpha -= 5;
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
            if (Wrapper.flags.alpha > 255) Wrapper.flags.alpha = 255;
            if (Wrapper.flags.alpha < 0) Wrapper.flags.alpha = 0;
            int margin_right = 100;
            int distance_to_right = win_w - (dst.x + dst.w);
            /*
            
            if (distance_to_right <= margin_right) {
                // Hitung alpha berdasarkan jarak
                float factor = (float)distance_to_right / (float)margin_right;
                window->alpha = (int)(factor * 255);
            } else {
                window->alpha = 255;
            }
            */   
            
            //SDL_RenderClear(render);
            //SDL_SetRenderDrawColor(render,0,0,0,255);
            int width,height;
            SDL_GetWindowSize(win,&width,&height);
            int rend_w,rend_h;
            SDL_RenderGetLogicalSize(render,&rend_w,&rend_h);
            //Vector2 barrier = {(width),(height + win_h)};
            SDL_Rect barrier = {0,(win_h - 130),win_w,65};
            SDL_RenderFillRect(render,&barrier);
            if (SDL_HasIntersection(&dst, &barrier)) {
                dst.y = barrier.y - dst.h; // biar tepat di atas lantai
                velocity = 0;
            }
            switch(Wrapper.flags.flags_image){
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
            switch(Wrapper.flags.flags_font){
                case 1:
                    SDL_RenderCopy(render,new_font[1],NULL,&pollin[1]);
                    break;
                case 2:
                    SDL_RenderCopy(render,new_font[2],NULL,&pollin[2]);
                    break;
                case 3:
                    SDL_RenderCopy(render,new_font[3],NULL,&pollin[3]);
                    break;
                case 4:
                    SDL_RenderCopy(render,new_font[4],NULL,&pollin[4]);
                    break;
	            case 5:
	                SDL_RenderCopy(render,new_font[5],NULL,&pollin[5]);
		            break;
                default:
                break;
            }
        //SDL_RenderPresent(render);
        //SDL_Delay(16);
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
    SDL_DestroyTexture(login_str_texture);
    //TTF_CloseFont(font_render);
    //pthread_join(tid,NULL);
    TTF_Quit();
    IMG_Quit();
    curl_global_cleanup();
    //free(window);
    return 0;
}
