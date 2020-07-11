# Dungeon Crawler for MSX2

The objective of this project is to learn some programming for MSX2 computers while having some fun creating a Dungeon Crawler.

![Ingame Screenshot](https://pbs.twimg.com/media/EcrHezDWsAA2i_R?format=png&name=large)

It's being created in GRAPHIC 4, SCREEN 5 mode (resolution: 256 x 212 pixels, 16 colours per pixel). It allows 4 pages of VRAM.

**How video memory is organized during dungeon gameplay:**
* The first and second page are being used for the front/back buffer. The active page (the one being visible on screen) is constantly swapped between the two.
* The third page contains the dungeon background and sprites (enemies, doors, etc).
* The fourth page contains the dungeon walls.

**Things done**
* Dungeon rendering/movement.
* Simple dungeon generation.
* Bitmap font rendering with color support.
* Simple music support.
* Start screen.
* Minimap (for debugging purposes).
* Show current palette (for debugging purposes).

**To-Do List**
* Intro.
* Menus/UI.
* Character creation.
* Hub Town.
* Enemies/Combat.
* Inventory.
* FX sound.
* Save/Load game.

## Third party resources:
**Fusion-C Library 1.2**

*Author: Eric Boez & Fernando Garcia*

http://www.repro-factory.com/
https://github.com/ericb59/Fusion-C-v1.2

**Palette based on DB16 - DawnBringer's 16 Col Palette v1.0**

*Author: DawnBringer*

http://pixeljoint.com/forum/forum_posts.asp?TID=12795

**First Person Dungeon Crawl Art Pack**

*Author: Clint Bellanger*

https://opengameart.org/content/first-person-dungeon-crawl-art-pack

**Cyberpunk Street Environment**

*Author: ansimuz*

https://opengameart.org/content/cyberpunk-street-environment

**Scifi creature tileset**

*Author: Stephen Challener (Redshrike[T3h Luggage])*

https://opengameart.org/content/scifi-creature-tileset-mini-32x32-scifi-creature-icons

**More RPG enemies**

*Author: Redshrike*

https://opengameart.org/content/more-rpg-enemies
