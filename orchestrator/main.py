import sys
import os
import shutil
from fastapi import FastAPI, UploadFile
from pathlib import Path

import config

current_dir = Path(__file__).parent

engine_path = current_dir.parent / "engine" / "cmake-build-debug"
sys.path.append(str(engine_path.resolve()))

import engine

app = FastAPI(title="ETL engine")

@app.get("/")
def read_root():
    return {"status": "Orchestrator is running"}

@app.get("/test_engine")
def test_engine():
    result = engine.add(5,7)
    return {
        "message": "Calculation performed by the native C++ engine.",
        "result": result
    }

@app.post("/read_csv")
def read_file(file: UploadFile):
    if not os.path.exists("Uploads/"):
        os.makedirs("Uploads/")
    file_path = "Uploads/" + file.filename
    with open(file_path, "wb") as f:
        shutil.copyfileobj(file.file, f)

    result = engine.read_csv(file_path, first_n_lines = 5)
    return {"result": result}

@app.get("/connect_db")
def connect_db():
    connection_string = config.connection_string
    health_check = engine.connect_to_db(connection_string)
    create_table = engine.create_table(connection_string, "people", ["Index","User Id","First Name","Last Name","Sex","Email","Phone","Date of birth","Job Title"])
    populate_db = engine.populate_db(connection_string, "people", "people.csv")
    return {
        "message": "Connection successful",
        "health_check": health_check,
        "result": create_table,
        "populate_db": populate_db
    }