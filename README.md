# Homework 0
Public repository and stub/testing code for Homework 0 of 10-714.

## Run locally in VS Code (macOS)

Install the Microsoft **Python** and **Jupyter** extensions in VS Code. Open this
folder and `hw0.ipynb`, then select **HW0 (.venv Python 3.12)** in the notebook's
top-right kernel picker. Alternatively select **Python Environments** and choose
`.venv/bin/python`. Run the setup cells first, then the cells for the question
you are working on. Skip the `mugrade submit` cells until you are ready to submit.

To recreate the environment with [uv](https://docs.astral.sh/uv/):

```sh
UV_PYTHON_INSTALL_DIR="$PWD/.python" uv venv .venv --python 3.12 --seed
uv pip install --python .venv/bin/python -r requirements.txt
.venv/bin/python -m ipykernel install --user --name hw0-venv --display-name "HW0 (.venv Python 3.12)"
.venv/bin/python scripts/build_ext.py
```

The C++ build requires Apple's Command Line Tools (`xcode-select --install` if
they are missing). The `.python` directory contains the local Python runtime;
keep it alongside `.venv`.

To activate the environment and test the currently implemented functions:

```sh
source .venv/bin/activate
python -m pytest -q -k 'add or parse_mnist'
```

Run `python -m pytest -q` for all assignment tests. Questions 3–6 still contain
unfinished functions, so their tests and training cells will fail until those
functions are implemented.

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
ready to submit. `mugrade` is not installed by `requirements.txt`; it is optional
for local work and must be installed separately before online submission.
