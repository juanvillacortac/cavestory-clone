# WIP: A SDL Cave Story clone
To compile, you must satisfy the following dependencies:

 - SDL2
 - SDL2 ttf

Before, run `make`, or `make && make run`. You can build without debug parammeter with `make DEBUG=0` flag (likewise `DEBUG=1` for debug, enabled by default).

## Configs:
In the file `config.cpp` you can change the following values:

 - Graphic Quality (getGraphicsQuality) = `ORIGINAL | HIGH` (Cave Story + graphics)
 - Scale Type (getScaleType) = `INT | FLOAT`
 - Fullscreen (getFullscreen) = *bool value*
  - You can also change this option in runtime by pressing F4.


***Note:** this project is for educational purposes only, Cave Story and Cave Story + are intellectual property of [Pixel](http://studiopixel.sakura.ne.jp/).*
