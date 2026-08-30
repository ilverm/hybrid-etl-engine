import streamlit as st

pages = [
    st.Page("pages/home.py", title="Home"),
    st.Page("pages/test_engine.py", title="Engine"),
    st.Page("pages/read_csv.py", title="Read CSV"),
]

pg = st.navigation(pages=pages)
pg.run()