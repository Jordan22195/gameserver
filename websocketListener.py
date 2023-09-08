import asyncio
import multiprocessing
import os
import queue
import signal
import sys
import websockets
import time
import threading
import socket
import json

from asyncio.events import AbstractEventLoop

# Dictionary to store connected clients
connected_clients = {}
toServerFifo = 0
fromServerFifo = 0



def receive_udp_from_gameServer_and_forward_to_client():
    print("try bind")
    sockfd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sockfd.bind(("0.0.0.0", 50005))
   # rxSocketAddress = ('0.0.0.0', 50005)
    print("bind success")
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    while True:
        
        print("wating for message from gameserver")
        #get payload size
        sizeBuff, rxSocketAddress = sockfd.recvfrom(4, socket.MSG_PEEK)
        bufferSize = int.from_bytes(sizeBuff, "little")
        if (bufferSize <= 0):
            continue
        bufferSize = bufferSize + 4
        print(f'bufferSize: {bufferSize}')
        dataBuff, rxSocketAddress = sockfd.recvfrom(bufferSize)
        print(dataBuff)
        received_message = dataBuff[4:].decode()
        print(f"Received string from gameServer: {received_message}")
        print(f"Received data from gameServer: {dataBuff[4:]}")
        print(f"data len: {len(dataBuff)}")

        clientName = json.loads(received_message)['clientName']
        if(connected_clients.get(clientName, "")!= ""): 
            loop.run_until_complete(send_message(connected_clients.get(clientName, ""), received_message))
            print(f"Sent gameServer packet to client: {clientName}")
        else:
            print(f'Error client {clientName} not found')



def send_udp_to_gameServer(message):
    txSocketAddress = ('0.0.0.0', 50004)
    sockfd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    header = len(message.encode()).to_bytes(4, 'little')
    payload = message.encode()
    dataPacket = header + payload
    sockfd.sendto(bytes(dataPacket), txSocketAddress)
    print(f'sent {dataPacket}')




def get_nth_item(input_string, n):
    items = input_string.strip().split('\n')
    if n >= 0 and n < len(items):
        return items[n].strip()
    else:
        return None


    

async def send_message(websocket, message):
        print ('wait tx')
        await websocket.send(message)
        print(f"sent: {message}")


async def client_handler(websocket, path):
    # Add client to dictionary
    
    print(f"Client connected: {path}")
    try:
        async for message in websocket:
            clientName = get_nth_item(message, 0)
            command = get_nth_item(message, 1)
            if(command == "LOGIN"):
                connected_clients[clientName] = websocket
                print(f"login from {clientName}")
            
            if(clientName in connected_clients):
                print("send to server")
                send_udp_to_gameServer(message)

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
        t1 = threading.Thread(target=receive_udp_from_gameServer_and_forward_to_client)
        t1.start()
        #asyncio.get_event_loop().run_until_complete(main(send_message()))
        #asyncio.get_event_loop().create_task(send_message())

        asyncio.get_event_loop().run_until_complete(start_server)
        print("start server")
        asyncio.get_event_loop().run_forever()

    except KeyboardInterrupt:
        print("WebSocket server terminated.")
        sys.exit(0)





