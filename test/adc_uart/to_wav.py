import csv
from scipy.io.wavfile import write
import numpy as np

data = []
with open('op.csv', newline='') as f:
    reader = csv.reader(f)
    data = list(reader)

pcm_data = []
for i in range(len(data[0])):
    if data[0][i] != '':
        pcm_data.append(int(data[0][i]))

npa = np.asarray(pcm_data, dtype=np.uint8)
write("example.wav", 48000, npa.astype(np.uint8))

