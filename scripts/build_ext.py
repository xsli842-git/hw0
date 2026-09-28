"""Build the homework's pybind11 extension with the active Python environment."""

import os
import subprocess
import sys
import sysconfig
from pathlib import Path

import pybind11


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src" / "simple_ml_ext.cpp"
OUTPUT = ROOT / "src" / ("simple_ml_ext" + sysconfig.get_config_var("EXT_SUFFIX"))


def main():
    includes = [f"-I{sysconfig.get_path('include')}", f"-I{pybind11.get_include()}"]
    env = os.environ.copy()

    if os.name == "nt":
        import ziglang

        compiler = Path(ziglang.__file__).parent / "zig.exe"
        python_lib = Path(sys.base_prefix) / "libs" / f"python{sys.version_info.major}{sys.version_info.minor}.lib"
        env["ZIG_GLOBAL_CACHE_DIR"] = str(ROOT / ".zig-cache")
        command = [str(compiler), "c++", "-O2", "-shared", "-std=c++11", *includes,
                   str(python_lib), str(SOURCE), "-o", str(OUTPUT)]
    else:
        command = ["c++", "-O3", "-shared", "-std=c++11", "-fPIC", *includes,
                   str(SOURCE), "-o", str(OUTPUT)]
        if sys.platform == "darwin":
            command += ["-undefined", "dynamic_lookup"]

    subprocess.run(command, cwd=ROOT, env=env, check=True)
    print(f"Built {OUTPUT}")


if __name__ == "__main__":
    main()
