import webiopi
...
HOUR_ON = 8
HOUR_OFF = 18
...
def setup():
...
def loop():
...
def destroy():
...

@webiopi.macro
def getLightHours():
    return "%d;%d" % (HOUR_ON, HOUR_OFF)

@webiopi.macro
def setLightHours(on, off):
    global HOUR_ON, HOUR_OFF
    HOUR_ON = int(on)
    HOUR_OFF = int(off)
    return getLightHours()