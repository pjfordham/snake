

// int main()
// {
//    sf::RenderWindow window(sf::VideoMode((2+BOARD_SIZE) * (int)TILE_SIZE, (2+BOARD_SIZE) * (int)TILE_SIZE), "Snake");
//    Snake snake;

//    sf::Clock clock;

//    while (window.isOpen()) {

//       sf::sleep(sf::milliseconds(5));

//       bool skip_pulse = true;

//       if (clock.getElapsedTime().asMilliseconds() > 100) {
//          skip_pulse = false;
//       }

//       for ( sf::Event event; window.pollEvent(event);) {
//          if (event.type == sf::Event::Closed) {
//             window.close();
//          } else if ( event.type == sf::Event::KeyPressed ) {
//             // Respond to key pressed events
//             switch (event.key.code) {
//             default:
//                break;
//             case sf::Keyboard::Escape:
//                return 0;
//                break;
//             case sf::Keyboard::Space:
//                snake.reset();
//                skip_pulse = false;
//                break;
//             case sf::Keyboard::Left:
//                snake.setDirection( Snake::Left );
//                skip_pulse = false;
//                break;
//             case sf::Keyboard::Right:
//                snake.setDirection( Snake::Right );
//                skip_pulse = false;
//                break;
//             case sf::Keyboard::Up:
//                snake.setDirection( Snake::Up );
//                skip_pulse = false;
//                break;
//             case sf::Keyboard::Down:
//                snake.setDirection( Snake::Down );
//                skip_pulse = false;
//                break;
//             }
//             // Make the game more responsive. Accelerate pulse rate inline
//             // with rate of keypresses.
//             if (skip_pulse == false) {
//                break;
//             }
//          }
//       }

//       if (!skip_pulse && snake.pulse()) {
//          clock.restart();

//          window.clear( sf::Color::Blue );

//          sf::RectangleShape shape(sf::Vector2f(TILE_SIZE*BOARD_SIZE, TILE_SIZE*BOARD_SIZE));
//          shape.setFillColor(sf::Color::Black);
//          shape.setOrigin(1*-TILE_SIZE, 1*-TILE_SIZE);
//          window.draw(shape);

//          for (auto&& [ x, y, content ] : snake) {
//             sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
//             shape.setOrigin((x+1)*-TILE_SIZE, (y+1)*-TILE_SIZE);
//             switch (content) {
//             default:
//                shape.setFillColor(sf::Color::Black);
//                break;
//             case Snake::Food:
//                shape.setFillColor(sf::Color::Red);
//                break;
//             case Snake::Body:
//                shape.setFillColor(sf::Color::White);
//                break;
//             case Snake::Corpse:
//                shape.setFillColor(sf::Color::Yellow);
//                break;
//             case Snake::Head:
//                shape.setFillColor(sf::Color::Green);
//                break;
//             }
//             window.draw(shape);
//          }
//          window.display();

//       }
//    }

//    return 0;
// }
