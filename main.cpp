#include <iostream>
#include <SDL2/SDL.h>
#include <memory>

struct Vector2{
  int x;
  int y;
};

template <typename T>
class Box{
private:
  T value;
public:
  Box(T val) : value(val){}

  void printValue(){
    std::cout << value << std::endl;
  }
};

class Wrapper{
public:
  bool counter = false;
  SDL_Window *CreateWindow(const char *name,int width,int heigth,SDL_WindowFlags flags){
    SDL_Window *win = SDL_CreateWindow(name,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,heigth,flags);
    if(!win){
      std::cout << "Error made window " << SDL_GetError() << std::endl;
      return nullptr;
    }
    return win;
  }

  SDL_Renderer *CreateRender(SDL_Window *win,int index,Uint32 flags){
    SDL_Renderer *render = SDL_CreateRenderer(win,index,flags);
    if(!render){
      std::cout << "Error made renderer " << SDL_GetError() << std::endl;
      return nullptr;
    }
    return render;
  }
};

int main(){
  Wrapper WrapSDL2;
  SDL_Window *window = WrapSDL2.CreateWindow("Prototype",800,600,SDL_WINDOW_RESIZABLE);
  SDL_Renderer *render = WrapSDL2.CreateRender(window,-1,SDL_RENDERER_ACCELERATED);
  int width,heigth;
  SDL_GetWindowSize(window,&width,&heigth);
  Vector2 vec = {(width - 100) / 2,(heigth - 100) / 2};

  float gravitasi = 0.5f;
  int velocity = 0;
  
  WrapSDL2.counter = true;
  SDL_Event e;
  while(WrapSDL2.counter){
    const Uint8 *status = SDL_GetKeyboardState(NULL);
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT){
	WrapSDL2.counter = false;
      }
    }
    if(status[SDL_SCANCODE_Q]) WrapSDL2.counter = false;
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render,0,255,0,255);
    int rect_w,rect_h;
    SDL_GetWindowSize(window,&rect_w,&rect_h);
    if(status[SDL_SCANCODE_RIGHT]){
      vec.x += 5;
    }
    if(status[SDL_SCANCODE_LEFT]){
      vec.x -= 5;
    }
    if(status[SDL_SCANCODE_UP]){
      velocity -= 8;
    }
    if(status[SDL_SCANCODE_DOWN]){
      velocity += 5;
    }
    if(vec.x < 0) vec.x = 0;
    if(vec.x > rect_w - 100) vec.x = rect_w - 100;
    if(vec.y < 0) vec.y = 0;
    if(vec.y > rect_h - 100) vec.y = rect_h - 100;

    velocity += gravitasi;
    vec.y += (int)velocity;

    if(vec.y > rect_h - width){
        vec.y = width - rect_h;
        velocity = 0;
    }

    // Batas atas
    if(vec.y < 0){
        vec.y = 0;
        velocity = 0;
    }
    
    SDL_Rect rect = {vec.x,vec.y,100,100};
    SDL_RenderFillRect(render,&rect);
    SDL_SetRenderDrawColor(render,100,100,100,255);
    SDL_RenderPresent(render);
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);
  return 0;
}
