import streamlit as st
import requests

API_URL = "http://127.0.0.1:8000"

if st.button("Test connector"):

    try:
        response = requests.get(f"{API_URL}/connect_db")
        if response.status_code == 200:
            data = response.json()
            st.success("Success!")

            st.write("Message from the API: ", data.get("message"))
            st.metric(label="Health check is equal to: ", value=data.get("health_check"))
            st.metric(label="Create table is equal to: ", value=data.get("result"))
            st.metric(label="Populate db is equal to: ", value=data.get("populate_db"))

        else:
            st.error(f"Error from the API: {response.status_code}")

    except requests.exceptions.ConnectionError:
        st.error("Unable to connect to the API. Make sure the Orchestrator (FastAPI) is running in another terminal!")