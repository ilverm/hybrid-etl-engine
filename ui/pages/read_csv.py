import streamlit as st
import requests

API_URL = "http://127.0.0.1:8000"

st.sidebar.header("test read csv")

if st.button("Read CSV"):
    try:
        response = requests.get(f"{API_URL}/read_csv")
        if response.status_code == 200:
            data = response.json()
            st.success("Success!")

            st.write("CSV:")
            st.dataframe(data.get("result"))

        else:
            st.error(f"Error from the API: {response.status_code}")

    except requests.exceptions.ConnectionError:
        st.error("Unable to connect to the API. Make sure the Orchestrator (FastAPI) is running in another terminal!")