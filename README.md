# Star Rangers: A Dungeon Crawler for the MSX2

The objective of this project is to learn some programming for MSX2 computers while having some fun creating an old school dungeon crawler.

My primary references are games like The Eye of the Beholder, Shining in the Darkness, and Digital Devil Story: Megami Tensei.

![Ingame Screenshot](https://pbs.twimg.com/media/EcrHezDWsAA2i_R?format=png&name=large)

It's being created in GRAPHIC 4, SCREEN 5 mode (resolution: 256 x 212 pixels, 16 colours per pixel). It allows 4 pages of VRAM.

**How video memory is organized during dungeon gameplay:**
* The first and second page are being used for the front/back buffer. The active page (the one being visible on screen) is constantly swapped between the two.
* The third page contains the bitmap font, dungeon background and sprites (player avatar, enemies, etc).
* The fourth page contains the dungeon walls.

**Things done:**
* Dungeon rendering/movement.
* Dungeon generation.
* Bitmap font rendering with color support.
* Music support.
* Intro.
* Start screen.
* Minimap (Debug mode).
* Show current palette (Debug mode).

**To-Do List:**
* Menu navegation.
* Character creation.
* Hub City.
* Dungeon progression.
* Enemies/Combat.
* Treasure generation.
* Gadgets/Streams.
* Sound effects.
* Save/Load game.

## Third party resources:
**Fusion-C Library 1.2**
*Author: Eric Boez & Fernando Garcia*

http://www.repro-factory.com/
https://github.com/ericb59/Fusion-C-v1.2

**Palette based on DB16 - DawnBringer's 16 Col Palette v1.0**
*-Author: DawnBringer*

http://pixeljoint.com/forum/forum_posts.asp?TID=12795

**First Person Dungeon Crawl Art Pack**
*-Author: Clint Bellanger*

https://opengameart.org/content/first-person-dungeon-crawl-art-pack

**Cyberpunk Street Environment**
*-Author: ansimuz*

https://opengameart.org/content/cyberpunk-street-environment

**Scifi creature tileset**
*-Author: Stephen Challener (Redshrike[T3h Luggage])*

https://opengameart.org/content/scifi-creature-tileset-mini-32x32-scifi-creature-icons

**More RPG enemies**
*-Author: Redshrike*

https://opengameart.org/content/more-rpg-enemies
