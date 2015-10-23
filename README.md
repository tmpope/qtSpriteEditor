# qtSpriteEditor

*by Obey Your Thirst*

Sprite Editor application powered by Qt for CS3505.

## Required Requirements

These are requirements that we are required to include in our application:

* Set the size of the sprite in pixels
* Set and adjust the number of frames in the sprite
* Allow the user to modify the pixels of the sprite (to draw the thing)
* Provide a preview of the sprite animation cycle
* Save and load various projects using the file format defined in class - .ssp

## Extra Requirements

The following is a tentative list of the various requirements that we will promise our end user:

* Onion skin slider that shows a transparent version of the previous sprite onto the current frame
* Ability to export the project into a .gif file
* A collection of extra tools:
    * Eraser
    * Select and Move & copy and paste commands
    * Eyedropper
    * Clone onto all frames
    * Undo/Redo
    * Rotate frame 90/180/270 degrees - potentially with the select and move tool

## Notes

* It looks like if we want to be able to have the user convert our file format (.ssp) into .gif, we will need to write our own .gif encoder. The .gif file format is kind of tricky, but I think it's something that is feasible. There are libraries that exist to interact with .gif files, but those are not what we need. We need something that allows us to take our data model (whatever that may be) and convert it into a .gif file. That's something that we will need to write ourselves. For more information, please refer to these links: [here for a general understanding of a gif](https://en.wikipedia.org/wiki/GIF), [here for how gif files are encoded](http://giflib.sourceforge.net/whatsinagif/bits_and_bytes.html), and [here for an explanation of the algorithm that encodes it](https://www.youtube.com/watch?v=j2HSd3HCpDs). I'm more than happy to sit down and write the thing (I think it would be pretty fun) but it does mean that we will have to divert time, attention and resources to doing that. 
