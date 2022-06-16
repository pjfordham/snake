#include "jslib.hh"
#include "snake.hh"
#include <string.h>
#include <stdio.h>

const int TILE_SIZE = 20;

const unsigned int SCREEN_WIDTH  = (2+BOARD_SIZE) * TILE_SIZE;
const unsigned int SCREEN_HEIGHT = (2+BOARD_SIZE) * TILE_SIZE;

unsigned int BUFFER[SCREEN_WIDTH * SCREEN_HEIGHT];

extern "C" unsigned int *get_buffer_address() { return &BUFFER[0]; }


extern "C" int getWidth() {
   return SCREEN_WIDTH;
}

extern "C" int getHeight() {
   return SCREEN_HEIGHT;
}

extern "C" void plot(int x, int y, unsigned int color) {
   BUFFER[SCREEN_WIDTH * y + x] = color;
}

static void plot_rectange(int x, int y, unsigned int color) {
   for (int i = 0; i < TILE_SIZE; ++i) {
      for (int j = 0; j < TILE_SIZE; ++j) {
         plot( x * TILE_SIZE + i,
               y * TILE_SIZE + j,
               color );
      }
   }
}



bool running = false;
Snake snake;

static void draw() {
   for( int x=1;x<BOARD_SIZE+1;x++ ){
      for ( int y = 1;y<BOARD_SIZE+1;y++) {
         plot_rectange(x, y, 0xFF000000);
      }
   }
   for (auto&& [ x, y, content ] : snake) {

      switch ( content ) {
      default:
         plot_rectange(x+1, y+1,js_black);
         break;
      case Snake::Food:
         plot_rectange(x+1, y+1,js_red);
         break;
      case Snake::Body:
         plot_rectange(x+1, y+1,js_white); ;
         break;
      case Snake::Corpse:
         plot_rectange(x+1, y+1,js_yellow);
         break;
      case Snake::Head:
         plot_rectange(x+1, y+1,js_green);
         break;
      }
   }
}


extern "C" void init() {
   // Clear window to Blue to do blue boarder.
   for( int x=0;x<BOARD_SIZE+2;x++ ){
      for ( int y = 0;y<BOARD_SIZE+2;y++) {
         plot_rectange(x, y, 0xFFFF0000);
      }
   }
   draw();
}

extern "C" void pulse() {
   if (running) {
      snake.pulse();
      draw();
   }
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
      snake.reset();
      break;
   case 'i':
      snake.pulse();
      break;
   case 'w':
      snake.setDirection( Snake::Up );
      break;
   case 's':
      snake.setDirection( Snake::Down );
      break;
   case 'a':
      snake.setDirection( Snake::Left );
      break;
   case 'd':
      snake.setDirection( Snake::Right );
      break;
   default:
      running = !running;
      break;
   }

   draw();

}
