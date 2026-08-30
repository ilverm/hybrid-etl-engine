import streamlit as st
import requests

API_URL = "http://127.0.0.1:8000"

st.sidebar.header("test read csv")

uploaded_file = st.file_uploader("Upload a CSV file", type=["csv"])
if uploaded_file is not None:
    r = requests.post(url=f"{API_URL}/read_csv", files={"file": (uploaded_file.name, uploaded_file, "text/csv")})
    if r.status_code == 200:
        data = r.json()
        st.success("Success!")

        st.write("CSV:")
        st.dataframe(data.get("result"))

    else:
        st.error(f"Error from the API: {r.status_code}")