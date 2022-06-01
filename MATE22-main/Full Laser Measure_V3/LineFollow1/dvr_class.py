import cv2
import requests
import numpy as np
from hikvisionapi import Client

dvr_link = 'http://169.254.108.159'
user_name = 'admin'
password = 'admin000'
class DvrCamera:
    def __init__(self,link,user_name,password):
        self.cam = Client(link, user_name, password)

    def read(self,camera_number,ch_size = None):
        vid = self.cam.Streaming.channels[camera_number * 100].picture(method ='get', type = 'opaque_data') # Channel like 102
        bytes = b''
        for chunk in vid.iter_content(chunk_size=ch_size):
                bytes += chunk
                a = bytes.find(b'\xff\xd8')
                b = bytes.find(b'\xff\xd9')
                if a != -1 and b != -1:
                    jpg = bytes[a:b+2]
                    bytes = bytes[b+2:]
                    frame = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)
                    return [None,frame]
if __name__ == "__main__":
    cap = DvrCamera(dvr_link,user_name,password)
    print("Hello Code !")
    while cv2.waitKey(1) != ord("d"):
        _,frame1 = cap.read(3,None)
        cv2.imshow("frameNone",frame1)
