# Homework 0
Public repository and stub/testing code for Homework 0 of 10-714.

## Run locally in VS Code (Windows)

Open this folder in VS Code, open `hw0.ipynb`, and click the kernel name in the
top-right corner. Select `HW0 (.venv Python 3.12)` (under **Select Another Kernel
> Jupyter Kernel**, if needed), or choose **Python Environments** and select
`.venv\Scripts\python.exe`. An already selected notebook kernel can differ from
the workspace's default Python interpreter. Run notebook cells in order as you implement functions in
`src/simple_ml.py` and `src/simple_ml_ext.cpp`; the starter functions are
unfinished, so the assignment tests will fail until you complete them.

To recreate the environment with [uv](https://docs.astral.sh/uv/):

```powershell
uv venv .venv --python 3.12
uv pip install --python .venv\Scripts\python.exe -r requirements.txt
.\.venv\Scripts\python.exe -m ipykernel install --user --name hw0-venv --display-name "HW0 (.venv Python 3.12)"
```

To run the local tests or build the C++ extension from a terminal:

```powershell
.\.venv\Scripts\python.exe -m pytest -q
.\.venv\Scripts\python.exe scripts\build_ext.py
```

The submission cells require your own mugrade key. Run them only when you are
ready to submit.
