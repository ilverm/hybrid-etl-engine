from fastapi.testclient import TestClient
from main import app

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