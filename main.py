import tkinter as tk
import time
import serial
import serial.tools.list_ports
from tkinter import ttk
from tkinter import *
from PIL import ImageTk, Image
import tk_tools

ports = list(serial.tools.list_ports.comports())
ser = serial.Serial(ports[0][0], 9600, timeout=4)

# Fullscreen
root = Tk()
# root.overrideredirect(True)
# root.overrideredirect(False)
root.geometry("{0}x{1}+0+0".format(root.winfo_screenwidth(), root.winfo_screenheight()))
root.attributes("-fullscreen", True)
root.configure(background='#F0F8FF')
root.config(cursor="none")
root.title('Information Window')

# Logos
imgfile1 = Image.open("/home/pi/Desktop/logo1.png")
imgfile1 = imgfile1.resize((300,100))
img1 = ImageTk.PhotoImage(imgfile1)
img1label = Label(root, image=img1)
img1label.image=img1
img1label.place(x=100,y=50)

imgfile2 = Image.open("/home/pi/Desktop/logo2.jpg")
imgfile2 = imgfile2.resize((280,100))
img2 = ImageTk.PhotoImage(imgfile2)
img2label = Label(root, image=img2)
img2label.image=img2
img2label.place(x=900,y=50)


imgfile3 = Image.open("/home/pi/Desktop/logo2.jpeg")
imgfile3 = imgfile3.resize((250,250))
img3 = ImageTk.PhotoImage(imgfile3)
img3label = Label(root, image=img3)
img3label.image=img2
img3label.place(x=(root.winfo_screenwidth()/2)-125,y=50)

# Labels
textInput=""

current_temp1 = tk.StringVar()
current_temp2 = tk.StringVar()
current_level = tk.StringVar()
current_time = tk.StringVar()

phGauge = tk_tools.Gauge(root,max_value = 14, min_value = 0,
                         label = "Ph", divisions = 14,
                         yellow_low=42, yellow=57,
                         red_low=35, red=64,
                         width=300, height=200,  bg="#F0F8FF")
phGauge.place(x=150,y=300)
phGauge.set_value(7.5)

tdsGauge = tk_tools.Gauge(root,max_value = 1000, min_value = 0,
                         label = "TDS", divisions = 20, unit="PPM",
                         yellow=40,
                         red=50,
                         width=300, height=200,  bg="#F0F8FF")
tdsGauge.place(x=800,y=300)
tdsGauge.set_value(150)

def update_status():
    ser.reset_input_buffer()
    ser.flush()
    textInput = str(ser.readline())
    ph=   ""
    tds=  ""
    temp1= ""
    temp2= ""
    level=""
    timen = ""
    print(textInput)
    
    for i in range(0,len(textInput)-2):
        if(textInput[i]=="P" and textInput[i+1]=="H"):  #PH
            j=i+4
            while(textInput[j]!=" "):
                ph=ph+textInput[j]
                j=j+1
            phGauge.set_value(float(ph))
                        
        if(textInput[i]=="T" and textInput[i+1]=="D"):  # TDS
            j=i+5
            while(textInput[j]!=" "):
                tds=tds+textInput[j]
                j=j+1
            tdsGauge.set_value(float(tds))
        if(textInput[i]=="W" and textInput[i+1]=="a"):  # WaterLevel
            j=i+7
            while(textInput[j]!=" "):
                level=level+textInput[j]
                j=j+1
            level=level+" L"
            
        if(textInput[i]=="T" and textInput[i+1]=="e" and textInput[i+4]=="1"):  # Temperature
            j=i+7
            while(textInput[j]!=" "):
                temp1=temp1+textInput[j]
                j=j+1
            temp1=temp1+chr(176)
            
        if(textInput[i]=="T" and textInput[i+1]=="e" and textInput[i+4]=="2"):  # Temperature
            j=i+7
            while(textInput[j]!=" "):
                temp2=temp2+textInput[j]
                j=j+1
            temp2=temp2+chr(176)            
            
    current_temp1.set(temp1)
    current_temp2.set(temp2)
    current_level.set(level)
    timen = time.strftime("%H:%M")
    current_time.set(timen)
    root.after(4000,update_status)

# This is the section of code which creates the a label
lb1=Label(root, textvariable=current_time, bg='#F0F8FF', font=('arial', 24, 'normal')).place(relx=0.93, rely=0.06)
lb1=Label(root, text="Water Kiosk ", bg='#F0F8FF', font=('arial', 32, 'normal')).place(relx=.5, y=root.winfo_screenheight()*0.45, anchor="center")

lb3=Label(root, text="Cold Temp: ", bg='#F0F8FF', font=('arial', 32, 'normal')).place(x=root.winfo_screenwidth()/6, y=root.winfo_screenheight()*6/8)
lb4=Label(root, text="Warm Temp: ", bg='#F0F8FF', font=('arial', 32, 'normal')).place(x=root.winfo_screenwidth()/6, y=root.winfo_screenheight()*7/8)
lb5=Label(root, text="Water Level: ", bg='#F0F8FF', font=('arial', 32, 'normal')).place(x=root.winfo_screenwidth()*3.5/6, y=root.winfo_screenheight()*6/8)

lb6=Label(root, text="Ph", bg='#F0F8FF', font=('arial', 32, 'normal')).place(x=150, y=550)
lb7=Label(root, text="TDS", bg='#F0F8FF', font=('arial', 32, 'normal')).place(x=800, y=550)

lb33=Label(root, textvariable=current_temp1, bg='#F0F8FF', font=('arial', 32, 'normal')).place(x=root.winfo_screenwidth()*2.5/6, y=root.winfo_screenheight()*6/8)
lb333=Label(root, textvariable=current_temp2, bg='#F0F8FF', font=('arial', 32, 'normal')).place(x=root.winfo_screenwidth()*2.5/6, y=root.winfo_screenheight()*7/8)
lb44=Label(root, textvariable=current_level, bg='#F0F8FF', font=('arial', 32, 'normal')).place(x=root.winfo_screenwidth()*5/6, y=root.winfo_screenheight()*6/8)

root.bind("<Escape>", lambda event:root.destroy())
root.after(4000,update_status)
root.mainloop()

