
import pyglet
from pyglet.window import key

window = pyglet.window.Window()
keys = key.KeyStateHandler()
window.push_handlers(keys)
label = pyglet.text.Label('Hello, world',
                          font_name='Times New Roman',
                          font_size=36,
                          x=window.width//2, y=window.height//2,
                          anchor_x='center', anchor_y='center')

label2 = pyglet.text.Label('Hello,sdfgbgrld',
                          font_name='Times New Roman',
                          font_size=36,
                          x=window.width//2, y=window.height//2,
                          anchor_x='center', anchor_y='center')


@window.event
def on_draw():
#    window.clear()
#    label.draw()

    if keys[key.SPACE]:
        label.draw()

    if keys[key.ENTER]:
        label2.draw()

pyglet.app.run()

# Check if the spacebar is currently pressed:

