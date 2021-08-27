# Star Rangers: A Dungeon Crawler for the MSX2

The objective of this project is to learn some programming for MSX2 computers while having some fun creating an old school dungeon crawler.

My primary references are games like The Eye of the Beholder, Shining in the Darkness, and Digital Devil Story: Megami Tensei.

![Ingame Screenshot](https://pbs.twimg.com/media/E9gUsnaXoAAozWR?format=jpg&name=small)

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
* Intro screen.
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
* Game Over screen.

## How To Compile

* Download the repository with your git client of your choice.
* The project is configured for Visual Code, but any other editor will do.
* Download and install SDCC 4.1.0 (http://sdcc.sourceforge.net/). Make sure it's added to your PATH. 
* You need to modify SDCC included libraries to make them compatible with Fusion-C. Open a terminal window and browse to the Z80 library folder (SDCC\lib\z80), then type these commands:
> copy z80.lib z80.save
> 
> sdar -d z80.lib printf.rel
> 
> sdar -d z80.lib sprintf.rel
> 
> sdar -d z80.lib vprintf.rel
> 
> sdar -d z80.lib putchar.rel
> 
> sdar -d z80.lib getchar.rel
* Download and install OpenMSX (https://openmsx.org/). Create a folder inside the project called "openmsx" and extract the emulator to it. You will also need to find and install the system roms in the "share/systemroms" folder.
* In Visual Code you can select "Terminal/Run Build Task" to build and run the game.
* The game should run.
* Enjoy!

## License

Star Raiders is being created by Cristina Ramos.

The game code is licensed under a BSD-3-Clause License.

The game art (graphics, fonts, music and sound) is licensed under a Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).

## Third party resources:
**Fusion-C Library 1.2**
*- Author: Eric Boez & Fernando Garcia*

http://www.repro-factory.com/
https://github.com/ericb59/Fusion-C-v1.2

**Palette based on DB16 - DawnBringer's 16 Col Palette v1.0**
*- Author: DawnBringer*

http://pixeljoint.com/forum/forum_posts.asp?TID=12795

**First Person Dungeon Crawl Art Pack**
*- Author: Clint Bellanger*

https://opengameart.org/content/first-person-dungeon-crawl-art-pack

**Cyberpunk Street Environment**
*- Author: ansimuz*

https://opengameart.org/content/cyberpunk-street-environment

**Scifi creature tileset**
*- Author: Stephen Challener (Redshrike[T3h Luggage])*

https://opengameart.org/content/scifi-creature-tileset-mini-32x32-scifi-creature-icons

**More RPG enemies**
*- Author: Redshrike*

https://opengameart.org/content/more-rpg-enemies
