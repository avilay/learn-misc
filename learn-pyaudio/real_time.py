import wave
import io
import pyaudio
from google.cloud import speech
from google.cloud.speech.encoding import Encoding


CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 16000
RECORD_SECONDS = 60

p = pyaudio.PyAudio()
stream = p.open(format=FORMAT, channels=CHANNELS, rate=RATE, input=True, frames_per_buffer=CHUNK)
print('* recording')
frames = []
for i in range(0, int(RATE/CHUNK * RECORD_SECONDS)):
    data = stream.read(CHUNK)
    frames.append(data)

print('* done recording')
stream.stop_stream()
stream.close()
p.terminate()

bytestream = io.BytesIO()
wf = wave.open(bytestream, 'wb')
wf.setnchannels(CHANNELS)
wf.setsampwidth(p.get_sample_size(FORMAT))
wf.setframerate(RATE)
wf.writeframes(b''.join(frames))
wf.close()

client = speech.Client()
s = client.sample(bytestream.getvalue(), None, encoding=Encoding.LINEAR16, sample_rate=16000)

texts = client.sync_recognize(s)
for text in texts:
    print('\ntranscript: {}'.format(text['transcript']))
    print('confidence: {}'.format(text['confidence']))

