# Star Rangers: A Dungeon Crawler for the MSX2

The objective of this project is to learn some programming for MSX2 computers while having some fun creating an old school dungeon crawler.

My primary references are games like The Eye of the Beholder, Shining in the Darkness, and Digital Devil Story: Megami Tensei.

![Ingame Screenshot](https://pbs.twimg.com/media/E9gUsnaXoAAozWR?format=jpg&name=small)

It's being created in GRAPHIC 4, SCREEN 5 mode (resolution: 256 x 212 pixels, 16 colours per pixel). It allows 4 pages of VRAM.

**How video memory is organized during dungeon gameplay:**
* The first page is the active page (the one being visible on the screen). I stopped using double buffer since I noticed it takes too much time and means having two pages dedicated exclusively to it. The VDP is fast enough to draw directly on the visible page so I can keep the second page for storing additional graphics. The first screen is also the page storing the hardware sprites (currently I'm not sure if I will end up using them in the game).
  
  ![image](https://github.com/SaffronCR/msx-rpg/assets/11486276/792fd0d8-e344-4bc3-8779-1c75b947e412)
  
* The second page is mostly empty now. Currently I use it to prepare the dungeon view, since that requires drawing different pieces using the painter's algorithm and that would be visible to the player if done directly on the active page. I will probably store other graphics in this page eventually.
  
  ![image](https://github.com/SaffronCR/msx-rpg/assets/11486276/4e269d30-df6b-4506-8b80-f424637695e8)
  
* The third page contains the bitmap font, dungeon background and sprites (player avatar, enemies, etc).
  
  ![image](https://github.com/SaffronCR/msx-rpg/assets/11486276/eaea825a-8ed9-4b7e-9eca-62f16473ea79)
  
* The fourth page contains the dungeon walls.
  
  ![image](https://github.com/SaffronCR/msx-rpg/assets/11486276/fceecb6d-51a5-4e12-85c6-8b5e01a89d96)

**Things done:**
* Dungeon rendering/movement.
* Dungeon generation.
* Bitmap font rendering with color support.
* Music support.
* Sound effects.
* Intro screen (needs rework).
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
* Save/Load game.
* Game Over screen.

## How To Compile

* Download the repository with your git client of your choice.
* The project is configured for Visual Studio Code, but any other editor will do.
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
* In Visual Studio Code you can select "Terminal/Run Build Task" to build and run the game.
* The game should run.
* Enjoy!

## License

Star Rangers is being created by Cristina Ramos.

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

**MSX-DOS binaries (MSXDOS.SYS and COMMAND.COM)**
*- Owned by MSX Licensing Corporation*

http://www.nishi.org/

**Nextor binaries (NEXTOR.SYS and COMMAND2.COM)**
*- Author: Konamiman (Néstor Soriano)*

https://github.com/Konamiman/Nextor

**1-Bit Pack**
*- Author: Kenney*

https://kenney.nl/assets/1-bit-pack
