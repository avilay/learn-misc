import time
from google.cloud import speech
from google.cloud.speech.encoding import Encoding


client = speech.Client()

with open('linear.wav', 'rb') as f:
    data = f.read()

s = client.sample(data, None, encoding=Encoding.LINEAR16, sample_rate=16000)

# operation = client.async_recognize(s)
# retry_count = 100
# while retry_count > 0 and not operation.complete:
#     retry_count -= 1
#     time.sleep(10)
#     operation.poll()
# print('Operation is complete {}'.format(operation.complete))
# for result in operation.results:
#     print(result.transcript)


texts = client.sync_recognize(s)
for text in texts:
    print('\ntranscript: {}'.format(text['transcript']))
    print('confidence: {}'.format(text['confidence']))
