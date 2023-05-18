#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PENDULUM_RADIUS = 200;
const int PENDULUM_LENGTH = 300;
const int PENDULUM_CENTER_X = WINDOW_WIDTH / 2;
const int PENDULUM_CENTER_Y = WINDOW_HEIGHT / 2;
const int SOUND_FREQUENCY = 440;  //  Hz
const int SOUND_AMPLITUDE = 4096;
const int SOUND_DURATION = 1000;  // milliseconds

int main(void) 
{
    // start window
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
    {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Pendulum with Sound", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) 
    {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) 
    {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // audio part
    if (SDL_Init(SDL_INIT_AUDIO) < 0) 
    {
        std::cerr << "SDL audio initialization failed: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    
    if (SDL_OpenAudioDevice(nullptr, 0, nullptr, nullptr, 0) < 0) 
    {
        std::cerr << "Failed to open audio device: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // audio format
    SDL_AudioSpec audioSpec;
    SDL_zero(audioSpec);
    audioSpec.freq = SOUND_FREQUENCY;
    audioSpec.format = AUDIO_S16SYS;
    audioSpec.channels = 1;
    audioSpec.samples = 2048;
    audioSpec.callback = nullptr;

    
    Uint8 audioBuffer[SOUND_DURATION * audioSpec.freq / 1000];
    for (int i = 0; i < SOUND_DURATION * audioSpec.freq / 1000; ++i) 
    {
        double time = static_cast<double>(i) / audioSpec.freq;
        audioBuffer[i] = SOUND_AMPLITUDE * std::sin(2 * M_PI * SOUND_FREQUENCY * time);
    }

    // play sound
    SDL_QueueAudio(1, audioBuffer, sizeof(audioBuffer));
    SDL_PauseAudio(0);

    // keep window open
    bool quit = false;
    double angle = 0.0;
    Uint32 prevTicks = SDL_GetTicks();

    while (!quit) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}