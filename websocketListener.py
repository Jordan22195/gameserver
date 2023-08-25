import asyncio
import multiprocessing
import os
import queue
import signal
import sys
import websockets
import time
import threading
from asyncio.events import AbstractEventLoop

# Dictionary to store connected clients
connected_clients = {}


def pipe_input():
    print("enter send")
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    while True:
        for websocket in connected_clients:
            print("socket")
            with open('pipe1') as f:   # add `rb` for binary mode
                print("open pipe")
                # line-by-line read
                for line in f:
                    print ("read line")
                    print(line)
                    loop.run_until_complete(send_message(websocket, line))
                    print(f"Sent: {line}")
        print("sleep")
        time.sleep(1)
        

async def send_message(websocket, message):
        print ('wait tx')
        await websocket.send(message)
        print(f"sent: {message}")


async def client_handler(websocket, path):
    # Add client to dictionary
    connected_clients[websocket] = path
    print(f"Client connected: {path}")
    try:
        async for message in websocket:
            print(f"Received from {path}: {message}")
            
            # Echo the message back to the client
            await websocket.send(f"You said: {message}")

    except websockets.exceptions.ConnectionClosed:
        pass

    # Remove client from dictionary when disconnected
    del connected_clients[websocket]
    print(f"Client disconnected: {path}")



async def main(func1):
    await asyncio.gather(func1)

if __name__ == "__main__":

   

    # Start WebSocket server
    start_server = websockets.serve(client_handler, "0.0.0.0", 12345)

    try:
        t1 = threading.Thread(target=pipe_input)
        t1.start()
        #asyncio.get_event_loop().run_until_complete(main(send_message()))
        #asyncio.get_event_loop().create_task(send_message())

        asyncio.get_event_loop().run_until_complete(start_server)
        print("start server")
        asyncio.get_event_loop().run_forever()

    except KeyboardInterrupt:
        print("WebSocket server terminated.")
        sys.exit(0)





