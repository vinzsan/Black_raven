while(Wrapper.flags.counter){
        const Uint8 *keyState = SDL_GetKeyboardState(NULL);
        while(SDL_PollEvent(&e)){
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
        }
        SDL_RenderClear(render);
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
        SDL_SetRenderDrawColor(render,0,0,0,255);
        int width,height;
        SDL_GetWindowSize(win,&width,&height);
        SDL_Rect pollin[MAX_TEXT_CENTER];
        for(int i = 0;i < ttf_max;i++){
            Vector2 vector = {.x = (width - font_vector[i].x)/2,.y = (height - font_vector[i].y)/2};
            SDL_Rect rectangle = {vector.x,vector.y,font_vector[i].x,font_vector[i].y};
            pollin[i] = rectangle;
        }
        int rend_w,rend_h;
        SDL_RenderGetLogicalSize(render,&rend_w,&rend_h);
        //Vector2 barrier = {(width),(height + win_h)};
        SDL_Rect barrier = {0,(win_h - 130),win_w,65};
        SDL_RenderFillRect(render,&barrier);
        if (SDL_HasIntersection(&dst, &barrier)) {
            dst.y = barrier.y - dst.h; // biar tepat di atas lantai
            velocity = 0;
        }
        SDL_RenderSetLogicalSize(render,width,height);
        for(int i = 0;i < sizeof(text)/sizeof(text[0]);i++){
            SDL_SetTextureAlphaMod(text[i],Wrapper.flags.alpha);
        }
        for(int i = 0;i < ttf_max;i++){
            SDL_SetTextureAlphaMod(new_font[i],Wrapper.flags.alpha);
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
	        case 5:
	            SDL_RenderCopy(render,new_font[4],NULL,&pollin[4]);
		        break;
            default:
            break;
        }
        // <--------------LOGIN PAGE--------------------->

        // <---------END REGION LOGIN PAGE--------------->
        SDL_RenderPresent(render);
        SDL_Delay(16);
    }