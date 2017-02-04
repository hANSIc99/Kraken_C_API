from distutils.core import setup, Extension

kraken = Extension('kraken', sources = ['krakenmodule.c'])

setup (name = 'PackageName', version = '0.1',
        description = 'This is a demo package',
        ext_modules = [kraken])

