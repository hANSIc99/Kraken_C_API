from distutils.core import setup, Extension
import subprocess


krakenprivatemodule = Extension('kraken',
        include_dirs = ['.'],
        libraries = [ 'crypto'],
        library_dirs = ['.'],
        sources = ['krakenprivatemodule.c'])


setup (name="kraken", version="1.0",
      ext_modules=[krakenprivatemodule])

