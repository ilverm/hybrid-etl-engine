import sys
import pytest

from fastapi.testclient import TestClient
from main import app
from pathlib import Path

current_dir = Path(__file__).parent

engine_path = current_dir.parent / "engine" / "cmake-build-debug"
sys.path.append(str(engine_path.resolve()))

import engine

client = TestClient(app)

def test_read_root():
    response = client.get("/")
    assert response.status_code == 200
    assert response.json() == {"status": "Orchestrator is running"}

def test_test_engine():
    response = client.get("/test-engine")
    assert response.status_code == 200
    assert response.json() == {
        "message": "Calculation performed by the native C++ engine.",
        "result": 12
    }

@pytest.mark.parametrize("number_of_lines_to_be_read, expected", [
    (5, 5),
    (10, 10)
])
def test_read_csv(number_of_lines_to_be_read, expected):
    result = engine.read_csv("people.csv", number_of_lines_to_be_read)
    assert len(result) == expected

def test_read_csv_endpoint():
    response = client.get("/read-csv")
    assert response.status_code == 200
    assert isinstance(response.json().get("result"), list)
    assert len(response.json().get("result")) == 5
    header = ["Index","User Id","First Name","Last Name","Sex","Email","Phone","Date of birth","Job Title\r"]
    assert header == response.json().get("result")[0]

