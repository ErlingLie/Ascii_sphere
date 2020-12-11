from PIL import Image, ImageSequence
import numpy as np
import time
im = Image.open("tenor.gif")
while True:
    for frame in ImageSequence.Iterator(im):
        frame = frame.convert("L")
        frame = frame.resize((124,100))
        frame = np.array(frame).astype(float)
        frame /= 255
        frame *= 12
        frame = frame.astype(int)
        frame = np.array(list(".,-~:;=!*#$@"))[frame]
        print("\x1b[H")
        for row in frame:
                r = "".join(row)
                print(r)
        time.sleep(1/16)