## QMK firmware for @sk's *Ergohaven Remnant* ergonomic keyboard

Based on very excellent [@sunaku's work](https://sunaku.github.io/ergohaven-remnant-keyboard.html).

Difference with @sunaku's version:

- all layers placed to keymap.c, no more any json file.

- there's 3 main layers: qwerty, engram and russian ycuken (i going to learn
  engram but need to have english layout that i'm familiar with).

- caps lock used for switching english and russian layouts.

- slightly rearranged cursors layout, cursor keys now same as in [xah
  lee's](http://xahlee.info/emacs/misc/xah-fly-keys.html) fly keys.

- introduce key for switching between qwerty and engram layouts.

- any cursor, numbers, symbols, etc. layers switched to current engligh layout
  if ycuken is active (and switched back to ycuken after leaving layer)
