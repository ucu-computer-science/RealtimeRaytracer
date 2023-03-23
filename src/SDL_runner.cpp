// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//#include <stdlib.h>
//#include <SDL2/SDL.h>
//
//int show(int width, int height) {
//    SDL_Event event;
//    SDL_Renderer *renderer;
//    SDL_Window *window;
//
//    SDL_Init(SDL_INIT_VIDEO);
//    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//    SDL_RenderClear(renderer);
//
//    for (int i = 0; i < width; ++i)
//        for (int j=0; j<height; ++j) {
//            SDL_SetRenderDrawColor(renderer, i*255/width, j*255/height, i*255*j*255/height/width, 255);
//            SDL_RenderDrawPoint(renderer, i, j);
//        }
//    SDL_RenderPresent(renderer);
//    while (1) {
//        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
//            break;
//    }
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    return EXIT_SUCCESS;
//}
