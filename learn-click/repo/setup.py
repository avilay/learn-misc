from setuptools import setup

setup(
    name="click-example-repo",
    version="0.1",
    py_modules=["repo"],
    include_package_data=True,
    install_requires=["click"],
    entry_points="""
        [console_scripts]
        aptgrepo=repo:cli
    """,
)
