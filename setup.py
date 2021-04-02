from setuptools import setup

setup(
    name="barva",
    licence="GPLv3+",
    packages=["barva"],
    install_requires=["numpy"],
    tests_require=["pytest"],
    entry_points={"console_scripts": ["barva=barva.__main__:main"]},
)
