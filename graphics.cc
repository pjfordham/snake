#include "snake.hh"

#include "jslib.hh"
#include "render_window.hh"

static int TILE_SIZE;
static Snake *snake;
static RenderWindow *window;

static void draw( RenderWindow *window, Snake *snake ) {
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


extern "C" void init(int tile_size, int board_size) {
   TILE_SIZE = tile_size;
   snake = new Snake(board_size);
   window = new RenderWindow(
      (2 + board_size) * TILE_SIZE,
      (2 + board_size) * TILE_SIZE);
   draw( window, snake );
}

extern "C" unsigned int *get_buffer_address() {
   return window->get_buffer_address();
}

extern "C" int getWidth() {
   return window->getWidth();
}

extern "C" int getHeight() {
   return window->getHeight();
}

extern "C" void pulse() {
   snake->pulse();
   draw( window, snake);
}

extern "C" void click(int x, int y) {

   // auto i = (y / TILE_SIZE) - 1;
   // auto j = (x / TILE_SIZE) - 1;

   // if ( 0 <= i && i < BOARD_SIZE &&
   //      0 <= j && j < BOARD_SIZE )
   // {
   //    // gol.click( i ,j );
   //    draw();
   // }

}

extern "C" void rightclick(int x, int y) {

   // auto i = (y / TILE_SIZE) - 1;
   // auto j = (x / TILE_SIZE) - 1;

   // if ( 0 <= i && i < BOARD_SIZE &&
   //      0 <= j && j < BOARD_SIZE )
   // {
   //    gol.addShape(shapes[ shapeIndex ], i,j);
   //    draw();
   // }

}


extern "C" void keypress(char key) {
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

   draw( window, snake );

}
