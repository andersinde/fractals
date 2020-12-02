import numpy as np
import matplotlib.pyplot as plt

def getMatrixFromPPM(filename):
    f = open(filename, "r")
    line0 = f.readline()
    line1 = f.readline().split(" ")
    width, height  = int(line1[0]), int(line1[1])
    ret = np.zeros((height, width))

    for x in range(height):
        for y in range(width):
            val = float(f.readline().split(" ")[0])%255
            ret[x][y] = val
    return ret

def makeanimation():
    from cv2 import VideoWriter, VideoWriter_fourcc
    import glob

    (height, width) = np.shape(getMatrixFromPPM("frames/0.ppm"))
    frames = len(glob.glob("./frames/*.ppm"))
    FPS = 60

    frame = np.zeros((height, width, 3), dtype=np.uint8) #black frame
    #frame = np.full((height, width, 3), 255, dtype=np.uint8) #white frame

    fourcc = VideoWriter_fourcc(*'mp4v')
    video = VideoWriter('./fractal.mp4', fourcc, float(FPS), (width, height))


    for i in range(frames):
        matrix = getMatrixFromPPM(f"./frames/{i}.ppm")
        np.size(height)
        #for x in range(height):
            #for y in range(width):
                #c = matrix[x][y]
                #frame[x, y] = [c, c, c]
        f = open(f"./frames/{i}.ppm", "r")
        line0 = f.readline()
        line1 = f.readline()

        for x in range(height):
            for y in range(width):
                c = float(f.readline().split(" ")[0])%256
                frame[x, y] = [c, c, c]
        video.write(frame)
        print(f"Writing frame {i}")

    video.release()
    print("done")

def main():
    #filename = "frames/0.ppm"
    #matrix = getMatrixFromPPM(filename)
    #plt.imshow(matrix)
    #plt.show()
    makeanimation()


main()

