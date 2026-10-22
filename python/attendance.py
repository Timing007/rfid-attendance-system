import serial
import openpyxl
from datetime import datetime
import os

PORT = "COM9"
BAUD = 9600
FILE = "attendance.xlsx"

# Student data — name, ID number, UID
students = {
    "56F39126": {"name": "Akshat", "id": "4872519", "uid": "56 F3 91 26"},
    "F6F69D26": {"name": "Arnav",  "id": "3916204", "uid": "F6 F6 9D 26"},
    "66570C26": {"name": "Akash",  "id": "7253981", "uid": "66 57 0C 26"},
}

if not os.path.exists(FILE):
    wb = openpyxl.Workbook()
    ws = wb.active
    ws.title = "Attendance"
    ws.append(["Name", "ID Number", "UID", "Status", "Time", "Date"])
    wb.save(FILE)

ser = serial.Serial(PORT, BAUD, timeout=1)
print("Listening to Arduino...")

while True:
    line = ser.readline().decode("utf-8").strip()

    if line.startswith("PRESENT:") or line.startswith("ALREADY MARKED:") or line.startswith("DENIED:"):
        print(line)
        wb = openpyxl.load_workbook(FILE)
        ws = wb.active
        now = datetime.now()

        if line.startswith("PRESENT:"):
            raw_name = line.replace("PRESENT: ", "").strip()
            status = "Present"
        elif line.startswith("ALREADY MARKED:"):
            raw_name = line.replace("ALREADY MARKED: ", "").strip()
            status = "Already Marked"
        else:
            raw_name = "Unknown"
            status = "Access Denied"

        student = next((s for s in students.values() if s["name"] == raw_name), None)

        if student:
            name = student["name"]
            id_number = student["id"]
            uid = student["uid"]
        else:
            name = "Unknown"
            id_number = "N/A"
            uid = "N/A"

        ws.append([
            name,
            id_number,
            uid,
            status,
            now.strftime("%H:%M:%S"),
            now.strftime("%d/%m/%Y")
        ])
        wb.save(FILE)
        print(f"Logged: {name} | {id_number} | {uid} | {status}")
