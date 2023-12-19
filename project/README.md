# Watermark Editor
#### Video Demo:  https://youtu.be/4A3bY1upRPA
#### Description:
My project is an application that enables the user to add text or image watermarks onto an existing image.
They can manipulate the watermark's position, size and opacity, and add multiple amounts of the same or different watermarks.
The two watermark types, text and image can be used alongside each other, and the user has the ability to switch between the two at any given time.
The user can save their work whenever they wish.
Should the user choose to exit, they will be asked to save, if any updates to the canvas have been made.
For simplicity, this application only handles ".png" files, but could be expanded to handle multiple image formats.

#### Setup
In the VS Code terminal, enter:

"pip install -r requirements.txt"

"pip install tk"

"python main.py"

Open the GUI from the CS50 menu to view the app.

#### Folders and files
The first folder, "Fonts" contains all the .ttf fonts used in the application.
The fonts selected are all free for both personal and commercial use.
I chose to store these locally, as a previous built worked well on my Windows system, but failed to work on a virtual operating system that wasn't Windows.
By storing the fonts locally, this bypasses any potential issues.

The other folders contains images to be used in the application. It contains my blank canvas image.


#### Packages and modules:

I used the Tkinter package, as the toolkit provided me with all the features I required.
The "askopenfilename", "asksaveasfile" modules were imported to allow the user to browse through directories to open or save a file. The "askcolor" module lets users choose a color for their text.
The "messagebox" module allowed me to work with error message windows.
"ttk" provided me with a seperator widget for visual purposes.

The Pillow package gave me the toolkit for adding and applying watermarks. The "Image" and "ImageTK" modules handled adding an image onto another image and manipulating the properties of those images. The "ImageDraw" and "ImageFont" modules handled adding text and manipulating the properties of the text.

The first thing I needed to do was to create an interface.  The application uses a fullscreen window. I considered allowing the window to be resizable, but ultimately decided against it, as the application works best in full screen, and any dynamic scaling would create potential UI/UX problems.

The canvas is on the left hand side of the window and the tools for manipulating watermarks are on the right. Once the user adds an image to the canvas, the features to add a watermark image or text become active. The user is then able to add a watermark onto the canvas image and can "stamp" the watermark when they wish to apply it. The same can be done with text that the user inputs into the text box.

#### Global values:

Maximum height and width for images is set for UI purposes.
Default values are given for sliders and text font and color to ensure no errors are thrown.
"IS_WM" and "IS_TXT" values control which watermark type is currently being used.
These values are checked whenever a slider is changed, and update when a text watermark or image watermark is added.
They are important values that allow the sliders to control only the current watermark type and ignore the other.

#### Functions:

The "blank_canvas" function will add the default image "canvas.png" onto the interface.
This sets the maximum dimensions, and any image added onto the canvas will scale to this size.
I decided to do this, so the UI remains the same once an image is added, and to give the user a sense of where their image will be placed before adding it.

The "reset_sliders" function is called when an image watermark or a text watermark is added.
This function was important to add, so that when a user switches watermark type, the new watermark reverts to the original size, opacity and default position in the top left corner of the canvas.
It also disables the stamp features, so that only the relevant watermark type stamp feature is activate once the associated function is called.
I chose not to reset sliders after the user stamps a watermark onto the canvas, as it seems more user-friendly to duplicate the watermark in the same location, with the same size and opacity, so the user can simply repeat the process until they are satisfied and wish to save, or change watermark type.

The "watermark type" function checks which watermark type is currently being handled, and calls the function pertaining to said watermark type.
The function allows certain features to activate or disable, depending on which watermark type the user is dealing with.

The "font_changed" function listens for the current selected font in the font picker box.
It is called by "adjust_text", allowing the text on screen to always reflect the selected font at any given time.

The "opacity_changed" function listens for the current selected opacity from the opacity slider.
Whenever the opacity slider is adjusted, the function will set the global values for opacity and call "watermark_type()" so that the opacity is changed for only the current watermark being handled (text or image).

The "rgb2hex" function was created to pass a hex value into the color box, once a color has been chosen for font.
The color box will simply give the user a visual aid for what color is currently selected for font.
It was necessary to convert the RGB value into a hex value for this feature to work properly.

The "size_changed" function listens for the current selected size from the size slider.
Whenever the size slider is adjusted, the function will set the global values for size and call "watermark_type()" so that the size is changed for only the current watermark being handled (text or image).

The "slider_x_changed" function listens for the current selected x value from the position(x) slider.
Whenever the position(x) slider is adjusted, the function will set the global values for x position and call "watermark_type()" so that the position is changed for only the current watermark being handled (text or image).

The "slider_y_changed" function listens for the current selected y value from the position(y) slider.
Whenever the position(y) slider is adjusted, the function will set the global values for y position and call "watermark_type()" so that the position is changed for only the current watermark being handled (text or image).

The "add_image" function enables to user to open a PNG file to be used as a base image.
Once opened, the image will scale down to the canvas size, if it exceeds it, and will be displayed on the canvas.
This function is called when the user clicks the "Add Image" button displayed on the top left corner of the interface.
I chose to make this the largest button, as it is required for further use of other features. Without an image, all other features are disabled.

The "add_text" function is called whenever the "adjust_text" function is called.
The function utilises the Pillow modules ImageFont and ImageDraw to draw text onto the main image on the canvas. It checks for selected font, opacity, size, color and position, and draws text accordingly.

The "add_watermark" function is called when the "Add watermark" button.
A pop-up window will allow the user to open a PNG file to use as a watermark.

The "adjust_text" function is called when the "Font changed" button is clicked and "reset_wm_sliders()" is called, the text color is changed or the "watermark_type" function is called whilst IS_TXT is True.
The function sets text font, size, opacity and position, before calling "add_text" and passing in these values.
While a text watermark is active on the canvas, all image watermark features are disabled, allowing the sliders to adjust only the text.

The "adjust_watermark" function is called when a watermark image is added or any of the sliders are adjusted, provided a watermark image has been added already.
The function scales the watermark image if it exceeds the maximum size, and pastes the image onto the canvas according to the selected size, opacity and position.
While an image watermark is active on the canvas, all text watermark features are disabled, allowing the sliders to adjust only the image.

The "change_color" function is called when the user clicks the "Color" button.
This opens a window that allows the user to choose a font color, and sets the values before calling "adjust_text()"

The "close_files" function removes temporary files stored in the project folder.

The "close_window" function closes the window and attempts to clear the remaining temporary file.
In case no file was ever saved, the function will simply pass before closing the window without throwing an error.

The "enable_text" function is called by "adjust_text()" and activates the text features, whilst deactivating the image watermark features.

The "enable_watermark" function is called by "adjust_watermark()" and activates the image watermark features, whilst deactivating the text features.

The "on_exit" function is called when the "Save and CLose" button is clicked.
It checks for any temporary files, and will ask the user to save if there are any existing images.
If the user wishes to save, "save_image()" will be called before "close_window()".
If the user does not wish to save, "close_files()" is called to handle the remaining temporary files, before "close_window()"
If there has been no activity and no temporary files exists, only close_window() will be called.

The "remove_text" function is called when the "Remove text" button is clicked.
The function will simply replace the current canvas image with a previous one, saved as a temporary file.
It checks for three different temporary images, depending on if a watermark image, text or both have been added.
Once called, the button will then disable, as only one previous state for the image exists/

The "remove_watermark" function is called when the "Remove watermark" button is clicked.
The function will simply replace the current canvas image with a previous one, saved as a temporary file.
It checks for three different temporary images, depending on if a watermark image, text or both have been added.
Once called, the button will then disable, as only one previous state for the image exists.

The "reset_wm_sliders" function acts as a way to reset sliders and activate text.
When the Add text button calls this function, it simply calls "reset_sliders()" and "adjust_text()".
The reason for this function was because I needed a way to reset sliders first, which disables text features, and then by calling "adjust_text()" the sliders will enable again.
This function is somewhat of a workaround.

The "save_image" function will find the most recently saved temporary file (the current image on the canvas) and save it to a folder of the user's choosing.
A pop up window will allow user to set a directory to save the image into.

The "save_text" function is called when the user clicks the top "Stamp" button, to place their text watermark.
It will find the most recently saved temporary file (the current image on the canvas) and save it, allowing the text to be effectively stamped onto the canvas.
Once stamped, the button will be disabled until more text is created.

The "save_watermark" function is called when the user clicks the bottom "Stamp" button, to place their image watermark.
It will find the most recently saved temporary file (the current image on the canvas) and save it, allowing the image watermark to be effectively stamped onto the canvas.
Once stamped, the button will be disabled until another image watermark is created.

#### User Interface:

I chose to create a minimal interface, with as few buttons and sliders as possible, whilst still allowing a range of features.
The top row of buttons control what goes onto or gets removed from the canvas, and allows the canvas image to be saved at any point.

On the sidebar are the tools to manipulate the image and text watermarks.
I wanted the tools to feel intuitive, and used labels where only absolutely necessary.
The position sliders were changed to align horizontally and vertically to make it more visual to the user.
For this reason I chose not to use numbers on the sliders, as the slider itself physically indicates the axis' positions.
I added numbers to the opacity and size sliders to better inform users of their impact on the watermark, and to allow users to be aware of these numbers if they wish to replicate the conditions for other watermarks.

On the top of the sidebar are all the text features.
I chose to bunch them together so choosing a text felt intuitive and the user feels compelled to use them and experiment whilst adding a text watermark.
The color box was used to give the user visual feedback of their selected color.
It is set to black by default but will be replaced by a new panel whenever the user updates the color.

I chose to put the stamp buttons close to the sliders for ease of use, as the user will most likely want to place the watermark after moving it, and may wish to repeat the process.
I would have preferred only one stamp button, but it proved to be problematic, and instead opted for two.
To avoid confusion, all features of the watermark type not being used are disabled, and only those for the current watermark type are active.
