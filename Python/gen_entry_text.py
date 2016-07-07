import random
import string
from tkinter import *

#function which generates ids
def gen():
  return random.choice(string.ascii_letters + string.digits)

entryText.set('00000001008%s111%s1%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s' % (gen(), gen(),gen(), gen(),gen(),gen(),gen(),gen(),gen(),gen(),gen(),gen(),gen(),gen(), gen(), gen(),gen()))
#main  Window    
window = Tk()
#size of the window
window.geometry("500x300")

#title of the window 
window.title("TestTest")

#Entry Text 
entryText= StringVar(window)
#button
botton = Button(window, text="Generate Ids",command=gen).place(x=263,y=160)
#textfield
textbox = Entry(window, textvariable=entryText).place(x=260,y=100)
