import asyncio
import multiprocessing
import os
import queue
import signal
import sys
import websockets
import time

# IPC message queue


async def send_message(websocket):
    global ipc_queue
    while True:
        
        print("ipc get")
        with open('pipe1') as f:   # add `rb` for binary mode
            # line-by-line read
            for line in f:
                print(line)
                await websocket.send(line)
                print(f"Sent: {line}")
        time.sleep(1)

async def receive_message(websocket):
    message = await websocket.recv()
    print(f"Received: {message}")


# WebSocket server
async def websocket_server(websocket, path):
    print("go")
    await asyncio.gather(
        send_message(websocket),
        receive_message(websocket)
    )


if __name__ == "__main__":


    # Start WebSocket server
    start_server = websockets.serve(websocket_server, "0.0.0.0", 12345)

    try:
        asyncio.get_event_loop().run_until_complete(start_server)
        asyncio.get_event_loop().run_forever()
    except KeyboardInterrupt:
        ipc_process.terminate()
        ipc_process.join()
        print("WebSocket server terminated.")
        sys.exit(0)
