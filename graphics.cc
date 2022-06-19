#include <emscripten/bind.h>

#include "snake.hh"

#include "jslib.hh"
#include "render_window.hh"

struct SnakeGame {
   int TILE_SIZE;
   Snake *snake;
   RenderWindow *window;

   SnakeGame(int tile_size, int board_size) {
      TILE_SIZE = tile_size;
      snake = new Snake(board_size);
      window = new RenderWindow(
         (2 + board_size) * TILE_SIZE,
         (2 + board_size) * TILE_SIZE);
      draw();
   }

   ~SnakeGame() {
      delete snake;
      delete window;
   }

   void draw() {
      window->clear( js_blue );

      int BOARD_SIZE = snake->get_board_size();
      RectangleShape shape(TILE_SIZE*BOARD_SIZE, TILE_SIZE*BOARD_SIZE);
      shape.setFillColor( js_black );
      shape.setPosition(1*TILE_SIZE, 1*TILE_SIZE);
      window->draw(shape);

      for (auto&& [ x, y, content ] : *snake) {
         RectangleShape shape(TILE_SIZE, TILE_SIZE);
         shape.setPosition((x+1)*TILE_SIZE, (y+1)*TILE_SIZE);
         switch ( content ) {
         default:
            shape.setFillColor( js_black );
            break;
         case Snake::Food:
            shape.setFillColor( js_red );
            break;
         case Snake::Body:
            shape.setFillColor( js_white );
            break;
         case Snake::Corpse:
            shape.setFillColor( js_yellow );
            break;
         case Snake::Head:
            shape.setFillColor( js_green );
            break;
         }
         window->draw(shape);
      }
   }

   void keypress(char key) {
      switch( key ) {
      case 'c':
         snake->reset();
         break;
      case 'i':
         snake->pulse();
         break;
      case 'w':
         snake->setDirection( Snake::Up );
         break;
      case 's':
         snake->setDirection( Snake::Down );
         break;
      case 'a':
         snake->setDirection( Snake::Left );
         break;
      case 'd':
         snake->setDirection( Snake::Right );
         break;
      default:
         break;
      }
      draw();
   }

   void pulse() {
      snake->pulse();
      draw();
   }

   uintptr_t get_buffer_address() {
      return (uintptr_t)window->get_buffer_address();
   }

   int getWidth() {
      return window->getWidth();
   }

   int getHeight() {
      return window->getHeight();
   }

};

// Binding code
EMSCRIPTEN_BINDINGS(my_class_example) {
   emscripten::class_<SnakeGame>("SnakeGame")
    .constructor<int, int>()
    .function("pulse", &SnakeGame::pulse)
    .function("draw", &SnakeGame::draw)
    .function("keypress", &SnakeGame::keypress)
    .function("getWidth", &SnakeGame::getWidth)
    .function("getHeight", &SnakeGame::getHeight)
    .function("getBufferAddress", &SnakeGame::get_buffer_address)
    ;
}
