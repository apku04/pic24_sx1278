from fastapi import FastAPI, WebSocket
from fastapi.staticfiles import StaticFiles
import serial

app = FastAPI()

# Mount static files
app.mount("/static", StaticFiles(directory="static"), name="static")

ser = serial.Serial('COM10', 57600)  # Adjust as per your setup

@app.get("/")
async def get():
    # Redirect to the static HTML page
    return {"status": "WebSocket Server is running"}

@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    while True:
        data = ser.readline().decode('utf-8').strip()
        await websocket.send_text(data)
