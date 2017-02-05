from distutils.core import setup, Extension
"""
kraken = Extension('kraken', sources = ['krakenmodule.c'])

setup (name = 'PackageName', version = '0.1',
        description = 'This is a demo package',
        ext_modules = [kraken])
"""

setup(name="kraken", version="1.0",
      ext_modules=[
         Extension("kraken", ["krakenmodule.c"]),
         Extension("noddy", ["noddy.c"]),
         ])
