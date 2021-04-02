from setuptools import find_packages
from setuptools import setup

setup(
    name="barva",
    version="0.7.0",
    license="GPLv3+",
    install_requires=["numpy"],
    tests_require=["pytest", "hypothesis"],
    entry_points={"console_scripts": ["barva=barva.__main__:main"]},
    url="https://github.com/Kharacternyk/barva",
    packages=find_packages(),
)
