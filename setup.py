from distutils.core import setup, Extension
import subprocess
"""
kraken = Extension('kraken', sources = ['krakenmodule.c'])

setup (name = 'PackageName', version = '0.1',
        description = 'This is a demo package',
        ext_modules = [kraken])
"""

krakenprivatemodule = Extension('kraken',
        library_dirs = ['.'],
        libraries = ['kraken'],
        sources = ['krakenprivatemodule.c'])


setup (name="kraken", version="1.0",
      ext_modules=[krakenprivatemodule])

