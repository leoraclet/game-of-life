// TODO: Implement DearImgui TODO: Load pre-made structure TODO: Use shader

// ImGui
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
// SDL
#include <SDL2/SDL.h>

/*
 * Here you can change grid and cell size
 */

#define CELL_SIZE 20       // Size of cells in pixels
#define SCREEN_SIZE_X 1920 // Screen width
#define SCREEN_SIZE_Y 1080 // Screen height

#define GRID_SIZE_X (SCREEN_SIZE_X / CELL_SIZE) // Number of grid columns
#define GRID_SIZE_Y (SCREEN_SIZE_Y / CELL_SIZE) // Number of grid rows
#define GRID_SIZE (GRID_SIZE_X * GRID_SIZE_Y)   // NUmber of cells

void updateGrid(int cells[GRID_SIZE_X][GRID_SIZE_Y]);

int main() {
  // Global variables
  bool leftMouseButtonDown = false;
  bool rightMouseButtonDown = false;
  bool darkMode = false;
  bool quit = false;
  bool update = false;
  bool showGrid = true;

  int fps = 60;
  int xPos, yPos;

  // Board of cells
  int cells[GRID_SIZE_X][GRID_SIZE_Y] = {{0}};

  // Render colors
  SDL_Color BG = {255, 255, 255, 255}; // Background color
  SDL_Color GL = {200, 200, 200, 255}; // Grid lines color
  SDL_Color AC = {0, 0, 0, 255};       // Alive cell color

  // Initialise SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return 1;
  }

  // Create window
  SDL_Window *window =
      SDL_CreateWindow("Game of life", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_SIZE_X, SCREEN_SIZE_Y,
                       SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);

  if (!window) {
    fprintf(stderr, "Error creating window.\n");
    return 2;
  }

  // Create renderer
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    fprintf(stderr, "Error creating renderer.\n");
    return 3;
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  // Initialise Dear ImGui
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer_Init(renderer);

  // Main loop running forever
  while (!quit) {
    SDL_Event event;

    // Handle user events
    while (SDL_PollEvent(&event)) {
      // ImGui_ImplSDL2_ProcessEvent(&event);

      switch (event.type) {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        // Quit window
        case SDLK_ESCAPE:
          quit = SDL_TRUE;
          break;

          // Update state ON / OFF
        case SDLK_SPACE:
          update = !update;
          break;

          // Show / Hide grid
        case SDLK_g:
          showGrid = !showGrid;
          break;

          // Change color mode
        case SDLK_c:

          // Black board and white cells
          if (darkMode) {
            AC = {0, 0, 0, 255};
            GL = {200, 200, 200, 255};
            BG = {255, 255, 255, 255};
            darkMode = false;
          }
          // White board and black cells
          else {
            BG = {0, 0, 0, 255};
            GL = {100, 100, 100, 255};
            AC = {255, 255, 255, 255};
            darkMode = true;
          }
          break;

          // Clean grid
        case SDLK_BACKSPACE:
          for (auto &cell : cells) {
            for (int &y : cell) {
              y = 0;
            }
          }
          break;

          // Update grid to next state
        case SDLK_RIGHT:
          updateGrid(cells);
          break;

          // Increase FPS
        case SDLK_UP:
          if (fps <= 55)
            fps += 5;
          break;

          // Decrease FPS
        case SDLK_DOWN:
          if (fps >= 10)
            fps -= 5;
          break;

        default:
          break;
        }
        break;

        // Handle mouse click press
      case SDL_MOUSEBUTTONDOWN:

        if (event.button.button == SDL_BUTTON_LEFT) {
          leftMouseButtonDown = true;
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
          rightMouseButtonDown = true;
        }
        break;

        // Handle mouse click release
      case SDL_MOUSEBUTTONUP:

        if (event.button.button == SDL_BUTTON_LEFT) {
          leftMouseButtonDown = false;
          cells[xPos][yPos] = 1;
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
          rightMouseButtonDown = false;
          cells[xPos][yPos] = 0;
        }
        break;

        // Handle mouse motion
      case SDL_MOUSEMOTION:

        xPos = event.motion.x / CELL_SIZE;
        yPos = event.motion.y / CELL_SIZE;

        if (leftMouseButtonDown) {
          cells[xPos][yPos] = 1;
        }
        if (rightMouseButtonDown) {
          cells[xPos][yPos] = 0;
        }

        break;

        // Handle mouse scrolling
      case SDL_MOUSEWHEEL:
        break;

        // Quit window
      case SDL_QUIT:
        quit = SDL_TRUE;
        break;

      default:
        break;
      }
    }

    // Update grid to next state
    if (update) {
      updateGrid(cells);
    }

    // Draw ImGui window
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    /*
    if (show_demo_window) { ImGui::ShowDemoWindow(&show_demo_window);
    }
    */
    // Render Dear Imgui
    ImGui::Render();

    // Draw background color
    SDL_SetRenderDrawColor(renderer, BG.r, BG.g, BG.b, BG.a);
    SDL_RenderClear(renderer);

    // Draw grid lines
    if (showGrid) {
      SDL_SetRenderDrawColor(renderer, GL.r, GL.g, GL.b, GL.a);

      for (int x = 0; x < SCREEN_SIZE_X; x += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_SIZE_Y);
      }
      for (int y = 0; y < SCREEN_SIZE_Y; y += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, 0, y, SCREEN_SIZE_X, y);
      }
    }

    // Draw cells
    SDL_SetRenderDrawColor(renderer, AC.r, AC.r, AC.r, AC.r);

    for (int i = 0; i < GRID_SIZE_X; i++) {
      for (int j = 0; j < GRID_SIZE_Y; j++) {
        if (cells[i][j] == 1) {
          SDL_Rect cell;

          cell.x = i * CELL_SIZE;
          cell.y = j * CELL_SIZE;
          cell.h = CELL_SIZE;
          cell.w = CELL_SIZE;

          SDL_RenderFillRect(renderer, &cell);
        }
      }
    }
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    // Draw everything
    SDL_RenderPresent(renderer);
    // FPS
    SDL_Delay(1000 / fps);
  }

  // Destroy Dear ImGui context
  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  // Clean up memory
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

/*
 * @brief: Update current game of life state
 *
 * @param cells: Grid of cells
 *
 * @return None
 */

void updateGrid(int cells[GRID_SIZE_X][GRID_SIZE_Y]) {
  // Made a copy of cell's board
  int lastGrid[GRID_SIZE_X][GRID_SIZE_Y];
  memcpy(lastGrid, cells, GRID_SIZE * sizeof(int));

  // Loop over each cell
  for (size_t x = 0; x < GRID_SIZE_X; x++) {
    for (size_t y = 0; y < GRID_SIZE_Y; y++) {
      int nearCells = 0;

      // Count neighbour cells
      if (x > 0)
        nearCells += lastGrid[x - 1][y];
      if (y > 0)
        nearCells += lastGrid[x][y - 1];
      if (x < GRID_SIZE_X - 1)
        nearCells += lastGrid[x + 1][y];
      if (y < GRID_SIZE_Y - 1)
        nearCells += lastGrid[x][y + 1];
      if (x > 0 && y > 0)
        nearCells += lastGrid[x - 1][y - 1];
      if (x > 0 && y < GRID_SIZE_Y - 1)
        nearCells += lastGrid[x - 1][y + 1];
      if (y > 0 && x < GRID_SIZE_X - 1)
        nearCells += lastGrid[x + 1][y - 1];
      if (y < GRID_SIZE_Y - 1 && x < GRID_SIZE_X - 1)
        nearCells += lastGrid[x + 1][y + 1];

      // Update cell state according to the number of neighbours
      if (cells[x][y] == 0) {
        // If the cell is dead and has 3 neighbours, it comes to life
        if (nearCells == 3) {
          cells[x][y] = 1;
        }
      } else {
        // If the cells is alive, and has less than two or more than 3 neighbours, then it dies
        if (nearCells < 2 || nearCells > 3) {
          cells[x][y] = 0;
        }
      }
    }
  }
}
