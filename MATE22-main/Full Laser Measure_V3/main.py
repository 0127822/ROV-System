import cv2 ,keyboard,os
import numpy as np
import tkinter as tk
from tkinter import ttk
from utiles import *
from dvr_class import *
mouse = Mouse()
wind = tk.Tk()
camera_number_entry_STRVAR = tk.StringVar()
camera_number_entry_STRVAR.set("3")
list_of_diver_len_to_be_sumed = []
real_diagonal = 5.5 # the real distance between the two laser points

real_width = 17 # If you want to use warping in cm
real_height = 22 # If you want to use warping in cm
dvr_link = 'http://169.254.108.159' # Our Dvr link
user_name = 'admin' # The user name of Our Dvr
password = 'admin000' # The password of Our Dvr


scale = 1 # Image scale if too big for the first program -----> not of warping
ratio = None # To check if we get the ratio or not for tkinter app
cap = DvrCamera(dvr_link,user_name,password) # Only use this when you are connected to the ROV by the Ethernet Caple
_,img = cap.read(camera_number = int(camera_number_entry_STRVAR.get())) #Only use this with the ROV camera
img = rescale_frame(img,scale)
def program1_specify_points_of_laser():
    """
    This function is only made to be controlled by tkinter button
    to use this function click on the button named "Laser points    .    ."
    here you will have a two screens
    """
    cv2.destroyAllWindows() # Here we just destroy all windows if program2 was having any window
    global img,ratio # Making them global can control the second program without any errors

    point_indx = 0 #just for counting our clicks and it's not important

    # Program for measuring the distance with floor by the diagonal of a ceramic to find a ration
    os.system("cls") # clear any printed output on the screen
    print("###program1 specify ratio###")
    list_of_diagonal_points = [] # list of the two point laser in pixels
    while cv2.waitKey(1) != ord("q"): # if you prees Q it will exit this program and go to the menu screen
        _,frame = cap.read(int(camera_number_entry_STRVAR.get()))
        frame = rescale_frame(frame,scale) #Rescaling the frame if it's so big

        if keyboard.is_pressed("n"): # if "n" is pressed save this screenshot and display it
            img = frame.copy()
        img_c = img.copy() # here just to refresh the screen to draw objects on it without being sticked

        if mouse.pulse == 1 and len(list_of_diagonal_points) <2 :# Checking if the pulse increased by one and the length of list_of_diagonal_points is less than two to not add more laser points as they always be two
            if  mouse.X < img.shape[1]: # just test if mouse clicks the left screen
                point_indx +=1 # increase the counter by one ,not important
                print(f"clicked point {point_indx}",mouse.X)
                list_of_diagonal_points.append(mouse()) # append this coor to this list
                mouse.pulse += 1 #increase pulse by one to go to line_drawing mode
            else:
                mouse.pulse = 0 # if the click is in the right screen reduse mouse pulse to zero as this screen is the frame shoing screen we should'nt draw on it

        elif mouse.pulse ==2 : #if the line_drawing mode is one draw our line from the saved point above to the mouse location now
                if len(list_of_diagonal_points) >0 : # Checking if there is any point in this list
                    if list_of_diagonal_points[0][0]< img.shape[1]: # Checking if this point is in the first image
                        cv2.line(img_c,list_of_diagonal_points[0],mouse(),(0,0,255),1) # the line is being drawn here
                else:
                    mouse.pulse = 0 # If any one of this conditions falls then restart the pulse counter
        elif mouse.pulse == 3 : # Here the save for the point in the list to get the ratio if the letter "s" is pressed
            list_of_diagonal_points.append(mouse()) # Here the append
            mouse.pulse =0 # reduce mouse pulse to be zero to accept the other point and do all this again

        if keyboard.is_pressed("c"): # If this is pressed you will reset the pulse to be zero and delete all the selected points
            # this method can be used if you accidently press 'n' and refresh your frame saved or when you clicked all your laser points wrong
            list_of_diagonal_points = [] # Update list to be empty
            mouse.pulse = 0 # Update the click to be zero

        if keyboard.is_pressed("s") and len(list_of_diagonal_points) > 1 : # Here we save our image and our ratio and it should be clicked to run program two
            x1 = list_of_diagonal_points[0][0] # COOR ->X1
            y1 = list_of_diagonal_points[0][1] # COOR ->Y1
            x2 = list_of_diagonal_points[1][0] # COOR ->X2
            y2 = list_of_diagonal_points[1][1] # COOR ->Y2
            diagonal = ( (x2-x1)**2 + (y2-y1)**2 )**0.5 # calculate distance between thos two points in pixels
            ratio = (real_diagonal / diagonal) # calculate the ratio of this surface
            info_label.config(text = "Choose points to measure",fg = "green") # Update this label to tell user that he can use program 2
            wind.update()
            print(f"diagonal = {diagonal} , ratio = {ratio}")
            cv2.destroyAllWindows() # Destroy all windows to be able to see and clean the real screen
            break



        if len(list_of_diagonal_points) ==2:# Here we just make sure to not add any point to the list
            mouse.pulse = 0

        if mouse.Right ==1: # Here we remove only the last point -> UNDO
            if len(list_of_diagonal_points) ==2:
                mouse.pulse = 2 # test if in insert mode to return it
            else:
                mouse.pulse = 0
            mouse.Right = 0
            try:
                list_of_diagonal_points.pop(-1) # this try to check if no index error if list kength is smaller than 0
            except IndexError:
                print("error in index")
        draw_points(list_of_diagonal_points,img_c) # draw the points on screen :: a very basic function i made

        Horizontal_concatinate = np.concatenate((img_c,frame),axis = 1) # concatinat thos images to be in the same screen
        cv2.imshow("frame to save",Horizontal_concatinate) # Show this concatinated
        mouse.event("frame to save") #Handeling mouse events with this class method
    cv2.destroyAllWindows() # Destroy all windows to make sure we are fast and clean sreen

def specify_your_points_to_measure():
    cv2.destroyAllWindows()
    if ratio is None: # Test if the ratio is'nt identified yet don't run program 2
        info_label.config(text = "Choose Laser Points First",fg = "red") # update this label with this message
        wind.update()
        return None # returning here only for exit this function
    print(real_diagonal)
    mouse.pulse = 0 # Here we make sure resting all program1 faults
    mouse.Right = 0 # Here we make sure resting all program1 faults
    point_indx = 0 # Here we make sure resting all program1 faults
    list_of_points = [] # Here the list of points selected like "list_of_diagonal_points" in the first program
    os.system("cls") # clear any printed output on the screen
    print("###program2 measure distance###")
    measured_objects = [] # a new points to be measured list
    run_porgram2 = True # just an exit loop confirm :)
    while run_porgram2:
        cv2.waitKey(1)
        if keyboard.is_pressed("q"):
            run_porgram2 = False
            cv2.destroyAllWindows()
            break
        img_c = img.copy() # refreshing screen
        # ALL THE LOGIC IS LIKE THE FIRST FUNCTION-----------------------
        if mouse.pulse == 1 and len(list_of_points) <2:
            list_of_points.append(mouse())
            mouse.pulse += 1
            point_indx +=1
            print(f"clicked point {point_indx}")
        elif mouse.pulse ==2:
            cv2.line(img_c,list_of_points[0],mouse(),(0,0,255),1)
        elif mouse.pulse ==3:
            list_of_points.append(mouse())
            x1 = list_of_points[0][0]
            y1 = list_of_points[0][1]
            x2 = list_of_points[1][0]
            y2 = list_of_points[1][1]
            length = [(( (x2-x1)**2 + (y2-y1)**2 )**0.5) * ratio,(x1,y1),(x2,y2)]
            measured_objects.append(length)
            list_of_diver_len_to_be_sumed.append((( (x2-x1)**2 + (y2-y1)**2 )**0.5) * ratio)
            sum_label.config(text = f"sum : {list_of_diver_len_to_be_sumed}")
            wind.update()
            list_of_points = []
            mouse.pulse = 0
        if mouse.Right == 1:
            if len(list_of_diver_len_to_be_sumed) > 0 :
                list_of_diver_len_to_be_sumed.pop(-1)
                sum_label.config(text = f"sum : {list_of_diver_len_to_be_sumed}")
                wind.update()
            if len(measured_objects) > 0:
                measured_objects.pop(-1)
            mouse.Right =0

        for obj in measured_objects:
            cv2.line(img_c,obj[1],obj[2],(0,0,255),1)
            cv2.putText(img_c,str(round(obj[0],4)),obj[1],cv2.FONT_HERSHEY_PLAIN,2,(0,255,0),2)
        draw_points(list_of_points,img_c)
        cv2.imshow("final measure",img_c)
        mouse.event("final measure")

globalized_warped_list = []
def warp_image_program():
    global globalized_warped_list
    cv2.destroyAllWindows()
    mouse = Mouse()
    if ratio is None: # Test if the ratio is'nt identified yet don't run program 2
        info_label.config(text = "Choose Laser Points First",fg = "red") # update this label with this message
        wind.update()
        return None # returning here only for exit this function
    run_porgram3 = True
    points_to_warped = []
    while run_porgram3:
        cv2.waitKey(1)
        if keyboard.is_pressed("q"):
            run_porgram3 = False
            cv2.destroyAllWindows()
            break
        img_W = img.copy()

        if mouse.pulse > 0 and len(points_to_warped) < 4 :
            points_to_warped.append(mouse())
            mouse.pulse = 0
        if mouse.Right == 1 and len(points_to_warped) > 0 :
            points_to_warped.pop(-1)
            mouse.Right=0
        if keyboard.is_pressed("s") and len(points_to_warped) ==4:
            globalized_warped_list = points_to_warped
            cv2.destroyAllWindows()
            break
        draw_points(points_to_warped,img_W)
        cv2.imshow("choose points to warp",img_W)
        mouse.event("choose points to warp")

def show_warped_image():
    if len(globalized_warped_list) != 4:
        warp_message_label.config(text = "ERROR In your points!!",fg="red")
        return None
    elif width_entry_STRVAR.get() == "" or height_entry_STRVAR.get() =="" or scale_entry_STRVAR.get() == "":
        warp_message_label.config(text = "ERROR In your W,H,S !!",fg="red")
        return None
    else:
        warp_message_label.config(text = "",fg="green")
    try:
        width = int(width_entry_STRVAR.get()) * 100 # to be in milli * 10
        height = int(height_entry_STRVAR.get()) * 100  # to be in milli * 10
        scale_from = float(scale_entry_STRVAR.get())
    except:
        warp_message_label.config(text = "ERROR In your W,H,S !!",fg="red")
        return None
    list_of_points = []
    measured_objects = []
    mouse = Mouse()
    center_warp = True
    if center_warp:
        points = PointCalibaration()
        points.solve_points(globalized_warped_list[0],globalized_warped_list[1],globalized_warped_list[2],globalized_warped_list[3])
        IMG_WARPED = warp_image(points.wp,img,points.dims[0],points.dims[1])
    else:
        IMG_WARPED = warp_image(globalized_warped_list,img,width,height)
    IMG_WARPED = rescale_frame(IMG_WARPED,scale_from)
    run_porgram4 = True
    while run_porgram4:
        cv2.waitKey(1)
        if keyboard.is_pressed("q"):
            run_porgram4 = False
            cv2.destroyAllWindows()
            break
        img_warped_c = IMG_WARPED.copy()
        if mouse.pulse == 1 and len(list_of_points) <2:
            list_of_points.append(mouse())
            mouse.pulse += 1
        elif mouse.pulse ==2:
            cv2.line(img_warped_c,list_of_points[0],mouse(),(0,0,255),1)
        elif mouse.pulse ==3:
            list_of_points.append(mouse())
            x1 = list_of_points[0][0]
            y1 = list_of_points[0][1]
            x2 = list_of_points[1][0]
            y2 = list_of_points[1][1]
            length = [(( (x2-x1)**2 + (y2-y1)**2 )**0.5) / (100 * scale_from) ,(x1,y1),(x2,y2)]
            measured_objects.append(length)
            list_of_diver_len_to_be_sumed.append((( (x2-x1)**2 + (y2-y1)**2 )**0.5) / (100 * scale_from) )
            sum_label.config(text = f"sum : {list_of_diver_len_to_be_sumed}")
            wind.update()
            list_of_points = []
            mouse.pulse = 0
        if mouse.Right == 1:
            if len(list_of_diver_len_to_be_sumed) > 0 :
                list_of_diver_len_to_be_sumed.pop(-1)
                sum_label.config(text = f"sum : {list_of_diver_len_to_be_sumed}")
                wind.update()
            if len(measured_objects) > 0:
                measured_objects.pop(-1)
            mouse.Right =0

        for obj in measured_objects:
            cv2.line(img_warped_c,obj[1],obj[2],(0,0,255),1)
            cv2.putText(img_warped_c,str(round(obj[0],4)),obj[1],cv2.FONT_HERSHEY_PLAIN,2,(0,255,0),2)
        draw_points(list_of_points,img_warped_c)
        cv2.imshow("final measure",img_warped_c)
        mouse.event("final measure")
# Tkinter GUI APP only for drawing buttons and label and controlling my logic above

NOTEBOOK = ttk.Notebook(wind)
NOTEBOOK.pack()
wind.geometry("450x230")
# Program frame buttons
program_frame = tk.Frame(wind,width = 250,height = 190)
program_frame.pack()

program_one_button = tk.Button(program_frame,width = 20,text = "Laser points    .    ." , font = ("BOLD",15),command = program1_specify_points_of_laser,bg = "grey")
program_one_button.pack()
program_two_button = tk.Button(program_frame,width = 20,text = "choose points to measure" , font = ("BOLD",15),command = specify_your_points_to_measure,bg = "grey")
program_two_button.pack()
camera_number_entry = tk.Entry(program_frame,width =5,textvariable = camera_number_entry_STRVAR,font = ("BOLD",25),bg="#aaaaaa")
camera_number_entry.pack()
info_label = tk.Label(wind,text = "Choose Laser points first",font = ("BOLD",15),bg = "white")
info_label.pack()

#editing frame to edit the ratio
editing_frame = tk.Frame(wind,width = 250,height = 190)
editing_frame.pack()
def save_new_ratio():
    # This function inserts a new diagonal
    global real_diagonal,ratio
    if ratio is not None:
        ratio = (ratio / real_diagonal) * float(ratio_entry_STRVAR.get())
    real_diagonal = float(ratio_entry_STRVAR.get())
    confirm_real_diagonal.config(text = "real diagonal : " + ratio_entry_STRVAR.get())

def sum_command():
    sum_label.config(text = f"{list_of_diver_len_to_be_sumed},\n final length: {sum(list_of_diver_len_to_be_sumed)}")
    print(list_of_diver_len_to_be_sumed,"\n","final length : ",sum(list_of_diver_len_to_be_sumed))

ratio_entry_STRVAR = tk.StringVar()
width_entry_STRVAR = tk.StringVar()
height_entry_STRVAR = tk.StringVar()
scale_entry_STRVAR = tk.StringVar()
width_entry_STRVAR.set(str(real_width))
height_entry_STRVAR.set(str(real_height))
scale_entry_STRVAR.set("0.3")
ratio_entry = tk.Entry(editing_frame,textvariable = ratio_entry_STRVAR,font = ("BOLD",25),bg="#aaaaaa")
ratio_entry.pack()
ratio_entry_STRVAR.set(real_diagonal)
ratio_button = tk.Button(editing_frame,width = 20,text = "save",font = ("BOLD",15),bg = "grey",command = save_new_ratio)
ratio_button.pack()
sum_button = tk.Button(editing_frame,width = 20,text = "sum of lengths",font = ("BOLD",9),bg = "grey",command = sum_command)
sum_button.pack()

confirm_real_diagonal = tk.Label(editing_frame,text = "real diagonal : " + ratio_entry_STRVAR.get(),font = ("BOLD",15))
confirm_real_diagonal.pack()

warping_frame = tk.Frame(wind,width = 250,height = 190)
warping_frame.pack()

warp_image_button = tk.Button(warping_frame,width = 20,text = "Warp points" , font = ("BOLD",15),bg = "grey",command = warp_image_program)
warp_image_button.pack()

width_height_frame = tk.Frame(warping_frame)
width_height_frame.pack()

width_entry = tk.Entry(width_height_frame,textvariable = width_entry_STRVAR,font = ("BOLD",15),width = 5,bg="#aaaaaa")
width_entry.grid(row = 0,column=0)

xlabel = tk.Label(width_height_frame,text = "X",font = ("BOLD",15) )
xlabel.grid(row = 0,column=1)

height_entry = tk.Entry(width_height_frame,textvariable = height_entry_STRVAR,font = ("BOLD",15),width = 5,bg="#aaaaaa")
height_entry.grid(row = 0,column=2)

scale_label = tk.Label(width_height_frame,text = " S:",font = ("BOLD",15) )
scale_label.grid(row = 0,column=3)

scale_entry = tk.Entry(width_height_frame,textvariable = scale_entry_STRVAR,font = ("BOLD",15),width = 4,bg="#aaaaaa")
scale_entry.grid(row = 0,column=4)

show_warp_image_button = tk.Button(warping_frame,width = 20,text = "Show warp" , font = ("BOLD",15),bg = "grey",command = show_warped_image)
show_warp_image_button.pack()

warp_message_label = tk.Label(warping_frame,text = "",font = ("BOLD",15) )
warp_message_label.pack()

NOTEBOOK.add(program_frame,text="Mode")
NOTEBOOK.add(editing_frame,text="edit")
NOTEBOOK.add(warping_frame,text="Warp")

sum_label = tk.Label(wind,text ="")
sum_label.pack()
wind.mainloop()
