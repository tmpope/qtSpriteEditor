# qtSpriteEditor

*by Obey Your Thirst*

Sprite Editor application powered by Qt for CS3505.

## Required Requirements

These are requirements that we are required to include in our application:

* Set the size of the sprite in pixels - Jordan
* Set and adjust the number of frames in the sprite - Quinn
* Allow the user to modify the pixels of the sprite (to draw the thing) - Andre
* Provide a preview of the sprite animation cycle - Taylor
* Save and load various projects using the file format defined in class - .ssp - Quinn

## Extra Requirements

The following is a tentative list of the various requirements that we will promise our end user:

* Onion skin selector that shows a transparent version of the previous sprite onto the current frame - Andre
* Ability to export the project into a .gif file - use https://github.com/Kopakc/WriteAnimatedGIF library - Taylor
* A collection of extra tools:
    * Eraser - Jordan
    * Clone frame - Andre
    * Undo/Redo - Taylor
    * Eyedropper - Quinn

## Notes

* It looks like if we want to be able to have the user convert our file format (.ssp) into .gif, we will need to write our own .gif encoder. The .gif file format is kind of tricky, but I think it's something that is feasible. There are libraries that exist to interact with .gif files, but those are not what we need. We need something that allows us to take our data model (whatever that may be) and convert it into a .gif file. That's something that we will need to write ourselves. For more information, please refer to these links: [here for a general understanding of a gif](https://en.wikipedia.org/wiki/GIF), [here for how gif files are encoded](http://giflib.sourceforge.net/whatsinagif/bits_and_bytes.html), and [here for an explanation of the algorithm that encodes it](https://www.youtube.com/watch?v=j2HSd3HCpDs). I'm more than happy to sit down and write the thing (I think it would be pretty fun) but it does mean that we will have to divert time, attention and resources to doing that. 
* So [this](http://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html) may be helpful.
* Perhaps we can use [this library](http://www.imagemagick.org/Magick++/) to import a .gif file. [Here](http://stackoverflow.com/questions/19649522/getting-rgb-values-of-every-pixel-in-a-gif-file) is a guy who tried doing it. We could use his mistake as a jump off point. Also try [this](http://stackoverflow.com/questions/28151240/get-rgb-color-with-magick-using-c);
