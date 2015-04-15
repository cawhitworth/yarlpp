#include <iostream>
#include <chrono>

#include "SDLWrapper.h"
#include "PNGLoader.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#include "TextRenderer.h"
#include "Color.h"
#include <sstream>
#include "FPS.h"
#include "Map.h"
#include "MapRenderer.h"

#pragma warning(disable: 4100)
int main(int argc, char* argv[])
{

    try {
        Position origin(0, 0);
        Map m(Size(200, 200));
        SDLWrapper wrapper(SCREEN_WIDTH, SCREEN_HEIGHT);

        auto &renderer = wrapper.Renderer();
        auto textRenderer = TextRenderer("images/CLA.png", renderer);
        auto charSize = textRenderer.CharSize();
        MapRenderer mapRenderer(textRenderer, m);

        Size viewPort(SCREEN_WIDTH / charSize.w, SCREEN_HEIGHT / charSize.h);

        FPS fps;

        auto quit = false;
        while (!quit)
        {
            fps.Tick();

            SDL_Event e;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            renderer.Clear();


            mapRenderer.Render(origin, viewPort);

            std::stringstream fpsText;
            fpsText << fps.Fps() << "FPS";

            textRenderer.PrintString(fpsText.str(), origin, Color(200, 255, 200));
            textRenderer.PrintString("Yet Another Rogue-like", Position(5,2), Color(200, 200, 200));

            renderer.Present();

        }
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
