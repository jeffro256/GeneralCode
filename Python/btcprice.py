#!/Library/Frameworks/Python.framework/Versions/3.4/bin/python3

from tkinter import *
from urllib.request import urlopen
import json

bought_btc = [list(map(float, x.split())) for x in open("btc_transactions.txt").read().strip().split('\n')]

mined_groestl = 0.2

w = 200
h = 100
root = Tk()
root.geometry(str(w)+'x'+str(h))
root.resizable(False, False)
root.attributes('-topmost', True)
pricel = Label(root, text="--")
pricel.place(x=w/2, y=25, anchor="center")
grsl = Label(root, text="--")
grsl.place(x=w/2, y=50, anchor="center")
rot = Label(root, text="--")
rot.place(x=w/2, y=75, anchor="center")

def refreshprice():
    try:
        btcdata = urlopen("https://api.coindesk.com/v1/bpi/currentprice.json", timeout=9).read().decode()
        btcjson = json.loads(btcdata)

        groestldata = urlopen("https://bittrex.com/api/v1.1/public/getmarketsummary?market=btc-grs").read().decode()
        groestljson = json.loads(groestldata)

        a = groestljson['result'][0]['Last']

        price = float(btcjson['bpi']['USD']['rate'].replace(',', ''))
        grate = float(groestljson['result'][0]['Last'])

        prices = "BTC Current: $%.2f" % price
        grss = "GRS Current: %.2f mmBTC" % (grate * 10**6)

        bought_price = sum([q*p for q, p in bought_btc])
        selling_price = sum([x[0] for x in bought_btc]) * price
        rotd = selling_price - bought_price

        rots = "ROI: " + ('-$' if rotd < 0 else '$') + '%.2f' % abs(rotd)
    except:
        prices = "BTC Current: --"
        rots = "ROI: --"
        grss = "GRS Current: --"

    pricel.config(text=prices)
    rot.config(text=rots)
    grsl.config(text=grss)
    pricel.pack()
    grsl.pack()
    rot.pack()
    root.after(10000, refreshprice)

root.after(0, refreshprice)
root.mainloop()
