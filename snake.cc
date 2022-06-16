#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>
#include <random>
#include <deque>

const int BOARD_SIZE = 40;
const float TILE_SIZE = 20.0f;

struct Pos {
   int x,y;

   bool operator==(const Pos&that) const {
      return x == that.x && y == that.y;
   }
};

class Snake {
   std::deque<Pos> body;
   bool dead;
   Pos food; // Maybe body[0] should be the food not the head?

public:

   enum direction_t {
      Up, Down, Left, Right
   };

   enum content_t {
      Corpse, Body, Food, Empty, Head
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

   Snake() {
      reset();
   }

   bool pulse() {
      if (dead)
         return false;

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
      return true;
   }

   //
   // Iteration logic
   //

   struct contents_t {
      int x, y;
      content_t content;
   };

   class iterator {
      Snake *parent;
      int index; // Maybe we could the the deque iterator internally.

   public:

      iterator( Snake* _parent) : parent{ _parent }, index( 0 ) {}

      bool operator!=(const iterator &that) const {
         return this->parent != that.parent || index != that.index;
      }

      iterator& operator++() {
         ++index;
         return *this;
      }

      contents_t operator*() const {
         if (index == 0) {
            return contents_t{parent->food.x, parent->food.y, Food};
         } else if (index == 1 && !parent->dead) {
             return contents_t{parent->body[0].x, parent->body[0].y, Head};
         } else {
            if (parent->dead)
               return contents_t{parent->body[index - 1].x, parent->body[index - 1].y, Corpse};
            else
               return contents_t{parent->body[index - 1].x, parent->body[index - 1].y, Body};
         }
      }

      friend Snake;
   };

   iterator begin() {
      return iterator(this);
   }

   iterator end() {
      auto i = iterator(this);
      i.index = body.size() + 1;
      return i;
   }

};


int main()
{
   sf::RenderWindow window(sf::VideoMode((2+BOARD_SIZE) * (int)TILE_SIZE, (2+BOARD_SIZE) * (int)TILE_SIZE), "Snake");
   Snake snake;

   sf::Clock clock;

   while (window.isOpen()) {

      sf::sleep(sf::milliseconds(5));

      bool skip_pulse = true;

      if (clock.getElapsedTime().asMilliseconds() > 100) {
         skip_pulse = false;
      }

      for ( sf::Event event; window.pollEvent(event);) {
         if (event.type == sf::Event::Closed) {
            window.close();
         } else if ( event.type == sf::Event::KeyPressed ) {
            // Respond to key pressed events
            switch (event.key.code) {
            default:
               break;
            case sf::Keyboard::Escape:
               return 0;
               break;
            case sf::Keyboard::Space:
               snake.reset();
               skip_pulse = false;
               break;
            case sf::Keyboard::Left:
               snake.setDirection( Snake::Left );
               skip_pulse = false;
               break;
            case sf::Keyboard::Right:
               snake.setDirection( Snake::Right );
               skip_pulse = false;
               break;
            case sf::Keyboard::Up:
               snake.setDirection( Snake::Up );
               skip_pulse = false;
               break;
            case sf::Keyboard::Down:
               snake.setDirection( Snake::Down );
               skip_pulse = false;
               break;
            }
            // Make the game more responsive. Accelerate pulse rate inline
            // with rate of keypresses.
            if (skip_pulse == false) {
               break;
            }
         }
      }

      if (!skip_pulse && snake.pulse()) {
         clock.restart();

         window.clear( sf::Color::Blue );

         sf::RectangleShape shape(sf::Vector2f(TILE_SIZE*BOARD_SIZE, TILE_SIZE*BOARD_SIZE));
         shape.setFillColor(sf::Color::Black);
         shape.setOrigin(1*-TILE_SIZE, 1*-TILE_SIZE);
         window.draw(shape);

         for (auto&& [ x, y, content ] : snake) {
            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            shape.setOrigin((x+1)*-TILE_SIZE, (y+1)*-TILE_SIZE);
            switch (content) {
            default:
               shape.setFillColor(sf::Color::Black);
               break;
            case Snake::Food:
               shape.setFillColor(sf::Color::Red);
               break;
            case Snake::Body:
               shape.setFillColor(sf::Color::White);
               break;
            case Snake::Corpse:
               shape.setFillColor(sf::Color::Yellow);
               break;
            case Snake::Head:
               shape.setFillColor(sf::Color::Green);
               break;
            }
            window.draw(shape);
         }
         window.display();

      }
   }

   return 0;
}
