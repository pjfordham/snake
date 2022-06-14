#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "support.hh"
#include <deque>

const int BOARD_SIZE = 40;
const float TILE_SIZE = 20.0f;

struct Pos {
   int x,y;

   bool operator==(const Pos&that) const {
      return x == that.x && y == that.y;
   }
};

class Game {
   std::deque<Pos> body;
   bool dead;
   Pos food;

public:

   enum direction_t {
      Up, Down, Left, Right
   };

   enum content_t {
      Snake, Food, Empty, Head
   };

private:
   direction_t new_direction;
   direction_t direction;

   void spawn_food() {
      static std::uniform_int_distribution<int> randomLocationRange(0, BOARD_SIZE-1);
      static std::random_device rd;
      static std::mt19937 randomNumbers(rd());
      do {
         food.x = randomLocationRange( randomNumbers );
         food.y = randomLocationRange( randomNumbers );
      } while ( (std::find(body.begin(), body.end(), Pos{food.x,food.y}) != body.end() ));
   }

public:

   void setDirection( direction_t dir ) {
      if ( dir == Left && direction != Right) {
         new_direction = Left;
      }
      else if ( dir == Right && direction != Left) {
         new_direction = Right;
      }
      else if ( dir == Up && direction != Down) {
         new_direction = Up;
      }
      else if ( dir == Down && direction != Up){
         new_direction = Down;
      }
   }

   void reset() {
      dead=false;
      body.clear();
      body.push_front(Pos{ BOARD_SIZE / 2,  BOARD_SIZE / 2});
      direction=Left;
      new_direction=Left;
      spawn_food();
   }

   Game() {
      reset();
   }

   content_t getContent(int x, int y) {
      if (x == body.front().x && y == body.front().y) {
         return Head;
      } else if (x == food.x && y == food.y) {
         return Food;
      } else if (std::find(body.begin(), body.end(), Pos{x,y}) != body.end() ) {
         return Snake;
      } else {
         return Empty;
      }
   }

   void iterate() {
      if (dead)
         return;

      direction = new_direction;
      int head_x = body.front().x;
      int head_y = body.front().y;

      switch (direction) {
      case Left:
         head_x--; break;
      case Right:
         head_x++;break;
      case Up:
         head_y--;break;
      case Down:
         head_y++;break;
      }

      if (head_x < 0 || head_y < 0 || head_x == BOARD_SIZE || head_y == BOARD_SIZE) {
         dead = true;
      } else if ( std::find(body.begin(), body.end(), Pos{head_x,head_y}) != body.end() ) {
         dead = true;
      } else {
         body.push_front(Pos{head_x,head_y});
         if ( head_x == food.x && head_y == food.y) {
            spawn_food();
         } else {
            body.pop_back();
         }
      }
   }

};


int main()
{
   sf::RenderWindow window(sf::VideoMode((2+BOARD_SIZE) * (int)TILE_SIZE, (2+BOARD_SIZE) * (int)TILE_SIZE), "Snake");

   Game game;

   sf::Clock clock;

   while (window.isOpen()) {
      sf::Time elapsed = clock.getElapsedTime();
      if (elapsed.asSeconds() > 0.2f) {
         game.iterate();
         clock.restart();
      }

      sf::Event event;
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed)
            window.close();
         // Respond to key pressed events
         if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Escape){
               return 0;
            }
            if (event.key.code == sf::Keyboard::Space){
               game.reset();
            }
            if (event.key.code == sf::Keyboard::Left){
               game.setDirection( Game::Left );
            }
            if (event.key.code == sf::Keyboard::Right){
               game.setDirection( Game::Right );
            }
            if (event.key.code == sf::Keyboard::Up){
               game.setDirection( Game::Up );
            }
            if (event.key.code == sf::Keyboard::Down){
               game.setDirection( Game::Down );
            }

         }
      }

      window.clear( sf::Color::Blue );
      for( int x=0;x<BOARD_SIZE;x++ ){
         for ( int y = 0;y<BOARD_SIZE;y++) {
            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            shape.setOrigin((x+1)*-TILE_SIZE, (y+1)*-TILE_SIZE);
            switch (game.getContent(x, y)) {
            case Game::Empty:
               shape.setFillColor(sf::Color::Black);
               break;
            case Game::Food:
               shape.setFillColor(sf::Color::Red);
               break;
            case Game::Snake:
               shape.setFillColor(sf::Color::White);
               break;
            case Game::Head:
               shape.setFillColor(sf::Color::Green);
               break;
            }
            window.draw(shape);
         }
      }

      window.display();
   }

   return 0;
}
