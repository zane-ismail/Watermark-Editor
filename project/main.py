import atexit
import os
import tkinter.messagebox
from tkinter import *
from tkinter import ttk, filedialog
from tkinter.colorchooser import askcolor
from tkinter.filedialog import askopenfilename, asksaveasfile

from PIL import Image, ImageTk, ImageDraw, ImageFont

# /// SET GLOBAL VALUES ///
BOX_COLOR = "black"
COLOR_SET = False
new_font = "arial"
MAX_IMG_SIZE = 600
MAX_WM_SIZE = 200
x_value = 0
y_value = 0
IS_WM = False
IS_TXT = True
IS_EXIT = False
# Temporary image file names
USER_IMAGE = "user-image.png"
WATERMARK_IMAGE = "user-image-watermark.png"
HYBRID_IMAGE = "user-image-hybrid.png"
# Font list
fonts = (
    "Arial",
    "Bahnschrift",
    "Calibri",
    "Cambria",
    "Ebrima",
    "SimSun",
    "Tahoma",
    "Verdana",
    "Webdings",
)


# Create a blank canvas
def blank_canvas():
    blank = Image.open("canvas.png")
    blank = ImageTk.PhotoImage(blank)
    canvas = Label(borderwidth=0)
    canvas.image = blank
    canvas.configure(image=blank)
    canvas.grid(column=1, row=1, columnspan=8, rowspan=15, padx=120, pady=15)


# Reset sliders
def reset_sliders():
    slider_x.set(0)
    slider_y.set(0)
    opacity_slider.set(255)
    size_slider.set(60)
    place_txt_btn.configure(state="disabled")
    place_wm_btn.configure(state="disabled")


def watermark_type():
    if IS_WM:
        adjust_watermark()
    elif not IS_WM:
        adjust_text()


# Create window
tk = tkinter
window = Tk()
window.resizable(True, True)
window.title("Watermark Editor")
window.config(padx=0, pady=5, background="#4d5147")
window.geometry("1400x1400")
# window.overrideredirect(1)
# Add canvas
blank_canvas()
# Slider current values
current_x_value = tk.IntVar()
current_y_value = tk.IntVar()
current_opacity_value = tk.IntVar()
current_size = tk.IntVar()


# /// FONT FEATURES ///
# Change font type
def font_changed():
    global new_font
    font = [font_list.get(idx) for idx in font_list.curselection()]
    font = str(font).strip("'[]").lower()
    new_font = font


# Adjust font opacity
def opacity_changed(event):
    global OPACITY, OPACITY_SET
    OPACITY = current_opacity_value.get()
    OPACITY_SET = True
    watermark_type()


# Change font color
def rgb2hex(r, g, b):
    box_color = "#{:02x}{:02x}{:02x}".format(r, g, b)
    # Color panel
    color_panel_default = Label(width=3, borderwidth=2, relief="groove", bg=box_color)
    color_panel_default.grid(column=12, row=1, columnspan=2, padx=25, sticky="W")


# Detect size slider position
def size_changed(event):
    global SIZE, SIZE_SET
    SIZE = current_size.get()
    SIZE_SET = True
    watermark_type()


# Detect text x-axis slider position
def slider_x_changed(event):
    global x_value
    x_value = current_x_value.get()
    watermark_type()


# Detect text y-axis slider position
def slider_y_changed(event):
    global y_value
    y_value = current_y_value.get()
    watermark_type()


# /// MAIN FUNCTIONS ///
# Open image and add to canvas
def add_image():
    # Todo create a folder
    # Save folder to a generic path
    img_file_path = askopenfilename(
        initialdir="C:/Users/Public/Pictures",
        title="Select a File",
        filetypes=(
            ("PNG", "*.png"),
        ),
    )
    # When file is added open up features
    if img_file_path:
        blank_canvas()
        add_wm.configure(state="normal")
    img = Image.open(img_file_path)
    # Remove existing cache files
    close_files()
    img_width = img.width
    img_height = img.height

    # Scale image and cap height and scale width
    if (
        img.height >= MAX_IMG_SIZE
        and img.height > img.width
        or MAX_IMG_SIZE > img.height > img.width
    ):
        img_diff = int(img.height - MAX_IMG_SIZE)
        diff_per = img_diff / img.height
        img_width = int(img.width * (1 - diff_per))
        img_height = MAX_IMG_SIZE
    # Cap width at and scale height
    elif (
        img.width >= MAX_IMG_SIZE
        and img.width > img.height
        or MAX_IMG_SIZE > img.width > img.height
    ):
        img_diff = int(img.width - MAX_IMG_SIZE)
        diff_per = img_diff / img.width
        img_height = int(img.height * (1 - diff_per))
        img_width = MAX_IMG_SIZE

    # Resize image
    resized_img = img.resize(((img_width), (img_height)))
    resized_img.convert("RGBA")
    # Add image to canvas
    img = ImageTk.PhotoImage(resized_img)
    image = Label(borderwidth=0)
    image.image = img
    image.configure(image=img)
    image.grid(column=1, row=1, columnspan=8, rowspan=15, padx=120, pady=15)
    # Save image
    resized_img.save(USER_IMAGE)


# Add text
def add_text(
    new_image, x_value, y_value, text_box, new_colors
):
    txt = Image.new("RGBA", new_image.size, (255, 255, 255, 0))
    # font = ImageFont.truetype("arial.ttf", 15)
    draw = ImageDraw.Draw(txt)
    font = ImageFont.load("arial.pil")

    # t = text_box.get(1.0, 'end-1c')
    draw.text(
        (x_value, y_value), f"{text_box.get(1.0, 'end-1c')}", font=font, fill=new_colors
    )
    new_image = Image.alpha_composite(new_image, txt)
    new_image.save(HYBRID_IMAGE)
    opacity_slider.configure(from_=0, to=255)
    return new_image


# Add watermark
def add_watermark():
    global FILE_PATH
    FILE_PATH = askopenfilename(
        initialdir="C:/Users/Public/Pictures",
        title="Select a File",
        filetypes=(
            ("PNG", "*.png"),
        ),
    )
    if FILE_PATH:
        # Reset fields
        global IS_WM
        IS_WM = True
        reset_sliders()
        adjust_watermark()


# Update text properties
def adjust_text():
    global IS_TXT, IS_WM, new_font, COLORS
    IS_TXT = True
    IS_WM = False
    # Deactivate watermark features
    enable_text()
    # Update fonts
    font_changed()
    # Update size
    txt_size_slider = current_size.get()
    # Update opacity and color
    if COLOR_SET is True and OPACITY_SET is True:
        color_a = current_opacity_value.get()
        new_colors = (COLOR_R, COLOR_G, COLOR_B, color_a)
    elif COLOR_SET:
        new_colors = COLORS
    elif OPACITY_SET:
        color_a = current_opacity_value.get()
        new_colors = (0, 0, 0, color_a)
    else:
        new_colors = (0, 0, 0, 255)

    # Add text onto canvas
    try:
        try:
            with Image.open(WATERMARK_IMAGE).convert("RGBA") as new_image:
                add_text(
                    new_image,
                    x_value,
                    y_value,
                    text_box,
                    new_colors,
                )
        except FileNotFoundError:
            with Image.open(USER_IMAGE).convert("RGBA") as new_image:
                add_text(
                    new_image,
                    x_value,
                    y_value,
                    text_box,
                    new_colors,
                )
        finally:
            with Image.open(HYBRID_IMAGE).convert("RGBA") as new_image:
                add_text(
                    new_image,
                    x_value,
                    y_value,
                    text_box,
                    new_colors,
                )
        new_image = ImageTk.PhotoImage(
            add_text(
                new_image,
                x_value,
                y_value,
                text_box,
                new_colors,
            )
        )
        new_panel_1 = Label(image=new_image, borderwidth=0)
        new_panel_1.image = new_image
        new_panel_1.grid(column=1, row=1, columnspan=8, rowspan=15, padx=120, pady=15)
    except OSError:
        pass


# Update watermark
def adjust_watermark():
    global IS_TXT, IS_WM
    IS_WM = True
    IS_TXT = False
    # Deactivate text feature when watermark is added
    enable_watermark()
    watermark_image = Image.open(FILE_PATH)
    w_img_height = 0
    w_img_width = 0
    # Cap height and scale width
    if (
        watermark_image.height >= MAX_WM_SIZE
        and watermark_image.height > watermark_image.width
        or MAX_WM_SIZE > watermark_image.height > watermark_image.width
    ):
        w_img_diff = int(watermark_image.height - MAX_WM_SIZE)
        w_diff_per = w_img_diff / watermark_image.height
        w_img_width = int(watermark_image.width * (1 - w_diff_per))
        w_img_height = MAX_WM_SIZE
    elif (
        watermark_image.width >= MAX_WM_SIZE
        and watermark_image.width > watermark_image.height
        or MAX_WM_SIZE > watermark_image.width > watermark_image.height
    ):
        w_img_diff = int(watermark_image.width - MAX_WM_SIZE)
        w_diff_per = w_img_diff / watermark_image.width
        w_img_height = int(watermark_image.height * (1 - w_diff_per))
        w_img_width = MAX_WM_SIZE

    # Scale watermark image
    wm_size_slider = current_size.get()
    w_img_width = int(w_img_width * (wm_size_slider * 0.01))
    w_img_height = int(w_img_height * (wm_size_slider * 0.01))
    watermark_image = watermark_image.resize((w_img_width, w_img_height))

    # Apply transparency
    opacity = current_opacity_value.get()
    if watermark_image.mode != "RGBA":
        alpha = Image.new("L", watermark_image.size, 255)
        watermark_image.putalpha(alpha)
    paste_mask = watermark_image.split()[3].point(lambda i: i * opacity / 100)

    # Paste watermark image onto canvas
    try:
        new_image = Image.open(HYBRID_IMAGE)
        new_image.paste(watermark_image, (x_value, y_value), mask=paste_mask)
        new_image.save(WATERMARK_IMAGE)
    except FileNotFoundError:
        new_image = Image.open(USER_IMAGE)
        new_image.paste(watermark_image, (x_value, y_value), mask=paste_mask)
        new_image.save(WATERMARK_IMAGE)
    else:
        new_image.paste(watermark_image, (x_value, y_value), mask=paste_mask)
        new_image.save(WATERMARK_IMAGE)

    new_image = ImageTk.PhotoImage(new_image)
    new_panel_2 = Label(image=new_image, borderwidth=0)
    new_panel_2.image = new_image
    new_panel_2.grid(column=1, row=1, columnspan=8, rowspan=15, padx=120, pady=15)


# Change font color
def change_color():
    global COLORS, COLOR_R, COLOR_G, COLOR_B, COLOR_A, COLOR_SET
    # Select color
    COLORS = askcolor(title="Tkinter Color Chooser")
    # Check if the user selected a color
    if COLORS and COLORS[1] is not None:
        # Isolate each color parameter
        COLOR_R = COLORS[0][0]
        COLOR_G = COLORS[0][1]
        COLOR_B = COLORS[0][2]
        COLOR_SET = True
    # Update text
    adjust_text()
    # Update color sample box
    rgb2hex(COLOR_R, COLOR_G, COLOR_B)


# Clear cache files
def close_files():
    try:
        os.remove(HYBRID_IMAGE)
    except FileNotFoundError:
        pass
    try:
        os.remove(WATERMARK_IMAGE)
    except FileNotFoundError:
        pass


# Clear cache file and close main window
def close_window():
    try:
        os.remove(USER_IMAGE)
    except FileNotFoundError:
        pass
    window.quit()


# Disable watermark features when text is added and enable text features when text is added
def enable_text():
    rm_txt_btn.configure(state="normal")
    color_picker.configure(state="normal")
    font_picker.configure(state="normal")
    place_txt_btn.configure(state="normal")
    rm_wm_btn.configure(state="disabled")


# Disable text features when watermark is added and enable watermark features when watermark is added
def enable_watermark():
    rm_wm_btn.configure(state="normal")
    opacity_slider.configure(from_=0, to=100)
    place_wm_btn.configure(state="normal")
    rm_txt_btn.configure(state="disabled")
    color_picker.configure(state="disabled")
    text_box.delete("1.0", END)
    font_picker.configure(state="disabled")
    place_txt_btn.configure(state="disabled")


# Ask if user wants to save on exit
def on_exit():
    global IS_EXIT
    IS_EXIT = True
    no_image = 0
    # Check if any drafts remain open
    try:
        Image.open(HYBRID_IMAGE)
    except FileNotFoundError:
        no_image += 1
    try:
        Image.open(WATERMARK_IMAGE)
    except FileNotFoundError:
        no_image += 1
    try:
        Image.open(USER_IMAGE)
    except FileNotFoundError:
        no_image += 1
    # If there are drafts close window
    if no_image < 3:
        result = tk.messagebox.askquestion("Save", "Would you like to save your work?")
        if result == "yes":
            save_image()
            close_window()
        else:
            close_files()
            close_window()
    # If there are no drafts close window
    else:
        close_window()


# Remove text
def remove_text():
    try:
        new_image = Image.open(WATERMARK_IMAGE)
        new_image.save(HYBRID_IMAGE)

    except FileNotFoundError:
        try:
            new_image = Image.open(USER_IMAGE)
            new_image.save(HYBRID_IMAGE)

        except FileNotFoundError:
            new_image = Image.open(HYBRID_IMAGE)
            new_image.save(HYBRID_IMAGE)

    new_image = ImageTk.PhotoImage(new_image)
    new_panel_3 = Label(image=new_image, borderwidth=0)
    new_panel_3.image = new_image
    new_panel_3.grid(column=1, row=1, columnspan=8, rowspan=15, padx=120, pady=15)
    rm_txt_btn.configure(state="disabled")


# Remove watermark
def remove_watermark():
    try:
        new_image = Image.open(HYBRID_IMAGE)
        new_image.save(WATERMARK_IMAGE)

    except FileNotFoundError:
        try:
            new_image = Image.open(HYBRID_IMAGE)
            new_image.save(WATERMARK_IMAGE)

        except FileNotFoundError:
            new_image = Image.open(USER_IMAGE)
            new_image.save(WATERMARK_IMAGE)

        else:
            new_image = Image.open(USER_IMAGE)
            new_image.save(WATERMARK_IMAGE)
    new_image = ImageTk.PhotoImage(new_image)
    new_panel = Label(image=new_image, borderwidth=0)
    new_panel.image = new_image
    new_panel.grid(column=1, row=1, columnspan=8, rowspan=15, padx=120, pady=15)
    rm_wm_btn.configure(state="disabled")


# Reset watermark sliders once text is placed
def reset_wm_sliders():
    reset_sliders()
    adjust_text()


# Save Image
def save_image():
    # OPEN IMAGE TO SAVE
    try:
        save_file = Image.open(HYBRID_IMAGE)
    except FileNotFoundError:
        try:
            save_file = Image.open(WATERMARK_IMAGE)
        except FileNotFoundError:
            try:
                save_file = Image.open(USER_IMAGE)
            except FileNotFoundError:
                return tk.messagebox.showerror("Error", "You must add an image first.")

    save_directory = asksaveasfile(
        initialdir="C:/Users/Public/Pictures",
        filetypes=(
            ("PNG", ".png"),
        ),
        mode="wb",
        defaultextension=".png",
    )
    if save_directory:
        return save_file.save(save_directory)
    close_files()


# Save text onto the canvas
def save_text():
    try:
        save_file = Image.open(HYBRID_IMAGE)
        save_file.save(WATERMARK_IMAGE)
    except FileNotFoundError:
        try:
            save_file = Image.open(USER_IMAGE)
            save_file.save(WATERMARK_IMAGE)
        except FileNotFoundError:
            save_file = Image.open("user-watermark.png")
            save_file.save(WATERMARK_IMAGE)
    rm_txt_btn.configure(state="disabled")
    place_txt_btn.configure(state="disabled")


# Save watermark onto the canvas
def save_watermark():
    try:
        save_file = Image.open(WATERMARK_IMAGE)
        save_file.save(HYBRID_IMAGE)
    except FileNotFoundError:
        try:
            save_file = Image.open(HYBRID_IMAGE)
            save_file.save("user-watermark.png")
        except FileNotFoundError:
            save_file = Image.open(USER_IMAGE)
            save_file.save(USER_IMAGE)
    rm_wm_btn.configure(state="disabled")
    place_wm_btn.configure(state="disabled")


# /// BUTTONS ///
# Open image
open_image = Button(
    text="Add Image...",
    command=add_image,
    bg="#7d6b57",
    foreground="#d9d0b4",
    font="bahnschrift 12",
    width=10,
    padx=15,
    highlightcolor="#7d6b57",
)
open_image.grid(column=2, row=0, sticky="E")
# Save as
save_as = Button(
    text="Save as...",
    command=save_image,
    bg="#7d6b57",
    foreground="#d9d0b4",
    font="bahnschrift 10",
    width=10,
    padx=0,
    activebackground="#d9d0b4",
)
save_as.grid(column=3, row=0)
# Create watermark
add_wm = Button(
    text="Add Watermark",
    command=add_watermark,
    bg="#ab9e86",
    foreground="#33362f",
    font="bahnschrift 9",
    highlightcolor="#7d6b57",
    width=15,
    padx=0,
    state="disabled",
)
add_wm.grid(column=4, row=0)
# Remove watermark
rm_wm_btn = Button(
    text="Remove Watermark",
    command=remove_watermark,
    bg="#ab9e86",
    foreground="#33362f",
    font="bahnschrift 9",
    activebackground="#d9d0b4",
    width=15,
    padx=0,
    state="disabled",
)
rm_wm_btn.grid(column=5, row=0)
# Remove text
rm_txt_btn = Button(
    text="Remove Text",
    command=remove_text,
    bg="#ab9e86",
    foreground="#33362f",
    font="bahnschrift 9",
    activebackground="#d9d0b4",
    width=15,
    padx=0,
    state="disabled",
)
rm_txt_btn.grid(column=6, row=0)

# /// WATERMARK AND FONT FEATURES ///
sep_vert_w = ttk.Separator(window, orient="vertical")
sep_vert_w.grid(column=10, row=0, rowspan=15, sticky="NS")
# Color panel
color_panel = Label(
    bg=BOX_COLOR, foreground="#d9d0b4", width=3, borderwidth=2, relief="groove"
)
color_panel.grid(column=12, row=1, columnspan=2, padx=25, sticky="W")
# Color picker
color_picker = Button(
    text="Color",
    command=change_color,
    bg="#666b5e",
    foreground="#d9d0b4",
    font="bahnschrift",
    width=10,
    relief="groove",
)
color_picker.grid(column=11, row=1, columnspan=1, padx=25, sticky="W")
style = ttk.Style()
style.theme_use("alt")
style.configure(
    "TButton",
    background="#666b5e",
    foreground="#d9d0b4",
    font="bahnschrift",
    width=10,
    relief="groove",
)
style.map("TButton", background=[("active", "#666b5e")])
# Font picker
var = Variable(value=fonts)
font_list = Listbox(
    listvariable=var,
    selectmode=tk.EXTENDED,
    bg="#d9d0b4",
    selectbackground="#7d6b57",
    font="Arial 10",
    width=11,
    height=4,
    relief="groove",
)
font_list.grid(column=12, row=2, rowspan=1, sticky="W")
font_list.select_set(0)
scrollbar = Scrollbar(command=font_list.yview, bg="#4d5147", troughcolor="#d9d0b4")
scrollbar.grid(column=12, row=2, rowspan=1, sticky="E")
font_list.configure(yscrollcommand=scrollbar.set)
font_picker = Button(
    text="Change font",
    command=adjust_text,
    bg="#666b5e",
    foreground="#d9d0b4",
    font="bahnschrift",
    width=10,
    relief="groove",
)
font_picker.grid(column=12, row=3, columnspan=1, sticky="W")
# Text box
text_box = Text(height=5, width=12, bg="#d9d0b4")
text_box.grid(column=11, row=2, columnspan=3, padx=25, sticky="W")
# Add text
add_txt_btn = Button(
    width=10,
    text="Add text",
    command=reset_wm_sliders,
    bg="#666b5e",
    foreground="#d9d0b4",
    font="bahnschrift",
    relief="groove",
)
add_txt_btn.grid(column=11, row=3, columnspan=1, padx=25)
# Slider x y label
slider_x_label = Label(
    text="Position:", bg="#4d5147", foreground="#d9d0b4", font="bahnschrift"
)
slider_x_label.grid(column=11, row=4, padx=25, sticky="E")
# Slider x
slider_x = Scale(
    command=lambda event=None: slider_x_changed(event),
    variable=current_x_value,
    bg="#4d5147",
    fg="#d9d0b4",
    troughcolor="#d9d0b4",
    from_=-150,
    to=550,
    orient="horizontal",
    showvalue=False,
)
slider_x.grid(column=12, row=4, sticky="W")
# Slider y
slider_y = Scale(
    command=lambda event=None: slider_y_changed(event),
    variable=current_y_value,
    bg="#4d5147",
    fg="#d9d0b4",
    troughcolor="#d9d0b4",
    from_=-150,
    to=550,
    orient="vertical",
    showvalue=False,
)
slider_y.grid(column=12, row=4, sticky="E")
# Place text button
place_txt_btn = Button(
    text="Stamp",
    command=save_text,
    bg="#666b5e",
    foreground="#d9d0b4",
    font="bahnschrift 10",
    height=1,
    width=10,
    relief="groove",
    state="disabled",
)
place_txt_btn.grid(column=11, row=4, columnspan=2, padx=27, pady=10, sticky="NE")
# Place text button
place_wm_btn = Button(
    text="Stamp",
    command=save_watermark,
    bg="#666b5e",
    foreground="#d9d0b4",
    font="bahnschrift 10",
    height=1,
    width=10,
    relief="groove",
    state="disabled",
)
place_wm_btn.grid(column=11, row=4, columnspan=2, padx=27, pady=10, sticky="SE")
# Size slider label
size_slider_label = Label(
    text="Size:", bg="#4d5147", foreground="#d9d0b4", font="bahnschrift"
)
size_slider_label.grid(column=11, row=5, padx=25, sticky="E")
# Size slider
size_slider = Scale(
    command=size_changed,
    variable=current_size,
    bg="#4d5147",
    fg="#d9d0b4",
    troughcolor="#d9d0b4",
    from_=1,
    to=500,
    orient="horizontal",
)
size_slider.set(60)
size_slider.grid(column=12, row=5, sticky="E")
# Opacity slider label
opacity_slider_label = Label(
    text="Opacity:", bg="#4d5147", foreground="#d9d0b4", font="bahnschrift"
)
opacity_slider_label.grid(column=11, row=6, padx=25, sticky="E")
# Opacity slider
opacity_slider = Scale(
    command=opacity_changed,
    variable=current_opacity_value,
    bg="#4d5147",
    fg="#d9d0b4",
    troughcolor="#d9d0b4",
    from_=0,
    to=255,
    orient="horizontal",
)
opacity_slider.set(255)
opacity_slider.grid(column=12, row=6, sticky="E")
# Padding
padding_1 = Label(bg="#4d5147")
padding_1.grid(column=1, row=0, rowspan=10, padx=30)
padding_2 = Label(bg="#4d5147")
padding_2.grid(column=8, row=0, rowspan=10, padx=30)
padding_3 = Label(bg="#4d5147")
padding_3.grid(column=9, row=0, rowspan=10, padx=50)
# Close button
close_btn = Button(
    text="Save and close",
    command=on_exit,
    bg="#33362f",
    foreground="#d9d0b4",
    font="bahnschrift 12",
    height=2,
    width=20,
)
close_btn.grid(column=11, row=9, columnspan=2, pady=20, sticky="E")

window.mainloop()
if IS_EXIT is False:
    atexit.register(on_exit)
