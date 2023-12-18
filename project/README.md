# Watermark Editor
#### Video Demo:  <URL HERE>
#### Description:
My project is an application that enables the user to add text or image watermarks onto an existing image. They can manipulate the watermark's position, size and opacity, and add multiple amounts of the same of different watermarks. 

PACKAGES AND MODULES

I used the Tkinter package, as the toolkit provided me with all the features I required.
The "askopenfilename", "asksaveasfile" modules were imported to allow the user to browse through directories to open or save a file. The "askcolor" module lets users choose a color for their text.
The "messagebox" module allowed me to work with error message windows. 
"ttk" provided me with a seperator widget for visual purposes.

The Pillow package gave me the toolkit for adding and applying watermarks. The "Image" and "ImageTK" modules handled adding an image onto another image and manipulating the properties of those images. The "ImageDraw" and "ImageFont" modules handled adding text and manipulating the properties of the text. 

The first thing I needed to do was to create an interface.  The application uses a fullscreen window. I considered allowing the window to be resizable, but ultimately decided against it, as the application works best in full screen, and any dynamic scaling would create potential UI/UX problems.

The canvas is on the left hand side of the window and the tools for manipulating watermarks are on the right. Once the user adds an image to the canvas, the features to add a watermark image or text become active. The user is then able to add a watermark onto the canvas image and can "stamp" the watermark when they wish to apply it. The same can be done with text that the user inputs into the text box.

FUNCTIONS

The "add_text"