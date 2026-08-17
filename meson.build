project('snake', 'c')
fs = import('fs')

sdl3_dep = dependency('sdl3')
sdl3_image_dep = dependency('sdl3-image')

tinyfiledialogs = library('tinyfiledialogs', ['ext/tinyfiledialogs/tinyfiledialogs.c'])

executable('snake', ['main.c', 'window.c', 'snake.c', 'defs.c', 'canvas.c', 'apple.c'], dependencies: [sdl3_dep, sdl3_image_dep], link_with: tinyfiledialogs)

fs.copyfile('spr_apple.png')
fs.copyfile('spr_grass.png')
fs.copyfile('spr_snake_down.png')
fs.copyfile('spr_snake_left.png')
fs.copyfile('spr_snake_right.png')
fs.copyfile('spr_snake_tail.png')
fs.copyfile('spr_snake_up.png')