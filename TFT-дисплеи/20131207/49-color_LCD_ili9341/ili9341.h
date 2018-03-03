/* small color graphics LCD based on ILI9341 chip */
/* ili9341.h */

/* hardware definition. Data is in SPI */
#define CONF_ILI9341_CS_PIN        _BV(4)
#define CONF_ILI9341_DC_PIN        _BV(3)
//#define CONF_ILI9341_BACKLIGHT_PIN 0
#define CONF_ILI9341_RESET_PIN     _BV(2)

//TFT resolution 240*320
#define MIN_X	0
#define MIN_Y	0
#define MAX_X	239
#define MAX_Y	319

#define FONT_SPACE 6
#define FONT_X 8
#define FONT_Y 8

#define ILI9341_COLOR(red, green, blue)   ((unsigned int)( (( red >> 3 ) << 11 ) | (( green >> 2 ) << 5  ) |  ( blue  >> 3 ))) 

 #define BLACK                       ILI9341_COLOR(0x00, 0x00, 0x00) 
 #define WHITE                       ILI9341_COLOR(0xFF, 0xFF, 0xFF) 
 #define RED                         ILI9341_COLOR(0xFF, 0x00, 0x00) 
 #define GREEN                       ILI9341_COLOR(0x00, 0xFF, 0x00) 
 #define BLUE                        ILI9341_COLOR(0x00, 0x00, 0xFF) 
 #define YELLOW                      ILI9341_COLOR(0xFF, 0xFF, 0x00) 
 #define MAGENTA                     ILI9341_COLOR(0xFF, 0x00, 0xFF) 
 #define CYAN                        ILI9341_COLOR(0x00, 0xFF, 0xFF) 
 #define GRAY                        ILI9341_COLOR(0x80, 0x80, 0x40) 
 #define SILVER                      ILI9341_COLOR(0xA0, 0xA0, 0x80) 
 #define GOLD                        ILI9341_COLOR(0xA0, 0xA0, 0x40) 


