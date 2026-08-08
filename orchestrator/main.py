import sys

from fastapi import FastAPI
from pathlib import Path

current_dir = Path(__file__).parent

engine_path = current_dir.parent / "engine" / "cmake-build-debug"
sys.path.append(str(engine_path.resolve()))

import engine

app = FastAPI(title="ETL engine")

@app.get("/")
def read_root():
    return {"status": "Orchestrator is running"}

@app.get("/test-engine")
def test_engine():
    result = engine.add(5,7)
    return {
        "message": "Calculation performed by the native C++ engine.",
        "result": result
    }
