# raymarch-fractal

Raymarched, 4D Julia set fractals

## [Version 1](https://github.com/d-002/raymarch-fractal/tree/master/v1_cpu): CPU-only, coded in c

Requires `SDL2`

### Build
```
make
```

### Screenshots

<p align="center">
  <img width="49%" src="https://github.com/user-attachments/assets/3f3e2163-bb21-40b1-ba3e-6f31b58241da" />
  <img width="49%" src="https://github.com/user-attachments/assets/d1c48578-257d-44f9-bc2a-3eaa65652c48" />
</p>

## [Version 2](https://github.com/d-002/raymarch-fractal/tree/master/v2_shaders): Compute shaders, used in a Unity project

Use the [Releases](https://github.com/d-002/raymarch-fractal/releases) page for releases

Sorry for the Vim-like controls :) but you do need a lot of keys to move around and rotate in 4D.

You will need a beefy gpu for some of the more expensive settings (small step ratio, antialiasing...)

### Keybinds

#### Movement
- forwards/left/backwards/right: wasd
- up/down/ana/kata: space/left shift/q/e

#### Rotation
These are the rotation keys for each plane. For example "*xz: ab*" means a rotates in one direction and b in the other, around the xz plane
- xy: hl
- xz: left/right arrows
- xw: jk
- yz: up/down arrows
- yw: yo
- zw: ui

#### Other options
- Cycle antialiasing (between 1, 2 and 4, higher value are smoother): t
- Cycle step ratio (between 1, 0.8, 0.5, 0.3, smaller values are more accurate): g
- Decrease/increase the fog distance: minus/plus (on keypad, sorry laptop users)
- Decrease/increase fog depth: divide/multiply (on keypad)
- Toggle popup menu: Return

### Screenshots

<p align="center">
  <img width="49%" src="https://github.com/user-attachments/assets/68e490ef-ab08-4467-94c9-24f07f674fba" />
  <img width="49%" src="https://github.com/user-attachments/assets/68750fa1-36bf-4ad6-821d-195187e1d0b2" />
</p>
