import csv
from scipy.io.wavfile import write
import numpy as np

MAX_12_BITS = 4096
MAX_INT16 = 32767

def covert_to_int16(_data):
    frac = _data / MAX_12_BITS
    op_data = -MAX_INT16 + frac * (MAX_INT16 * 2)
    return op_data

data = []
with open('op.csv', newline='') as f:
    reader = csv.reader(f)
    data = list(reader)

pcm_data = []
for i in range(len(data[0])):
    if data[0][i] != '' and int(data[0][i]) > 0 and int(data[0][i]) < 4096:
        pcm_data.append(covert_to_int16(int(data[0][i])))
    else:
        pcm_data.append(covert_to_int16(2048))

npa = np.asarray(pcm_data, dtype=np.int16)
write("example.wav", 40000, npa.astype(np.int16))


