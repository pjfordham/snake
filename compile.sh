emcc  -O3  -std=c++17 graphics.cc -o snake.html --shell-file=shell.html  -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -sEXPORTED_FUNCTIONS=_click,_rightclick,_keypress,_get_buffer_address,_pulse,_init,_getWidth,_getHeight 

emcc  -O3  -std=c++17 graphics.cc -o snake.html --shell-file=shell.html  -lembind 
