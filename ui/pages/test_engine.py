import streamlit as st
import requests

API_URL = "http://127.0.0.1:8000"

st.sidebar.header("Testing for the Orchestrator")

if st.button("Test the C++ engine"):
    st.info("Sending the request to the orchestrator")

    try:
        response = requests.get(f"{API_URL}/test_engine")
        if response.status_code == 200:
            data = response.json()
            st.success("Success!")

            st.write("Message from the API: ", data.get("message"))
            st.metric(label="Result is equal to: ", value=data.get("result"))

        else:
            st.error(f"Error from the API: {response.status_code}")

    except requests.exceptions.ConnectionError:
        st.error("Unable to connect to the API. Make sure the Orchestrator (FastAPI) is running in another terminal!")