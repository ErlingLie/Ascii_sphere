import time
import numpy as np

frames = np.load("secret.npy")
while True:
    for frame in frames:
        print("\x1b[H")
        for row in frame:
            r = "".join(row)
            print(r)
        time.sleep(1/16)