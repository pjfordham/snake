#ifndef JSLIB_FILE_H
#define JSLIB_FILE_H

class js_color {
public:
   unsigned char a,b,g,r;
   js_color(unsigned char _a, unsigned char _b, unsigned char _g, unsigned char _r) : a(_a), b(_b), g(_g), r(_r) {
   }

   js_color operator* ( js_color color ) const {
      return js_color( (a * color.a) >> 8,
                       (b * color.b) >> 8,
                       (g * color.g) >> 8,
                       (r * color.r) >> 8 );
   }

   operator unsigned int() const {
      return (a << 24) | (b << 16) | (g << 8) | r;
   }

};
const js_color js_red(0xFF, 0x00, 0x00, 0xFF);
const js_color js_yellow(0xFF, 0x00, 0xFF, 0xFF);
const js_color js_green(0xFF, 0x00, 0xFF, 0x00);
const js_color js_blue(0xFF, 0xFF, 0x00, 0x00);
const js_color js_black(0xFF, 0x00, 0x00, 0x00);
const js_color js_white(0xFF, 0xFF, 0xff, 0xFF);

#endif

